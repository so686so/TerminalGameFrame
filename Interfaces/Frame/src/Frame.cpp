#include "Frame.h"

using namespace GameFrame;

Frame::Frame( COORD startPos, const int width, const int height )
    : startPos_(startPos)
    , width_( ( width / TILE_UNIT_WIDTH ) * TILE_UNIT_WIDTH ) // Frame 은 반드시 TILE_UNIT_WIDTH 의 배수여야 함
    , height_( height )
    , frameColor_(FONT_COLOR::RESET)
{
    if( startPos_.xPos + width_ > getConsoleWidth() )
        width_ = getConsoleWidth() - startPos_.xPos;

    if( startPos_.yPos + height_ > getConsoleHeight() )
        height_ = getConsoleHeight() - startPos_.yPos;
}

COORD Frame::draw()
{
    setFontColor(frameColor_);
    COORD resPos = drawFrame(startPos_, width_, height_);
    setFontColor(FONT_COLOR::RESET);
    this->drawFrameName();
    return resPos;
}

void Frame::setFrameColor( const enum FONT_COLOR color )
{
    if( color > FONT_COLOR::COLOR_START && color < FONT_COLOR::COLOR_END )
        frameColor_ = color;
}

DEFINE FRAME_HEAD_PAD = 4;
void Frame::drawFrameName()
{
    if( frameName_.empty() ) return;

    KString kStr(frameName_);
    const int frameNameWidth = kStr.getWordsWidth();

    string adjustLenString;

    // '     [ {NAME} ] ' : total pad = 16
    if( frameNameWidth > width_ - 16 ) {
        int remain_len = width_ - 16;
        int i = 0;

        while( remain_len > 1 ) {
            string strToken = kStr[i++];
            KString kTkn(strToken);

            adjustLenString += strToken;
            remain_len -= (int)kTkn.getWordsWidth();
        }
        adjustLenString += "..";
    } else {
        adjustLenString = frameName_;
    }

    string headString = " [ ";
    headString += adjustLenString;
    headString += " ] ";

    setCoord( { startPos_.xPos + FRAME_HEAD_PAD, startPos_.yPos} );
    printf("%s\n", headString.c_str());
}

void Frame::resize( const COORD startPos, const int width, const int height )
{
    startPos_   = startPos;
    width_      = width;
    height_     = height;
}
