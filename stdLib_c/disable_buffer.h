#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void disable_buffering()
{
  struct termios tio;
  tcgetattr(STDIN_FILENO, &tio);
  tio.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

void enable_buffering()
{
  struct termios tio;
  tcgetattr(STDIN_FILENO, &tio);
  tio.c_lflag |= ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}
