/*
 * Ersteller: Johannes Heidelbach
 * Parkplatzverwaltung
 * kann mehrere Plaetze (einzeln oder als Bereich angegeben) gleichzeitig behandeln
 */

#include "color.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define SIZE 90
#define DIGITS 2

enum SlotState
{
	FREE, OCCUPIED, RESERVED
};

char *const state_desc[3] = { "Frei", "Belegt", "Reserviert" };
unsigned int const state_color[6] = { GREEN, RED, BLUE, BLACK, BLACK, GRAY };

void showMenue(unsigned int *lkw_p);

void display(unsigned int *lkw_p);

int main()
{
	unsigned int lkw_p[SIZE] = {0};

	while (1)
	{
		display(lkw_p);
		showMenue(lkw_p);
	}
}

unsigned int *addEntry(unsigned int **numbers, unsigned int *idx, unsigned int *size, bool range)
{
	// eingelesener Wert liegt in *idx;
	// *numbers[0] gibt aktuelle Zahl der Elemente an
	if (!range)
	{
		int sizeCurrent = ++(*numbers[0]);
		if (sizeCurrent == *size - 1)
		{
			// we need more memory
			unsigned int *numbersNew;
			unsigned int *numbersOld;
			numbersOld = *numbers;
			numbersNew = (unsigned int *) malloc(sizeof(unsigned int) * (2 * *size + 1));
			memcpy(numbersNew, numbersOld, sizeof(unsigned int) * *size);
			*numbers = numbersNew;
			free(numbersOld);
			*size *= 2;
			idx = &numbersNew[numbersNew[0]];
		}
		*idx -= 1;
		if (*idx < 0 || *idx >= SIZE)
		{
			printf("%3d ist ungueltig", *idx);
			free(*numbers);
			*numbers = NULL;
			return NULL;
		}
		*(++idx) = 0;
		return idx;
	}
	else
	{
		unsigned int start = *(idx - 1);
		unsigned int end = *idx;
		if (start < 1 || start > 50)
		{
			printf("Fehler: Startplatz %3d ist ungueltig.\n", start);
			free(*numbers);
			*numbers = NULL;
			return NULL;
		}
		if (end < 1 || end > SIZE || end < start)
		{
			printf("Fehler: Endplatz %3d ist ungueltig.\n", end);
			free(*numbers);
			*numbers = NULL;
			return NULL;
		}
		unsigned int delta = end - start + 1;
		unsigned int rem = *size - **numbers;
		if (rem < delta)
		{
			// we need more memory
			unsigned int *numbersNew;
			unsigned int *numbersOld;
			numbersOld = *numbers;
			numbersNew = (unsigned int *) malloc(sizeof(unsigned int) * (2 * *size + 1));
			*size *= 2;
			memcpy(numbersNew, numbersOld, sizeof(unsigned int) * *size);
			*numbers = numbersNew;
			free(numbersOld);
			idx = addEntry(numbers, &numbersNew[numbersNew[0]  + 2], size, range);
			return idx;
		}
		--idx;
		--end;
		--start;
		while (start <= end)
		{
			*idx = start;
			++idx;
			++start;
		}
		*idx = 0;
		(*numbers)[0] += delta;
		return idx;
	}
}

unsigned int *parseNumbers()
{
	unsigned int size = 16;
	unsigned int *numbers = (unsigned int *) malloc(sizeof(unsigned int) * (size + 1));
	unsigned int *idx = numbers;
	char *const buffer = (char *) malloc(sizeof(char) * 1024);
	char *bufferIdx = buffer;
	bool range = false;
	*idx = 0;
	*(++idx) = 0;

	printf("Bitte geben Sie die Nummer ein\n");
	printf("Sie koenen mehrere Nummern mit , trennen\n");
	printf("oder Bereiche als von:bis eingeben\n");
	scanf("%1023s", buffer);
	printf("\n");

	while (*bufferIdx && idx)
	{
		switch (*bufferIdx)
		{
		case ':':
			if (range)
			{
				printf("Fehler: Invalid format.\n");
				free(numbers);
				free(buffer);
				return NULL;
			}
			range = true;
			++idx;
			*idx = 0;
			break;

		case ',':
			idx = addEntry(&numbers, idx, &size, range);
			if (range)
			{
				range = false;
			}
			break;
		
		default:
			if (*bufferIdx >= '0' && *bufferIdx <= '9')
			{
				*idx = *idx * 10 + *bufferIdx - '0';
			}
			else
			{
				printf("Fehler: Invalid character.\n");
				free(numbers);
				free(buffer);
				return NULL;
			}
		}
		++bufferIdx;
	}
	addEntry(&numbers, idx, &size, range);
	free(buffer);
	return numbers;
}

