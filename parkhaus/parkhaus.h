#ifndef PARKHAUS_H
#define PARKHAUS_H

#include "parkplatz.h"

#include <cstdlib>

struct freeSpaceListEntry
{
  Parkplatz *space;
  struct freeSpaceListEntry *prev, *next;
};

class Parkhaus
{
private:
  unsigned int const _height;
  unsigned int const _spacePerHeight;

  Parkplatz ***spaces;
  struct freeSpaceListEntry *freeList;

  void addSpace(Parkplatz *const p)
  {
    if (freeList == NULL)
    {
      freeList = (struct freeSpaceListEntry *) malloc(sizeof(
          struct freeSpaceListEntry));
      freeList->prev = NULL;
      freeList->next = NULL;
      freeList->space = p;
    }
    else
    {
      struct freeSpaceListEntry *list = freeList;
      while (list->space->getPrio() > p->getPrio())
      {
        if (list->next == NULL)
        {
          list->next = (struct freeSpaceListEntry *) malloc(sizeof(
              struct freeSpaceListEntry));
          list->next->prev = list;
          list->next->next = NULL;
          list->next->space = p;
          return;
        }
        else
          list = list->next;
      }
      struct freeSpaceListEntry *prev = list->prev;
      list->prev = (struct freeSpaceListEntry *) malloc(sizeof(
          struct freeSpaceListEntry));
      list->prev->next = list;
      list->prev->prev = prev;
      if (prev)
        prev->next = list->prev;
      else
        freeList = list->prev;

      list->prev->space = p;
    }
  }


public:

  Parkhaus(unsigned int height, unsigned int spacePerHeight) : _height(height),
      _spacePerHeight(spacePerHeight)
  {
    freeList = NULL;
    spaces = (Parkplatz ***) malloc(_height * sizeof (Parkplatz **));
    for (unsigned int i = 0; i < height; ++i)
    {
      spaces[i] = (Parkplatz **) malloc(_spacePerHeight * sizeof (Parkplatz *));
      int const numberForHeight = i * _spacePerHeight;
      for (unsigned int j = 0; j < _spacePerHeight; ++j)
      {
        int prio = _spacePerHeight / 2 - j;
        char dir;
        if (prio <= 0)
        {
          prio = numberForHeight + 2 * -prio + 1;
          dir = '>';
        }
        else
        {
          prio = numberForHeight + 2 * prio;
          dir = '<';
        }
        spaces[i][j] = new Parkplatz(prio, numberForHeight + j + 1, dir, i);
        addSpace(spaces[i][j]);
      }
    }
  }

  ~Parkhaus()
  {
    for (unsigned int i = 0; i < _height; ++i)
    {
      for (unsigned int j = 0; j < _spacePerHeight; ++j)
        delete(spaces[i][j]);
      free(spaces[i]);
    }
    free(spaces);
    spaces = NULL;
    freeList = NULL;
  }

  void print();

  bool hasFreeSpace();

  bool freeSpace(Parkplatz *const);

  Parkplatz *search(unsigned int const number);

  Parkplatz *getFreeSpace(bool markOccupied = true);

  void removeFromFree(Parkplatz *const p);
};
#endif
