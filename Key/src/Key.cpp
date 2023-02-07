#include "Key.h"

typedef struct termios Termios;
static Termios set_termios_non_canonical_opt( Termios *set_attr )
{
    Termios save_attr = *set_attr;

    // 즉시 입력 받아지게 새로운 stdin 옵션 설정
    set_attr->c_lflag       &= ~(ICANON | ECHO);
    set_attr->c_cc[VMIN]    = 2;
    set_attr->c_cc[VTIME]   = 1;

    // set
    tcsetattr(STDIN_FILENO, TCSANOW, set_attr);

    return save_attr;
}

static int verify_keyboard_input( char* read_data )
{
    // Normal Case
    if( read_data[NORMAL_KEY_INDEX] != KEY_TYPE::ESC )
        return read_data[NORMAL_KEY_INDEX];
    
    // Arrow or ESC
    if( read_data[ARROW_CHECK_INDEX] == ARROW_CHECK_VALUE )
        return read_data[ARROW_VALUE_INDEX];
    else
        return KEY_TYPE::ESC;
}

int readKey()
{
    int  res                        = KEY_TYPE::NONE;
    int  read_bytes                 = 0;
    char read_data[INPUT_MAX_LEN]   = { 0x00, };

    Termios stdin_attr;
    memset( &stdin_attr, 0x00, sizeof(Termios) );

    // 기존 stdin 옵션 get 및 새로운 옵션 할당을 위한 함수 실행
    tcgetattr( STDIN_FILENO, &stdin_attr );
    Termios save_attr = set_termios_non_canonical_opt( &stdin_attr );

    read_bytes = read( STDIN_FILENO, read_data, INPUT_MAX_LEN );
    if( read_bytes > 0 )
        res = verify_keyboard_input( read_data );

    // 기존 stdin 옵션으로 롤백
    tcsetattr( STDIN_FILENO, TCSANOW, &save_attr );

    return res;
}