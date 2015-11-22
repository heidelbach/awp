#ifndef PARKPLATZ_H
#define PARKPLATZ_H

#include <ctime>

class Parkplatz
{
private:
  unsigned int const _number, _height, _prio;
  time_t _arrival;
  unsigned short _state;
  char const _dir;

public:
  Parkplatz(unsigned int prio, unsigned int number, char dir,
      unsigned int height) :
      _number(number),  _height(height), _prio(prio), _dir(dir)
  {
    _arrival = 0;
    _state = 0; // FREE
  }

  ~Parkplatz()
  {
  }

  unsigned int getNumber()
  {
    return _number;
  }

  bool free()
  {
    return _state == 0;
  }

  bool reserved()
  {
    return _state == 2;
  }

  char getDirection()
  {
    return _dir;
  }

  unsigned int getHeight()
  {
    return _height;
  }

  unsigned int getPrio()
  {
    return _prio;
  }

  void occupy()
  {
    if (_state == 0)
      _arrival = time(NULL);
    _state = 1;
  }

  void reserve()
  {
    _arrival = time(NULL);
    _state = 2;
  }

  bool setFree()
  {
    _state = 0;
    return true;
  }

  time_t getArrival()
  {
    return _arrival;
  }
};
#endif
