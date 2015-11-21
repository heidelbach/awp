/**
 * Ersteller: Johannes Heidelbach
 *
 * implementiert numerische Umwandlungsoperationen
 */

#include "numbers.h"
#include "io.h"
#include "sort.h"

#include <stdlib.h>


signed int toInt(char const *s)
{
	signed int ret = 0;
	char first;

	if (s == NULL)
		return 0;
	first = *s;
	while(++s)
	{
		char digit = *s;
		if (digit < '0' || digit > '9')
		{
			// ungueltiges Zeichen
			return 0;
		}
	}
	return ret;
}

signed int cmp(void *aPtr, void *bPtr)
{
	signed int a = *((signed int *) aPtr);
	signed int b = *((signed int *) bPtr);
	return a - b;
}
void sortInt(unsigned int const count, signed int *const numbers)
{
	sort((void *) numbers, sizeof(signed int), count, cmp);
}

void const print(unsigned int const count, signed int *const numbers)
{
	for (unsigned int i = 0; i < count; ++i)
	{
		printNumf("%4d", numbers[i]);
		printText(" ");
	}
	printText("\n");
}
