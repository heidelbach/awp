#include "shape2d.h"
#include "triangle.h"

#include <cstdlib>
#include <cmath>

Triangle::Triangle() : Shape2D()
{
}

Triangle::~Triangle()
{
}

float Triangle::area()
{
	float s =  (a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

float Triangle::perimeter()
{
	return a + b + c;
}

unsigned int Triangle::edges()
{
	return 3;
}

const char *Triangle::toString()
{
	return "Triangle";
}

void Triangle::setEdge(unsigned int id, float length)
{
	if (id == 0)
		a = length;
	else if (id == 1)
		b = length;
	else if (id == 2)
		c = length;
	else 
		abort();
}

const char *Triangle::edgeName(unsigned int id)
{
	if (id == 0)
		return "edge A";
	else if (id == 1)
		return "edge B";
	else if (id == 2)
		return "edge C";
	else 
		abort();
}

