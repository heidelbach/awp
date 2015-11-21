#include "cylinder.h"
#include "shape3d.h"

#include <cmath>
#include <cstdlib>

Cylinder::Cylinder() : Shape3D()
{
}

Cylinder::~Cylinder()
{
}

float Cylinder::area()
{
	return r * r * M_PI;
}

float Cylinder::volume()
{
	return 2 * r * h * M_PI;
}

unsigned int Cylinder::edges()
{
	return 2;
}

const char *Cylinder::toString()
{
	return "Cylinder";
}

void Cylinder::setEdge(unsigned int id, float length)
{
	if (id == 0)
		r = length;
	else if (id == 1)
		h = length;
	else
		abort();
}

const char *Cylinder::edgeName(unsigned int id)
{
	if (id == 0)
		return "radius";
	else if (id == 1)
		return "height";
	else
		abort();
}

