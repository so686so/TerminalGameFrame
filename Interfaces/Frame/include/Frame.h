#pragma once

#include <vector>
#include "Types.h"
#include "Tiles.h"
#include "ConsoleCmd.h"
#include "Coord.h"
#include "Draw.h"

// 각 인터페이스의 프레임 테두리를 그리는 기본 클래스
namespace GameFrame {
using namespace std;

class Frame {
public:
    Frame( const COORD startPos, const int width, const int height );
    ~Frame() {};

    COORD draw();
    void setFrameName( const string& fname ) { frameName_ = fname; };
    void resize( const COORD startPos, const int width, const int height );
    void setFrameColor( const enum FONT_COLOR color );

private:
    COORD   startPos_;
    int     width_;
    int     height_;
    FONT_COLOR frameColor_;
    string  frameName_;

    void drawFrameName();
}; // class Frame

}; // namespace GameFrame