/**
 * Ersteller: Johannes Heidelbach
 *
 * implementiert I/O-Operationen
 */

#include "io.h"

#include <stdio.h>

signed int getInt()
{
	signed int i;
	scanf("%d", &i);
	return i;
}

double getFloat()
{
  double d;
  scanf("%lf", &d);
  return d;
}

