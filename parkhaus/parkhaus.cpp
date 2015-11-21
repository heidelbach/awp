#include "parkhaus.h"

#include "color.h"
#include "parkplatz.h"

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <climits>
#include <iostream>

static bool terminate_programm = false;

#ifdef __linux__
#include <signal.h>

static void signalhandler(int signal)
{
  switch (signal)
  {
  case SIGINT:
    terminate_programm = true;
    break;
  default:
    printf("Caught signal %d\n", signal);
  }
}

static void register_signalhandler()
{
  struct sigaction action;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  action.sa_handler = signalhandler;
  if (sigaction(SIGINT, &action, NULL))
    fprintf(stderr, "Error installing handler for SIGINT\n");
  if (sigaction(SIGUSR1, &action, NULL))
    fprintf(stderr, "Error installing handler for SIGUSR1\n");
  if (sigaction(SIGUSR2, &action, NULL))
    fprintf(stderr, "Error installing handler for SIGUSR2\n");
  if (sigaction(SIGTERM, &action, NULL))
    fprintf(stderr, "Error installing handler for SIGTERM\n");
}
#endif

struct parkslotEntry
{
  Parkplatz *space;
  unsigned int tick;
  struct parkslotEntry *prev, *next;
};

static struct parkslotEntry *addSpace(Parkplatz *const p,
    unsigned int const tick, struct parkslotEntry *list);

static struct parkslotEntry *checkForFree(struct parkslotEntry *list,
    int &delta, Parkhaus *const phaus);

static bool getAutomode();

static unsigned int getHeight(bool const automode);

static unsigned int getWidth(bool const automode);

static void sleep(unsigned int);

static void printMenu();

static unsigned int getSlot(Parkplatz *const nextFree = NULL);

int main()
{
#ifdef __linux__
  register_signalhandler();
#endif
  unsigned int height, width;
  bool const automode = getAutomode();
  height = getHeight(automode);
  width = getWidth(automode);
  Parkhaus *phaus = new Parkhaus(height, width);
  struct parkslotEntry* list = 0;
  int delta = 0;

  if (automode)
  {
    phaus->print();
    while (phaus->hasFreeSpace() && !terminate_programm)
    {
      list = addSpace(phaus->getFreeSpace(), rand() % (height * width * 2 / 3),
          list);
      phaus->print();
      sleep(rand() & 0x7);
      list = checkForFree(list, delta, phaus);
    }
    phaus->print();
    sleep(200);
  }
  else
  {
    int action = -1;
    phaus->print();
    while (!terminate_programm)
    {
      int num;
      Parkplatz *p;
      Parkplatz *nextFree;
      if (action != 0)
        printMenu();
      terminate_programm = scanf("%c", (char *)(&action)) < 0;
      switch (action)
      {
        case 'l':
        case 'L':
          num = getSlot();
          p = phaus->search(num);
          if (!p->free())
            phaus->freeSpace(p);
          break;
        case 'e':
        case 'E':
          getchar(); // remove "old" buffered newline
          nextFree = phaus->getFreeSpace(false);
          num = getSlot(nextFree);
          p = phaus->search(num);
          if (p->free())
          {
            p->occupy();
            phaus->removeFromFree(p);
          }
          break;
        case 'r':
        case 'R':
          num = getSlot();
          p = phaus->search(num);
          if (p->free())
          {
            p->reserve();
            phaus->removeFromFree(p);
          }
          break;
        case 'q':
        case 'Q':
          terminate_programm = true;
          break;
        case 't':
        case 'T':
          num = getSlot();
          p = phaus->search(num);
          if (p->reserved())
            p->occupy();
          break;
        default:
          if (action > 0x3f)
          {
            action = -1;
            fprintf(stderr, "%c: Ungueltige Auswahl\n", action);
          }
          else
          {
            action = 0;
            continue;
          }
      }
      if (action > 0)
        action = 0;
      printf("=========\n");
      phaus->print();
    }
  }
  delete(phaus);
  while (list)
  {
     struct parkslotEntry *next = list->next;
     free(list);
     list = next;
  }
  return EXIT_SUCCESS;
}

bool Parkhaus::freeSpace(Parkplatz *const p)
{

  time_t duration = time(NULL) - p->getArrival();
  std::cout << "Parkplatz " << p->getNumber() << " ist nun frei.\n"
      << "Dauer war " << duration << " Sekunden\n" << std::endl;
  p->setFree();
  addSpace(p);
  return true;
}

