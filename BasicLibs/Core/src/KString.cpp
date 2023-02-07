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

size_t KString::getWordsLength() noexcept
{
    return this->getWordsLength(orgStr);
}

size_t KString::getWordsLength( const std::string& str ) noexcept
{
    size_t len  = 0;
    size_t i    = 0;

    while( i < str.size() ) {
        int char_size = 0;

        if      ( ( str[i] & CHAR_SIZE_4_CHCK_FLAG ) == CHAR_SIZE_4_COMP_FLAG ) char_size += 4;
        else if ( ( str[i] & CHAR_SIZE_3_CHCK_FLAG ) == CHAR_SIZE_3_COMP_FLAG ) char_size += 3;
        else if ( ( str[i] & CHAR_SIZE_2_CHCK_FLAG ) == CHAR_SIZE_2_COMP_FLAG ) char_size += 2;
        else if ( ( str[i] & CHAR_SIZE_1_CHCK_FLAG ) == CHAR_SIZE_1_COMP_FLAG ) char_size += 1;
        else    char_size += 1;

        i += char_size;
        len++;
    }

    return len;
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

        // if( idx == len ) return orgStr.substr(i, char_size);
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

static BOOL checkWordInTileSize1( std::string word )
{
    for( auto& tile : TILE_1 ) {
        if( word == tile.second ) return TRUE;
    }
    return FALSE;
}

size_t KString::getWordsWidth() noexcept
{
    size_t width = 0;
    size_t i     = 0;
    int j = 0;
    KString check {this->orgStr};

    while( i < this->orgStr.size() ) {
        int char_width = 0;
        int char_size  = 0;

        // if( checkWordInTileSize1( check[j++] ) == TRUE ) char_width += 1;
        if( ( this->orgStr[i] & CHAR_SIZE_4_CHCK_FLAG ) == CHAR_SIZE_4_COMP_FLAG ) {
            char_size  += 4;
            char_width += 2;
        }
        else if( ( this->orgStr[i] & CHAR_SIZE_3_CHCK_FLAG ) == CHAR_SIZE_3_COMP_FLAG ) {
            char_size  += 3;
            char_width += 2;
        }
        else if( ( this->orgStr[i] & CHAR_SIZE_2_CHCK_FLAG ) == CHAR_SIZE_2_COMP_FLAG ) {
            char_size  += 2;
            char_width += 2;
        }
        else if ( ( this->orgStr[i] & CHAR_SIZE_1_CHCK_FLAG ) == CHAR_SIZE_1_COMP_FLAG ) {
            char_size  += 1;
            char_width += 1;
        }
        else {
            char_size  += 1;
            char_width += 1;
        }

        std::string checkStr = check[j++];
        if( checkWordInTileSize1( checkStr ) )
            char_width = 1;

        i += char_size;
        width += char_width;
    }

    return width;
}

const char* KString::c_str() noexcept
{
    return this->orgStr.c_str();
}
