#include "io.h"
#include "disable_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *leseEin(int *noten, int anzahl);

float berechneDurchschnitt(int *noten, int anzahl);

int main()
{
  int anzahl = 0;
  int *noten = NULL;

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
  }
}

int *leseEin(int *noten, int anzahl)
{
  int note;
  while (1)
  {
    printf("Bitte Note eingeben, 0 zum Beenden: ");
    int read = getchar();
    if (read < 0x20)
    {
      continue;
    }
    else if (read < '0' || read > '6')
    {
      printf("\r\033[K\033[31mUngueltige Eingabe %c\033[0m\n", read);
    }
    else
    {
      note = read - '0';
      printf("\r\n");
      break;
    }
  }
  
  // Anfordern neuen Speichers und uebertragen von altem
  {
    int *noten_neu = malloc(sizeof(int) * (anzahl + 1));
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
