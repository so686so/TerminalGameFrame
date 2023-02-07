#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

#include "Types.h"

DEFINE CMD_MAX_LEN        = 256;
DEFINE CONSOLE_MIN_WIDTH  = 40;
DEFINE CONSOLE_MIN_HEIGHT = 10;

std::string getStringResultFromCommand( const std::string&& cmd ) noexcept;

BOOL getConsoleSize( int& width, int& height );
int  getConsoleWidth();
int  getConsoleHeight();

void resizeConsole( const int width, const int height );