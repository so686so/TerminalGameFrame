#pragma once
#include <string>

#ifndef BOOL_DEF
#define BOOL_DEF
typedef int		    BOOL;
#endif
typedef std::string TILE;
typedef char        UTF8CHAR[4];

#define TRUE        1
#define FALSE       0

#define UNUSED(x)   (void)(x)

#define DEFINE      constexpr auto
