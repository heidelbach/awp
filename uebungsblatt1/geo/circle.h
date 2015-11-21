
#ifndef __CIRC_H__
#define __CIRC_H__

#include "shape2d.h"

class Circle : public Shape2D {
private:
	float r;

public:
	Circle();

	~Circle();

	virtual float area();

	virtual float perimeter();

	virtual unsigned int edges();

	virtual void setEdge(unsigned int id, float length);

	virtual const char *toString();

	virtual const char *edgeName(unsigned int id);
};

#endif
