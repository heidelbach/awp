#include "rectangle.h"
#include "shape2d.h"

#include <cstdlib>

Rectangle::Rectangle() : Shape2D()
{
}

Rectangle::~Rectangle()
{
}

float Rectangle::area()
{
	return a * b;
}

float Rectangle::perimeter()
{
	return 2 * (a + b);
}

unsigned int Rectangle::edges()
{
	return 2;
}

const char *Rectangle::toString()
{
	return "Rectangle";
}

void Rectangle::setEdge(unsigned int id, float length)
{
	if (id == 0)
		a = length;
	else if (id == 1)
		b = length;
	else 
		abort();
}

const char *Rectangle::edgeName(unsigned int id)
{
	if (id == 0)
		return "width";
	else if (id == 1)
		return "height";
	else 
		abort();
}

