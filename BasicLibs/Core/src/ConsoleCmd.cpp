#include "ConsoleCmd.h"

using namespace std;

string getStringResultFromCommand( const string&& cmd ) noexcept
{
    string result;
    char buffer[CMD_MAX_LEN] = { '\0', };

    // popen : 주어진 cmd 를 shell 로 실행하고 파이프 연결 후 fd 반환
    FILE* stream = popen( cmd.c_str(), "r" );
    if( stream ) {
        // popen 및 shell cmd 성공적으로 수행했다면, 결과 string 받아오기
        while( fgets( buffer, CMD_MAX_LEN, stream ) != NULL ) result.append( buffer );
        pclose( stream );
    }

    return result;
}

// if Terminal Size 50(Lines) x 100(Columns) -> 'stty size' return : 50 100
BOOL getConsoleSize( int& width, int& height )
{
    try {
        // getStringResultFromCommand 이용해서 터미널 사이즈 받은 다음 토큰화
        istringstream iss( getStringResultFromCommand( "stty size" ) );
        string        tokenString;

        getline( iss, tokenString, ' ' );
        height = atoi( tokenString.c_str() );

        getline( iss, tokenString, ' ' );
        width = atoi( tokenString.c_str() );

        return TRUE;
    }
    catch (...) {
        // getStringResultFromCommand Failed.
        return FALSE;
    }
}

int getConsoleWidth()
{
    try         { return stoi( getStringResultFromCommand( "stty size | awk '{print $2}'" ) ); }
    catch (...) { return 0; }
}

int getConsoleHeight()
{
    try         { return stoi( getStringResultFromCommand( "stty size | awk '{print $1}'" ) ); }
    catch (...) { return 0; }
}

void resizeConsole( const int width, const int height )
{
    if( width < CONSOLE_MIN_WIDTH || height < CONSOLE_MIN_HEIGHT ) return;

    string cmd = "resize -s " + to_string(height) + " " + to_string(width) + " >/dev/null";
    string res = getStringResultFromCommand( move(cmd) );
    UNUSED(res);
}
