#include "cuboid.h"
#include "shape3d.h"

#include <cstdlib>

Cuboid::Cuboid() : Shape3D()
{
}

Cuboid::~Cuboid()
{
}

float Cuboid::area()
{
	return 2 * ((a * b) + (a * c) + (b * c));
}

float Cuboid::volume()
{
	return a * b * c;
}

unsigned int Cuboid::edges()
{
	return 3;
}

const char *Cuboid::toString()
{
	return "Cuboid";
}

void Cuboid::setEdge(unsigned int id, float length)
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

const char *Cuboid::edgeName(unsigned int id)
{
	if (id == 0)
		return "length";
	else if (id == 1)
		return "width";
	else if (id == 2)
		return "height";
	else
		abort();
}

