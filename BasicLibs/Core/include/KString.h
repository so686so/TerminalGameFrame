#pragma once
// For Korean String by UTF-8

#include <iostream>
#include <string>
#include "Types.h"
#include "Tiles.h"

DEFINE CHAR_SIZE_4_CHCK_FLAG = 0B11111000;
DEFINE CHAR_SIZE_4_COMP_FLAG = 0B11110000;

DEFINE CHAR_SIZE_3_CHCK_FLAG = 0B11110000;
DEFINE CHAR_SIZE_3_COMP_FLAG = 0B11100000;

DEFINE CHAR_SIZE_2_CHCK_FLAG = 0B11100000;
DEFINE CHAR_SIZE_2_COMP_FLAG = 0B11000000;

DEFINE CHAR_SIZE_1_CHCK_FLAG = 0B10000000;
DEFINE CHAR_SIZE_1_COMP_FLAG = 0B00000000;

class KString : std::string
{
public:
    // By rules of five : Constructor
    KString();
    KString(const char* cStr);

    // By rules of five : Destructor
    ~KString() noexcept {};

    // By rules of five : Copy constructor
    explicit KString( const KString& other ) : orgStr(other.orgStr), kLength(other.kLength) {};
    explicit KString( const std::string& other );
    explicit KString( const char*& other );

    // By rules of five : Move constructor
    KString( KString&& other ) noexcept : orgStr(std::move(other.orgStr)), kLength(other.kLength) {};
    KString( std::string&& other ) noexcept;
    KString( char*&& other ) noexcept;

    // By rules of five : Copy assignment
    KString& operator = ( const KString& other );
    KString& operator = ( const std::string& other );
    KString& operator = ( const char*& other );

    // By rules of five : Move assignment
    KString& operator = ( const KString&& other ) noexcept;
    KString& operator = ( const std::string&& other ) noexcept;
    KString& operator = ( const char*&& other ) noexcept;

    const char* operator [] ( const int index );
    KString&    operator += ( const char* str );
    KString&    operator += ( const KString& str );

    const std::string getString() { return this->orgStr; };

    // UTF8 문자열이 총 몇 글자인지 세는 함수
    size_t getWordsLength() noexcept;

    // 기존 아스키 문자는 1칸, 한글은 2칸을 차지한다고 가정했을 때 ( ex: D2Coding 폰트 )
    // 터미널에서 차지하는 글자 칸 수
    size_t getWordsWidth() noexcept;

    // override std::string c_str()
    const char* c_str() noexcept;

private:
    size_t getWordsLength( const std::string& str ) noexcept;

    std::string orgStr;
    size_t kLength;
};
