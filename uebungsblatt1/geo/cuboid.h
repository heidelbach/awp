#ifndef __CUBOID_H__
#define __CUBOID_H__

#include "shape3d.h"

class Cuboid : public Shape3D
{
private:
	float a, b, c;

public:
	Cuboid();

	virtual ~Cuboid();

	virtual float area();
	
	virtual float volume();

	virtual const char *edgeName(unsigned int);

	virtual unsigned int edges();

	virtual const char *toString();

	virtual void setEdge(unsigned int, float);
};

#endif
