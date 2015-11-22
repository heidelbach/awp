
#ifndef __RECT_H__
#define __RECT_H__

#include "shape2d.h"

class Rectangle : public Shape2D
{
private:
	float a, b;

public:
	Rectangle();

	~Rectangle();

	virtual float area();

	virtual float perimeter();

	virtual unsigned int edges();

	virtual void setEdge(unsigned int id, float length);

	virtual const char *toString();

	virtual const char *edgeName(unsigned int id);
};

#endif