void Parkhaus::removeFromFree(Parkplatz *const p)
{
  if (p->free())
    return;
  freeSpaceListEntry *next = freeList;
  if (next == NULL)
    return;
  if (next->space == p)
  {
    freeSpaceListEntry *oldHead = next;
    freeList = freeList->next;
    if (freeList != NULL)
      freeList->prev = NULL;
    free(oldHead);
    return;
  }
  next = next->next;
  while (next != NULL)
  {
    if (next->space == p)
    {
      freeSpaceListEntry *after = next->next;
      freeSpaceListEntry *before = next->prev;
      if (after)
        after->prev = before;
      before->next = after;
      free(next);
      return;
    }
    next = next->next;
  }
}

Parkplatz *Parkhaus::getFreeSpace(bool markOccupied)
{
  if (!freeList)
    return NULL;
  Parkplatz *ret = freeList->space;
  if (!markOccupied)
    return ret;
  ret->occupy();
  if (!freeList->next)
  {
    free(freeList);
    freeList = NULL;
  }
  else
  {
    freeList = freeList->next;
    free(freeList->prev);
    freeList->prev = NULL;
  }
  return ret;
}

bool Parkhaus::hasFreeSpace()
{
  return freeList != NULL;
}

void Parkhaus::print()
{
  if (terminate_programm)
    return;
  for (unsigned int i = _height; i < UINT_MAX; --i)
  {
    for (unsigned int j = 0; j < _spacePerHeight; ++j)
    {
      if (i == _height)
      {
        setBGBlack();
        setFGGray();
        if (j == _spacePerHeight / 2)
          std::cout << " ";
        if (j)
          std::cout << "-";
        if (j < 9)
          std::cout << "-";
        std::cout << j + 1;
        std::cout << "-";

        if (j == _spacePerHeight / 2 - 1)
          std::cout << "    ";
        if (j == _spacePerHeight - 1)
          std::cout << " ";
        resetColors();
      }
      else
      {
        setFGBlack();
        setBGBlack();
        std::cout << " ";
        resetColors();
        if (spaces[i][j]->free())
        {
          if (freeList && freeList->space == spaces[i][j])
          {
            setBGYellow();
            setFGYellow();
            std::cout << "X";
          }
          else if (spaces[i][j]->free())
          {
            setBGGreen();
            setFGGreen();
            std::cout << "O";

          }
        }
        else if (spaces[i][j]->reserved())
        {
          setBGBlue();
          setFGBlue();
          std::cout << "R";
        }
        else
        {
          setBGRed();
          setFGRed();
          std::cout << "-";
        }
        resetColors();
        setFGBlack();
        setBGBlack();
        std::cout << " ";
        resetColors();

        if (j == _spacePerHeight  / 2 - 1)
        {
          setFGBlack();
          setBGBlack();
          std::cout << "  ";
          resetColors();
          if (freeList)
          {
            unsigned int h = freeList->space->getHeight();
            if (h == i)
            {
              setBGBlack();
              setFGColor(DARK_GREEN);
              std::cout << freeList->space->getDirection();
            }
            else if (h > i)
            {
              setBGBlack();
              setFGColor(DARK_GREEN);
              std::cout << "^";
            }
            else
            {
              setFGBlack();
              setBGBlack();
              std::cout << " ";
            }
          }
          else
          {
            setBGBlack();
            if (i == 0)
            {
              setFGRed();
              std::cout << "X";
            }
            else
            {
              setFGBlack();
              std::cout << " ";
            }
          }
          setFGBlack();
          setBGBlack();
          std::cout << "   ";
          resetColors();
        }
        else
        {
          setBGBlack();
          std::cout << " ";
          resetColors();
        }
      }
    }
    resetColors();
    std::cout << std::endl;
    if (i != _height)
    {
      // numeric line
      setBGBlack();
      setFGColor(GRAY);
      for (unsigned int j = 0; j < _spacePerHeight; ++j)
      {
        unsigned int number = spaces[i][j]->getNumber();
        if (number < 10)
          std::cout << " ";
        std::cout << number;
        if (number < 100)
          std::cout << " ";
        std::cout << " ";
        if (j == _spacePerHeight / 2 - 1)
        {
          resetColors();
          setBGBlack();
          setFGGray();
          std::cout << " " << i;
          resetColors();
          setBGBlack();
          setFGColor(GRAY);
          if (i < 10)
            std::cout << " ";
          std::cout << "  ";
        }
      }
      resetColors();
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

Parkplatz *Parkhaus::search(unsigned int const number)
{
  if (number == 0)
    return NULL;
  unsigned int i = number - 1;
  unsigned int h = i / _spacePerHeight;
  unsigned int w = i % _spacePerHeight;
  return spaces[h][w];
}

static struct parkslotEntry *addSpace(Parkplatz *const p,
    unsigned int const tick, struct parkslotEntry *list)
{
  std::cout << "Parkplatz " << p->getNumber() << " ist nun belegt.\n"
      << std::endl;
  if (list == NULL)
  {
    list = (struct parkslotEntry *) malloc(sizeof(struct parkslotEntry));
    list->prev = NULL;
    list->next = NULL;
    list->tick = tick;
    list->space = p;
  }
  else
  {
    struct parkslotEntry *listPtr = list;
    while (listPtr->tick < tick)
    {
    if (listPtr->next == NULL)
      {
        listPtr->next = (struct parkslotEntry *) malloc(sizeof(
            struct parkslotEntry));
        listPtr->next->prev = listPtr;
        listPtr->next->next = NULL;
        listPtr->next->space = p;
        listPtr->next->tick = tick;
        return list;
      }
      else
        listPtr = listPtr->next;
    }
    struct parkslotEntry *prev = listPtr->prev;
    listPtr->prev = (struct parkslotEntry *) malloc(sizeof(
        struct parkslotEntry));
    listPtr->prev->next = listPtr;
    listPtr->prev->prev = prev;
    if (prev)
      prev->next = listPtr->prev;
    else
      list = listPtr->prev;
      listPtr->prev->space = p;
      listPtr->prev->tick = tick;
  }
  return list;
}

static struct parkslotEntry *checkForFree(struct parkslotEntry *list,
    int &delta, Parkhaus *phaus)
{
  if (terminate_programm)
    return NULL;
  if (list)
    ++delta;
  while (--list->tick <= 0)
  {
    phaus->freeSpace(list->space);
    phaus->print();
    sleep(3);
    if (!list->next)
    {
      free(list);
      list = 0;
    }
    else
    {
      list = list->next;
      free(list->prev);
      list->prev = 0;
      if (delta)
      {
        struct parkslotEntry* listPtr = list;
        while (listPtr)
        {
          listPtr->tick -= delta;
          listPtr = listPtr->next;
        }
      }
    }
    delta = 0;
  }
  return list;
}

static bool getAutomode()
{
  char automode;
  std::cout << "Automode (Y|n): ";
  std::cin >> automode;
  if (automode == 'n')
    return false;
  return true;
}

static unsigned int getHeight(bool const automode)
{
  if (terminate_programm)
    return 0;
  unsigned int height;
  std::cout << "Bitte Hoehe eingeben: ";
  int read = scanf("%d", &height);
  if (read < 0)
  {
    terminate_programm = true;
    return 0;
  }
  return height;
}

static unsigned int getWidth(bool const automode)
{
  if (terminate_programm)
    return 0;
  unsigned int width;
  std::cout << "Bitte Breite eingeben: ";
  int read = scanf("%u", &width);
  if (read < 0)
  {
    terminate_programm = true;
    return 0;
  }
  return width;
}

static void sleep(unsigned int seconds)
{
  if (terminate_programm)
    return;
  char syscall[200];
  int strlen;
  syscall[0] = 0;
#ifdef _WIN32
  strlen = sprintf(syscall, "timeout ");
#elif defined __linux__
  strlen = sprintf(syscall, "sleep ");
#endif
  strlen += sprintf(&syscall[strlen], "%d", seconds);
#ifdef _WIN32
#elif defined __linux__
  strlen += sprintf(&syscall[strlen], " >/dev/null 2>&1");
#endif
  if (system(syscall) != 0)
  {
    printf("\rterminate_programmd\n");
    terminate_programm = true;
  }
}

static void printMenu()
{
  printf("L: Ausfahrt\n");
  printf("E: Einfahrt\n");
  printf("R: Reservierung\n");
  printf("T: Reservierung belegen\n");
  printf("Q: Beenden\n");
  printf("Ihre Wahl: ");
}

static unsigned int getSlot(Parkplatz *nextFree)
{
  unsigned int number;
  if (nextFree != NULL)
  {
    char buffer;
    printf("Bitte Nummer eingeben (%d): ", nextFree->getNumber());
    buffer = getchar();
    if (buffer == '\n')
      return nextFree->getNumber();
    ungetc(buffer, stdin);
    scanf("%u", &number);
  }
  else
  {
    printf("Bitte Nummer eingeben: ");
    scanf("%u", &number);
  }
  return number;
}
