#include "circle.h"
#include "shape2d.h"

#include <cmath>
#include <cstdlib>

Circle::Circle() : Shape2D()
{
}

Circle::~Circle()
{
}

float Circle::area()
{
	return r * r * M_PI;
}

float Circle::perimeter()
{
	return 2 * r * M_PI;
}

unsigned int Circle::edges()
{
	return 1;
}

const char *Circle::toString()
{
	return "Circle";
}

void Circle::setEdge(unsigned int id, float length)
{
	if (id == 0)
		r = length;
	else
		abort();
}

const char *Circle::edgeName(unsigned int id)
{
	if (id == 0)
		return "radius";
	else
		abort();
}

