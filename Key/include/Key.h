#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

#include "Types.h"

enum KEY_TYPE {
    UP      = 65,
    DOWN    = 66,
    RIGHT   = 67,
    LEFT    = 68,
    ENTER   = 10,
    ESC     = 27,
    SPACE   = 32,
    NONE    = -2,
};

DEFINE INPUT_MAX_LEN = ( 3 + 1 );

/*  
    일반적인 아스키 값과 다르게 
    방향키는 아스키 값이 '27 91 65' 처럼 
    연속된 아스키 값으로 읽힘 
    이 때 방향키의 두 번째 키값은 91 고정
*/

DEFINE NORMAL_KEY_INDEX  = 0;    // 방향키 or ESC 키를 제외한 일반 키 값 Index
DEFINE ARROW_CHECK_INDEX = 1;    // 방향키 or ESC 키인지 체크하는 값의 Index
DEFINE ARROW_VALUE_INDEX = 2;    // 입력값이 방향키일 때 실제 키 값 Index

DEFINE ARROW_CHECK_VALUE = 91;

int readKey();