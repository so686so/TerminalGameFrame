#pragma once

#include "Types.h"
#include "Coord.h"
#include "Tiles.h"
#include "ConsoleCmd.h"
#include "KString.h"

// 가로 방향 직선 그리기
inline void drawLine( const int len )
{
    for( int i=0; i<len; ++i ) 
        printf( "%s", TILE(TILE_NAME::HORIZONTAL_LINE).c_str() );
}

// startPos 좌표부터 가로 방향 직선 그리기
inline void drawLine( const COORD& startPos, const int len )
{
    setCoord( startPos );
    drawLine( len );
}

// 가로 방향 한 줄 지우기 ( 공백으로 덮어쓰기 )
inline void clearLine( const int len )
{
    for( int i=0; i<len; ++i ) 
        printf( "%s", TILE(TILE_NAME::EMPTY_TILE).c_str() );
}

inline void clearLine( const COORD& startPos, const int len )
{
    setCoord( startPos );
    clearLine( len );
}

// 가로 방향 특정 패턴 직선 그리기
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

static const int getPatternEmptySpace( KString& pattern )
{
    for( size_t i=0; i<pattern.getWordsLength(); ++i )
        if( pattern[i] != TILE(EMPTY_TILE) ) return 0;
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
        // Draw pattern
        for( int i=0; i<adjustRepeatCnt; ++i ) printf("%s", strPtn.c_str() );

        // Draw pattern : remain space
        if( adjustRepeatCnt < repeatCnt ) {
            int remainWidth = totalWidth - ( ptnWidth * adjustRepeatCnt );
            int k = 0;
            // 남은 간격 안에 각 글자 너비 계산해서, 한글자씩 채워가며 여분 공간 체크
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

inline COORD drawPatternWithEdge( const COORD&      startPos, 
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
    return   drawPattern( curPos, 1, kREdge );
}

inline COORD drawPatternWithEdge( const COORD& startPos, 
                                  const int    totalLen, 
                                  const char*  lEdge, const char* pattern, const char* rEdge )
{
    std::string strLE = lEdge;
    std::string strPt = pattern;
    std::string strRE = rEdge;

    return drawPatternWithEdge( startPos, totalLen, strLE, strPt, strRE );
}

inline COORD drawFrame( const COORD& startPos, const int width, const int height )
{
    COORD curPos = startPos;

    drawPatternWithEdge( curPos, width, " ┌─", "───", "─┐ " ); curPos.yPos++;
    for( int i=1; i<height-1; ++i ) {
    drawPatternWithEdge( curPos, width, " │ ", "   ", " │ " ); curPos.yPos++;
    }
    drawPatternWithEdge( curPos, width, " └─", "───", "─┘ " );

    fflush(stdout);

    return getCoord();
}