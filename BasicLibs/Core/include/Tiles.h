#pragma once

#include "Types.h"
#include "KString.h"
#include <map>

DEFINE TILE_UNIT_WIDTH  = 3;

DEFINE EMPTY_TILE       = " ";
DEFINE HORIZON_LINE     = "─";
DEFINE VERTICAL_LINE    = "│";

typedef struct std::map<std::string, std::string> TILE_SET;

extern TILE_SET TILE_1;
