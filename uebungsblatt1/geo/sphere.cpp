#include "shape3d.h"
#include "sphere.h"

#include <cmath>
#include <cstdlib>

Sphere::Sphere() : Shape3D()
{
}

Sphere::~Sphere()
{
}

float Sphere::area()
{
	return r * r * 4 * M_PI;
}

float Sphere::volume()
{
	return r * r * r * 4 * M_PI / 3;
}

unsigned int Sphere::edges()
{
	return 1;
}

const char *Sphere::toString()
{
	return "Sphere";
}

void Sphere::setEdge(unsigned int id, float length)
{
	if (id == 0)
		r = length;
	else
		abort();
}

const char *Sphere::edgeName(unsigned int id)
{
	if (id == 0)
		return "radius";
	else
		abort();
}

