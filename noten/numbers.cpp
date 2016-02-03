/**
 * Ersteller: Johannes Heidelbach
 *
 * implementiert numerische Umwandlungsoperationen
 */

#include "numbers.h"
#include "io.h"
#include "sort.h"
#include "node.hpp"

#include <cstdlib>

#define DISPLAY_ARRAY_MAX_COL 60

signed int toInt(char const *s)
{
	signed int ret = 0;

	if (s == NULL)
		return 0;
	
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

signed int cmpIntVoid(void *aPtr, void *bPtr)
{
	signed int a = *((signed int *) aPtr);
	signed int b = *((signed int *) bPtr);
	return a - b;
}

signed int cmpInt(signed int const *aPtr, signed int const *bPtr)
{
	return *aPtr - *bPtr;
}

void sortInt(unsigned int count, signed int *const array)
{
  tsort(array, sizeof(int), count, cmpIntVoid);
}

void print_array(unsigned int const count, signed int *const numbers)
{
	for (unsigned int i = 0; i < count; ++i)
	{
		printNumf("%4d", numbers[i]);
		printText(" ");
	}
	printText("\n");
}

void display_array(unsigned int const count, signed int *const numbers)
{
  unsigned int maxCount, minCount;
  bool first = true;
  // use bintree to count
  Node<signed int> *tree = Node<signed int>::create(numbers, cmpInt);
  
  for (unsigned int i = 1; i < count; ++i)
  {
    tree->add(numbers + i);
  }

  // determine min max
  tree->iterator_generate();
  while ( 1 )
  {
    iterator_data<signed int> *next = tree->iterator_next();
    if (next == NULL)
      break;
    unsigned int count = next->_count;
    delete next;
    if (first)
    {
      first = false;
      maxCount = minCount = count;
    }
    else
    {
      if (maxCount < count)
        maxCount = count;
      if (minCount > count)
        minCount = count;
    }
  }

  maxCount -= minCount;

  // format and print output
  tree->iterator_generate();
  while ( 1 )
  {
    iterator_data<signed int> *next = tree->iterator_next();
    if (next == NULL)
      break;
    signed int const value = *(next->_value);
    unsigned int count_rel = maxCount == 0 ? 0 : (next->_count - minCount)
        * DISPLAY_ARRAY_MAX_COL / maxCount;

    delete next;
    
    printf("%3d| #", value);
    while (count_rel-- > 0)
      printf("#");
    printf("\n");
  }
  tree->free();
}
