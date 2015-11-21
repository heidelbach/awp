/*
 * Ersteller: Johannes Heidelbach
 * Windows/Linux specific functions to set colors for console
 */

#include "color.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

static HANDLE const console = GetStdHandle(STD_OUTPUT_HANDLE);
static WORD oldAttr = 0;
static bool oldAttrSet = false;

#elif defined __linux__
#include <cstdio>

#else
#error "Not recognized system"
#endif

void resetColors()
{
#ifdef _WIN32
  SetConsoleTextAttribute(console, oldAttr);
  oldAttrSet = false;
#endif
#ifdef __linux__
  printf("\033[00m");
#endif
}

void setFGColor(int colorFG)
{
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(console, &csbi);
  if (!oldAttrSet)
  {
    oldAttr = csbi.wAttributes;
    oldAttrSet = true;
  }
  WORD color = csbi.wAttributes;
  color = (color & 0xf0) | colorFG; // keep background color and set foreground
  SetConsoleTextAttribute(console, color);
#endif
#ifdef __linux__
  printf("\033[%dm", colorFG);
#endif
}

void setBGColor(int colorBG)
{
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(console, &csbi);
  if (!oldAttrSet)
  {
    oldAttr = csbi.wAttributes;
    oldAttrSet = true;
  }
  WORD color = csbi.wAttributes;
  color = (color & 0x0f) | (colorBG << 4); // keep foreground color and set background
  SetConsoleTextAttribute(console, color);
#endif
#ifdef __linux__
  printf("\033[%dm", colorBG + 10);
#endif
}