void freeSpace(unsigned int *lkw_p)
{
	unsigned int *numbers = parseNumbers();
	if (numbers == NULL)
		return;
	unsigned int count = *numbers;
	for (unsigned int i = 0; i < count;)
	{
		unsigned int pos = numbers[++i];
		if (lkw_p[pos] == FREE)
		{
			 printf("Fehler: Platz %3d ist bereits freigegeben.\n", pos + 1);
		}
		else
		{
			lkw_p[pos] = FREE;
			printf("Platz %3d ist freigegeben.\n", pos + 1);
		}
	}
	free(numbers);
}

void occupySpace(unsigned int *lkw_p)
{
	unsigned int *numbers = parseNumbers();
	if (numbers == NULL)
		return;
	unsigned int count = *numbers;
	for (unsigned int i = 0; i < count;)
	{
		unsigned int pos = numbers[++i];
		if (lkw_p[pos] != FREE)
		{
			 printf("Fehler: Platz %3d ist bereits %s.\n", pos + 1, lkw_p[pos] == OCCUPIED ? "belegt" : "reserviert");
		}
		else
		{
			lkw_p[pos] = OCCUPIED;
			printf("Platz %3d ist nun belegt.\n", pos + 1);
		}
	}
	free(numbers);
}

void reserveSpace(unsigned int *lkw_p)
{
	unsigned int *numbers = parseNumbers();
	if (numbers == NULL)
		return;
	unsigned int count = *numbers;
	for (unsigned int i = 0; i < count;)
	{
		unsigned int pos = numbers[++i];
		if (lkw_p[pos] != FREE)
		{
			 printf("Fehler: Platz %3d ist bereits %s.\n", pos + 1, lkw_p[pos] == OCCUPIED ? "belegt" : "reserviert");
		}
		else
		{
			lkw_p[pos] = RESERVED;
			printf("Platz %3d ist nun reserviert.\n", pos + 1);
		}
	}
	free(numbers);
}

void showMenue(unsigned int *lkw_p)
{
	char buffer = 0;
	while (buffer < 0x60)
	{
		if (buffer == 0)
		{
			printf("Um einen Platz freizugeben, druecken Sie bitte F.\n");
			printf("Um einen Platz zu reservieren, druecken Sie bitte R.\n");
			printf("Um einen Platz zu belegen, druecken Sie bitte B.\n");
		}
		scanf("%c", &buffer);
		printf("\n");

		switch (buffer)
		{
			case 'f':
			case 'F':
				freeSpace(lkw_p);
				break;
			
			case 'b':
			case 'B':
				occupySpace(lkw_p);
				break;

			case 'r':
			case 'R':
				reserveSpace(lkw_p);
				break;
			
			default:
				if (buffer < 0x60);
				else 
				{
					printf("Ungueltige Eingabe %c\n", buffer);
					buffer = 0;
				}
		}
		
	}
}

void display(unsigned int *lkw_p)
{
	printf("\n");
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		unsigned int slot = lkw_p[i];
		setFGColor(GRAY);
		setBGColor(BLACK);
		printf("%3d ", i + 1);
		setFGColor(state_color[slot]);
		setBGColor(state_color[slot + 3]);
		printf("%-10s", state_desc[slot]);
		resetColors();
		if (i % 3 == 2)
			printf("\n");
		else
			printf("\t\t");
			
	}
	printf("\n\n");
}
