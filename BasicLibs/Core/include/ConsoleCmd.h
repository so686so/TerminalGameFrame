#pragma once

/*
    터미널과 직접 상호작용하는 함수 모음 헤더파일
*/

#include <stdio.h>
#include <iostream>
#include <sstream>

#include "Types.h"

DEFINE CMD_MAX_LEN          = 256;
DEFINE CONSOLE_MIN_WIDTH    = 40;
DEFINE CONSOLE_MIN_HEIGHT   = 10;

enum FONT_COLOR {
    COLOR_START             = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    CYAN,
    SKY,
    WHITE,
    COLOR_END,
    RESET                   = 0,
};

DEFINE BACK_COLOR_OFFSET    = 10;
enum BACK_COLOR {
    B_COLOR_START           = ( FONT_COLOR::COLOR_START + BACK_COLOR_OFFSET ),
    B_RED,
    B_GREEN,
    B_YELLOW,
    B_BLUE,
    B_CYAN,
    B_SKY,
    B_WHITE,
    B_COLOR_END,
    B_RESET                 = 0,
};

// 쉘 스크립트에 명령어(cmd 인자)를 입력해 나온 결과를 반환하는 함수
std::string getStringResultFromCommand( const std::string&& cmd ) noexcept;

// 이하 사이즈들은 기본 유니코드 글자 기준 칸 단위
BOOL        getConsoleSize( int& width, int& height );
int         getConsoleWidth();
int         getConsoleHeight();
void        resizeConsole( const int width, const int height );

// 터미널에서 커서 숨김
inline void cursor_off( void )
{
    printf("\33[?25l");
}

// 숨긴 커서 다시 활성화
inline void cursor_on( void )
{
    printf("\33[?25h");
}

// setFontColor 함수 실행 이후의 글자 색 변경
inline void setFontColor( enum FONT_COLOR color )
{
    if( color > FONT_COLOR::COLOR_START && 
        color < FONT_COLOR::COLOR_END   ){
        printf("\x1b[0m");
        printf("\x1b[%dm", color);
    }
    else if( color == FONT_COLOR::RESET )
        printf("\x1b[0m");
}

// setBackColor 함수 실행 이후의 배경 색 변경
inline void setBackColor( enum BACK_COLOR color )
{
    if( color > BACK_COLOR::B_COLOR_START &&
        color < BACK_COLOR::B_COLOR_END   ){
        printf("\x1b[0m");
        printf("\x1b[%dm", color);
    }
    else if( color == BACK_COLOR::B_RESET )
        printf("\x1b[0m");
}