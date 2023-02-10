#include "Tiles.h"

// 터미널에서 한 칸을 차지하는 타일들의 집합
TILE_SET TILE_1 = {
    { EMPTY_TILE,         " " },
    { VERTICAL_LINE,      "│" },
    { HORIZONTAL_LINE,    "─" },

    { LEFT_TOP_EDGE,      "┌" },
    { RIGHT_TOP_EDGE,     "┐" },

    { LEFT_BOTTOM_EDGE,   "└" },
    { RIGHT_BOTTOM_EDGE,  "┘" },
};

// 터미널에서 두 칸을 차지하는 타일들의 집합
TILE_SET TILE_2 = {
    { EMPTY_TILE, "  " },
};