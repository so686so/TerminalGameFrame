#include "KString.h"

// By rules of five : Constructor
KString::KString()
    : orgStr("")
    , kLength(0)
{
    //
}

KString::KString(const char* cStr)
    : orgStr(cStr)
{
    kLength = this->getWordsLength();
}

// By rules of five : Copy constructor
KString::KString( const std::string& other )
    : orgStr(other)
{
    kLength = this->getWordsLength();
}

KString::KString( const char*& other )
    : orgStr(other)
{
    kLength = this->getWordsLength();
}

// By rules of five : Move constructor
KString::KString( std::string&& other ) noexcept
    : orgStr(std::move(other))
{
    kLength = this->getWordsLength();
}

KString::KString( char*&& other ) noexcept
    : orgStr(std::move(other))
{
    kLength = this->getWordsLength();
}

// By rules of five : Copy assignment
KString& KString::operator = ( const KString& other )
{
    if( &other == this ) return *this;

    orgStr  = other.orgStr;
    kLength = other.kLength;

    return *this;
}

KString& KString::operator = ( const std::string& other )
{
    orgStr  = other;
    kLength = this->getWordsLength();

    return *this;
}

KString& KString::operator = ( const char*& other )
{
    orgStr  = other;
    kLength = this->getWordsLength();

    return *this;
}

// By rules of five : Move assignment
KString& KString::operator = ( const KString&& other ) noexcept
{
    if( &other == this ) return *this;

    orgStr  = std::move( other.orgStr );
    kLength = other.kLength;

    return *this;
}

KString& KString::operator = ( const std::string&& other ) noexcept
{
    orgStr  = std::move( other );
    kLength = this->getWordsLength();

    return *this;
}

KString& KString::operator = ( const char*&& other ) noexcept
{
    orgStr  = std::move( other );
    kLength = this->getWordsLength();

    return *this;
}

const char* KString::operator [] ( const int index )
{
    size_t idx = static_cast<size_t>(index);

    if( idx > this->kLength - 1 ) {
        std::cout << "[Error] KString operator[] : out of range. " << idx << " > " << this->kLength - 1 << std::endl;
        exit(-1);
    }

    size_t len  = 0;
    size_t i    = 0;

    while( i < this->orgStr.size() ) {
        int char_size = 0;

        if      ( ( this->orgStr[i] & CHAR_SIZE_4_CHCK_FLAG ) == CHAR_SIZE_4_COMP_FLAG ) char_size += 4;
        else if ( ( this->orgStr[i] & CHAR_SIZE_3_CHCK_FLAG ) == CHAR_SIZE_3_COMP_FLAG ) char_size += 3;
        else if ( ( this->orgStr[i] & CHAR_SIZE_2_CHCK_FLAG ) == CHAR_SIZE_2_COMP_FLAG ) char_size += 2;
        else if ( ( this->orgStr[i] & CHAR_SIZE_1_CHCK_FLAG ) == CHAR_SIZE_1_COMP_FLAG ) char_size += 1;
        else    char_size += 1;

        if( idx == len ) {
            std::string subs = orgStr.substr(i, char_size);
            return subs.c_str();
        };

        i += char_size;
        len++;
    }

    return "";
}

KString& KString::operator += ( const char* str )
{
    this->orgStr += str;
    this->kLength = this->getWordsLength();
    return *this;
}

KString& KString::operator += ( const KString& str )
{
    this->orgStr += str.orgStr;
    this->kLength = this->getWordsLength();
    return *this;
}

const char* KString::c_str() noexcept
{
    return this->orgStr.c_str();
}
