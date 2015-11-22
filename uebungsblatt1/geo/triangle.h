
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "shape2d.h"

class Triangle : public Shape2D
{
private:
	float a, b, c;

public:
	Triangle();

	~Triangle();

	virtual float area();

	virtual float perimeter();

	virtual unsigned int edges();

	virtual void setEdge(unsigned int id, float length);

	virtual const char *toString();

	virtual const char *edgeName(unsigned int id);
};

#endif
