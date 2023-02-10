#pragma once

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "Types.h"

DEFINE RD_EOF = -1;
DEFINE RD_EIO = -2;

typedef struct _tCoord_
{
    int xPos;
    int yPos;

    bool operator == ( const _tCoord_& A )
    {
        return (xPos == A.xPos) && (yPos == A.yPos);
    }

    bool operator != ( const _tCoord_& A )
    {
        return (xPos != A.xPos) || (yPos != A.yPos);
    }

} COORD, *PCOORD;

constexpr COORD ERROR_GET_COORD = { -1, -1 };

enum MOVE_TYPE
{
    ABSOLUTE_MOVEMENT,
    RELATIVE_MOVEMENT,
};

static inline int rd( const int fd ) 
{
    unsigned char buffer[4];
    ssize_t       n;

    while( TRUE ) {
        n = read( fd, buffer, 1 );

        if( n  > (ssize_t) 0 ) 
            return buffer[0];
        else 
        if( n == (ssize_t) 0 ) 
            return RD_EOF;
        else 
        if( n != (ssize_t)-1 ) 
            return RD_EIO;
        else 
        if( errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK ) 
            return RD_EIO;
    }
}

static inline int wr(const int fd, const char* const data, const size_t bytes )
{
    const char*       head = data;
    const char* const tail = data + bytes;
    ssize_t           n;

    while( head < tail ) {
        n = write( fd, head, (size_t)( tail - head ) );

        if( n  > (ssize_t) 0 )
            head += n;
        else
        if( n != (ssize_t)-1 )
            return EIO;
        else
        if( errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK )
            return errno;
    }
    return 0;
}

/* Return a new file descriptor to the current tty */
int current_tty(void)
{
    const char* dev;
    dev = ttyname(STDIN_FILENO);

    if( !dev )
        dev = ttyname(STDOUT_FILENO);
    if( !dev )
        dev = ttyname(STDERR_FILENO);
    if( !dev ) {
        errno = ENOTTY;
        return -1;
    }

    int fd;
    do {
        fd = open( dev, O_RDWR | O_NOCTTY );
    } while( fd == -1 && errno == EINTR );

    return fd;
}

/*  Ref by : https://www.linuxquestions.org/questions/programming-9/get-cursor-position-in-c-947833/
    As the tty for current cursor position. This function return TRUE if success. */
COORD getCoord()
{
    struct termios  save_attr, new_attr;
    int             result, rows, cols;
    COORD           co = ERROR_GET_COORD;

    // fflush last buffer
    fflush(stdout);

    int tty = current_tty();
    if( tty == -1 ) 
        return ERROR_GET_COORD;

    // Save current terminal setting
    do {
        result = tcgetattr( tty, &save_attr );
    } while( result == -1 && errno == EINTR );

    if( result == -1 ) 
        return ERROR_GET_COORD;

    // Get current terminal settings for basis, too
    do {
        result = tcgetattr( tty, &new_attr );
    } while( result == -1 && errno == EINTR );

    if( result == -1 ) 
        return ERROR_GET_COORD;

    // Disable ICANON, ECHO, CREAD
    new_attr.c_lflag &= ~ICANON;
    new_attr.c_lflag &= ~ECHO;
    new_attr.c_lflag &= ~CREAD;

    do {
        // Set modified setting
        do {
            result = tcsetattr( tty, TCSANOW, &new_attr );
        } while( result == -1 && errno == EINTR );

        if( result == -1 ) {
            break;
        }

        // Request cursor coord from the teminal
        result = wr( tty, "\033[6n", 4 );
        if( result ) {
            break;
        }

        // Expect an ESC
        result = rd(tty);
        if( result != 27 ) break;

        // Expect [ after ESC
        result = rd(tty);
        if( result != '[' ) break;

        // Parse rows(yPos)
        rows   = 0;
        result = rd(tty);
        while( result >= '0' && result <= '9' ) {
            rows   = 10 * rows + result - '0';
            result = rd(tty);
        }

        if( result != ';' ) break;

        // Parse cols(xPos)
        cols   = 0;
        result = rd(tty);
        while( result >= '0' && result <= '9' ) {
            cols   = 10 * cols + result - '0';
            result = rd(tty);
        }

        if( result != 'R' ) break;

        // Success
        co.xPos = cols - 1;
        co.yPos = rows - 1;
    } while( FALSE );

    // Restore saved terminal setting
    do {
        result = tcsetattr( tty, TCSANOW, &save_attr );
    } while( result == -1 && errno == EINTR );

    return co;
}

/*
    ABSOLUTE_MOVEMENT : 
        최상단좌측을 (0,0) 이라 했을 때, 길이 방향 'x', 높이 방향 'y' 아래로 절대좌표 이동

    RELATIVE_MOVEMENT : 
        현 위치에서 길이 방향 'x', 높이 방향 'y'만큼 상대좌표 이동
*/
inline void setCoord( const COORD& coord, MOVE_TYPE type = ABSOLUTE_MOVEMENT )
{
    int maxConsoleX = getConsoleWidth()  - 1;
    int maxConsoleY = getConsoleHeight() - 1;

    switch (type)
    {
    case MOVE_TYPE::ABSOLUTE_MOVEMENT:
        {
            // setCoord : zero-start / getConsoleSize : 1 start
            // getConsoleHeight() or getConsoleWidth() 값으로 setCoord 할 때를 위한 값 조절
            COORD curPos = {
                .xPos = ( coord.xPos == getConsoleWidth()  ) ? maxConsoleX : coord.xPos,
                .yPos = ( coord.yPos == getConsoleHeight() ) ? maxConsoleY : coord.yPos,
            };

            if( curPos.xPos >= 0 && curPos.xPos <= maxConsoleX &&
                curPos.yPos >= 0 && curPos.yPos <= maxConsoleY ){
                printf("\033[%d;%df", curPos.yPos+1, curPos.xPos+1);
            }
        }
        break;
    
    case MOVE_TYPE::RELATIVE_MOVEMENT:
        {
            COORD curPos = getCoord();
            if( curPos != ERROR_GET_COORD ){
                curPos.xPos += coord.xPos;
                curPos.yPos += coord.yPos;

                if( curPos.xPos >= 0 && curPos.xPos <= maxConsoleX &&
                    curPos.yPos >= 0 && curPos.yPos <= maxConsoleY ){
                    printf("\033[%d;%df", curPos.yPos+1, curPos.xPos+1);
                }
            }
        }
        break;
    }
}

inline void setCoord( const int xPos, const int yPos, MOVE_TYPE type = ABSOLUTE_MOVEMENT )
{
    setCoord( {xPos, yPos}, type );
}