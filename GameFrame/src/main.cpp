#include "KString.h"
#include "ConsoleCmd.h"
#include "Key.h"
#include "GameThread.h"
#include "Draw.h"
#include "Frame.h"

using namespace GameFrame;

class TestFrame
{
private:
    int consoleW;
    int consoleH;

    Frame mapFrame;
    Frame invFrame;
    Frame logFrame;

public:
    TestFrame();
    ~TestFrame() {};

    int getFrameWidth() { return consoleW; };
    int getFrameHeight() { return consoleH; };

    void resize();
    void draw();
};

TestFrame::TestFrame()
    : consoleW(getConsoleWidth())
    , consoleH(getConsoleHeight())
    , mapFrame({0,0}, consoleW*3/4, consoleH*3/5)
    , invFrame({consoleW*3/4, 0}, consoleW/4, consoleH*3/5)
    , logFrame({0, consoleH*3/5}, consoleW, consoleH*2/5)
{
    consoleW = (consoleW/4)*4;
    consoleH = (consoleH/5)*5;

    resizeConsole(consoleW, consoleH);

    mapFrame.setFrameName("메인 화면");
    invFrame.setFrameName("인벤토리");
    logFrame.setFrameName("로그 시스템");
}

void TestFrame::draw()
{
    mapFrame.draw();
    invFrame.draw();
    logFrame.draw();
}

void TestFrame::resize()
{
    consoleW = getConsoleWidth();
    consoleH = getConsoleHeight();

    consoleW = (consoleW/4)*4;
    consoleH = (consoleH/5)*5;

    resizeConsole(consoleW, consoleH);

    mapFrame.resize({0,0}, consoleW*3/4, consoleH*3/5);
    invFrame.resize({consoleW*3/4, 0}, consoleW/4, consoleH*3/5);
    logFrame.resize({0, consoleH*3/5}, consoleW, consoleH*2/5);
}

int main()
{
// 화면 크기 고정 테스트 코드
#if 1
    TestFrame TF;
    TF.draw();

    while( TRUE ) {
        if( TF.getFrameWidth() != getConsoleWidth() || TF.getFrameHeight() != getConsoleHeight() ) {
            TF.resize();
            TF.draw();
        }
        usleep(1000000/3);
    }
#endif

// KString 테스트코드
#if 0
    KString test = "A[◎]B●C◎[▣]DEFGHI12345456712312312 ┌─123─┐ ";
    // KString test = "비엔지티 시스템 1234 ABC ◎ ●◎ 소병준";
    std::string test2 = "비엔지티 시스템 1234 ABC 소병준";

    printf("TotalLen : %d\n", (int)test.getWordsLength());
    // printf("%s \n", test[0]);
    // printf("%s \n", test[6]);
    // printf("%s \n", test[19]);

    std::cout << test.getString() << std::endl;
    // std::string c1 = test[2];
    // std::cout << test[1] << std::endl;
    // std::cout << c1 << std::endl;
    // std::cout << test[3] << std::endl;
    // std::cout << test2[0] << " / " << test2[6] << " / " << test2[19] << std::endl;

    // for( size_t i = 0; i < test.getWordsLength(); ++i )
    //     std::cout << test[i] << std::endl;

    // printf("CW : %d\n", (int)test.getWordsWidth());
    // printf("%s\n", test.c_str());
    // for(int i = 0; i < (int)test.getWordsWidth(); i++) printf(".");
    // printf("\n");

    // test += "";

    // printf("CW : %d\n", (int)test.getWordsWidth());
    // printf("%s\n", test.c_str());
    // for(int i = 0; i < (int)test.getWordsWidth(); i++) printf(".");
    // printf("\n");

    // KString test3 = " 한번 더 추가 1234?#";
    // test += test3;

    // printf("CW : %d\n", (int)test.getWordsWidth());
    // printf("%s\n", test.c_str());
    // for(int i = 0; i < (int)test.getWordsWidth(); i++) printf(".");
    // printf("\n");
    printf("END");
    fflush(stdout);
#endif

// Key 테스트코드
#if 0
    COORD curCPos = {3, 3};

    setCoord(curCPos);
    printf("O");
    while( TRUE ) {
        int key = readKey();
        switch(key)
        {
        case KEY_TYPE::UP:
            curCPos.yPos--;
            setCoord(curCPos);
            printf("O");
            break;
        case KEY_TYPE::DOWN:
            curCPos.yPos++;
            setCoord(curCPos);
            printf("O");
            break;
        case KEY_TYPE::LEFT:
            curCPos.xPos--;
            setCoord(curCPos);
            printf("O");
            break;
        case KEY_TYPE::RIGHT:
            curCPos.xPos++;
            setCoord(curCPos);
            printf("O");
            break;
        case KEY_TYPE::ENTER:
            TF.resize();
            TF.draw();
            setCoord(curCPos);
            break;
        default:
            break;
        }
        fflush(stdout);
    }
#endif

    return 0;
}