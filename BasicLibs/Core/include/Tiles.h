#pragma once

/*
    터미널에 맵을 그릴 때 사용하는 타일에 관한 헤더파일
*/

#include <string>
#include <map>
#include "Types.h"

// TILE UNIT 의 최대 단위 크기. 하나의 타일 패턴은 아래 크기를 넘을 수 없음. 조절 가능.
DEFINE TILE_UNIT_WIDTH  = 3;

enum TILE_NAME
{
    EMPTY_TILE,
    VERTICAL_LINE,
    HORIZONTAL_LINE,

    LEFT_TOP_EDGE,
    RIGHT_TOP_EDGE,

    LEFT_BOTTOM_EDGE,
    RIGHT_BOTTOM_EDGE,
};

typedef std::string               TILE;
typedef std::map<TILE_NAME, TILE> TILE_SET;

#define TILE(x) TILE_1[x]

// 터미널에서 한 칸을 차지하는 타일들의 집합
extern TILE_SET TILE_1;

// 터미널에서 두 칸을 차지하는 타일들의 집합
extern TILE_SET TILE_2;