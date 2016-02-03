#include "io.h"
#include "numbers.h"
#include "disable_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *leseEin(int *noten, int anzahl);

float berechneDurchschnitt(int *noten, int anzahl);

int main(int argc, char **argv)
{
  int anzahl = 0;
  int *noten = NULL;
  char print_histogram = 0;

  while (--argc > 0)
  {
    char *arg = *++argv;
    if (strcmp("-h", arg) == 0)
      print_histogram = 1;
    else
      fprintf(stderr,"Unknown arg %s\n", arg);
  }

  disable_buffering();
  while ( 1 )
  {
    noten = leseEin(noten, anzahl);
    if ( noten[anzahl++] == 0 )
    {
      break;
    }
  }
  enable_buffering();
  if (anzahl == 1)
  {
    printf("\nKeine Eingabe\n");
  }
  else
  {
    printf("\nDer Schnitt ist %4.2f\n", berechneDurchschnitt(noten, anzahl - 1));

    if (print_histogram)
      display_array(anzahl - 1, noten);
  }
}

int *leseEin(int *noten, int anzahl)
{
  int note = -1;
  while (1)
  {
    if (note == -1)
      printf("Bitte Note eingeben, 0 zum Beenden: ");
    int read = getchar();
    if (read == 0x7f)
    {
      note = -1;
      printf("\r\033[K");
      continue;
    }
    if (read < 0x20)
    {
      if (read == '\n')
      {
        if (note >= 0)
          break;
      }
      else
      {
        continue;
      }
    }
    
    if (read < '0' || read > '6' || note != -1)
    {
      if (note < 0)
      {
        printf("\r\033[K\033[31mUngueltige Eingabe %c\033[0m\n", read);
      }
      else
      {
        printf("\r\033[K\033[31mUngueltige Eingabe %d%c\033[0m\n", note, read);
        note = -1;
      }
    }
    else
    {
      note = read - '0';
    }
  }
  
  // Anfordern neuen Speichers und uebertragen von altem
  {
    int *noten_neu = (int *)malloc(sizeof(int) * (anzahl + 1));
    if (noten == NULL ) // oder anzahl == 0
    {
      noten = noten_neu;
    }
    else
    {
      memcpy(noten_neu, noten, sizeof(int) * anzahl);
      free(noten);
      noten = noten_neu;
    }

    // alternativ 
    /*
    if (noten == NULL)
      noten = malloc(sizeof(int) * (anzahl + 1));
    else
      noten = realloc(noten, sizeof(int) * (anzahl + 1));
    */
  }

  noten[anzahl] = note;
  return noten;
}

float berechneDurchschnitt(int *noten, int anzahl)
{
  int summe = 0;
  for (int i = 0; i < anzahl; ++i)
    summe += noten[i];
  return (float) summe / anzahl;
}
