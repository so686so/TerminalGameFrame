#pragma once

#include <stdio.h>
#include "Types.h"

typedef struct _tCoord_
{
    int xPos;
    int yPos;
} COORD, *PCOORD;

inline COORD getCoord( const int xPos, const int yPos ) noexcept
{
    return { xPos, yPos };
}

inline void setCoord( const COORD& coord )
{
    printf("\033[%d;%df",coord.yPos+1, coord.xPos);
}