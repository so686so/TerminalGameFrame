#pragma once

#include "Types.h"
#include "Coord.h"
#include "Tiles.h"
#include "ConsoleCmd.h"
#include "KString.h"

enum class DIRECTION
{
    HORIZONTAL = 0,
    VERTICAL,
};

inline void drawLine( const int len )
{
    for( int i=0; i<len; ++i ) printf( "%s", HORIZON_LINE );
}

inline void drawLine( const COORD& startPos, const int len )
{
    setCoord( startPos );
    drawLine( len );
}

inline void drawPattern( const int repeatCnt, KString& pattern )
{
    const int ptnWidth          = pattern.getWordsWidth();
    const int totalWidth        = getConsoleWidth();
    const int adjustRepeatCnt   = ( repeatCnt * ptnWidth > totalWidth ) ? totalWidth / ptnWidth : repeatCnt;

    std::string strPtn = pattern.getString();
    for( int i=0; i<adjustRepeatCnt; ++i ) printf("%s", strPtn.c_str() );

    if( adjustRepeatCnt < repeatCnt ) {
        int remainWidth = totalWidth - ( ptnWidth * adjustRepeatCnt );
        int k = 0;
        while( remainWidth > 0 ) {
            int ptnLen = pattern.getWordsLength();
            std::string strTkn = pattern[k++ % ptnLen];
            KString token {strTkn};

            if( (int)token.getWordsWidth() > remainWidth ) break;
            printf("%s", strTkn.c_str() );

            remainWidth -= token.getWordsWidth();
        }
    }
}

inline void drawPattern( const int repeatCnt, const std::string& pattern )
{
    KString kPattern {pattern};
    drawPattern( repeatCnt, kPattern );
}

static int getPatternEmptySpace( KString& pattern )
{
    for( size_t i=0; i<pattern.getWordsLength(); ++i )
        if( pattern[i] != TILE_1["EMPTY_TILE"] ) return 0;
    return pattern.getWordsLength();
}

inline COORD drawPattern( const COORD& startPos, const int repeatCnt, KString& pattern )
{
    const int ptnWidth          = pattern.getWordsWidth();
    const int totalWidth        = getConsoleWidth() - startPos.xPos;
    const int adjustRepeatCnt   = ( repeatCnt * ptnWidth > totalWidth ) ? totalWidth / ptnWidth : repeatCnt;
    const int emptySpaceCount   = getPatternEmptySpace(pattern);

    if( emptySpaceCount == 0 ) {
        setCoord( startPos );

        std::string strPtn = pattern.getString();
        for( int i=0; i<adjustRepeatCnt; ++i ) printf("%s", strPtn.c_str() );

        if( adjustRepeatCnt < repeatCnt ) {
            int remainWidth = totalWidth - ( ptnWidth * adjustRepeatCnt );
            int k = 0;
            while( remainWidth > 0 ) {
                int ptnLen = pattern.getWordsLength();
                std::string strTkn = pattern[k++ % ptnLen];
                KString token {strTkn};

                if( (int)token.getWordsWidth() > remainWidth ) break;
                printf("%s", strTkn.c_str() );

                remainWidth -= token.getWordsWidth();
            }
        }
    }

    return { startPos.xPos + ( adjustRepeatCnt * ptnWidth ), startPos.yPos };
}

inline void drawPatternWithEdge( const COORD&       startPos, 
                                 const int          totalLen, 
                                 const std::string& lEdge, const std::string& pattern, const std::string& rEdge ) 
{
    KString kLEdge {lEdge};
    const int lEdgeLen = kLEdge.getWordsWidth();

    KString kREdge {rEdge};
    const int rEdgeLen = kREdge.getWordsWidth();

    KString kPattern {pattern};
    const int patternRepeatCnt = ( totalLen - ( lEdgeLen + rEdgeLen ) ) / kPattern.getWordsWidth();

    COORD curPos = startPos;

    curPos = drawPattern( curPos, 1, kLEdge );
    curPos = drawPattern( curPos, patternRepeatCnt, kPattern );
    drawPattern( curPos, 1, kREdge );
}

inline void drawPatternWithEdge( const COORD& startPos, 
                                 const int    totalLen, 
                                 const char*  lEdge, const char* pattern, const char* rEdge )
{
    std::string strLE = lEdge;
    std::string strPt = pattern;
    std::string strRE = rEdge;

    drawPatternWithEdge( startPos, totalLen, strLE, strPt, strRE );
}

inline COORD drawFrame( const COORD& startPos, const int width, const int height )
{
    COORD curPos = startPos;

    drawPatternWithEdge( curPos, width, " ┌─", "───", "─┐ " ); curPos.yPos++;
    for( int i=0; i<height-2; ++i ) {
    drawPatternWithEdge( curPos, width, " │ ", "   ", " │ " ); curPos.yPos++;
    }
    drawPatternWithEdge( curPos, width, " └─", "───", "─┘ " );

    curPos.xPos += width;
    curPos.yPos += 1;

    fflush(stdout);

    return curPos;
}