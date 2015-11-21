#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include "shape3d.h"

class Cylinder : public Shape3D
{
private:
	float r, h;

public:
	Cylinder();

	virtual ~Cylinder();

	virtual float area();
	
	virtual float volume();

	virtual const char *edgeName(unsigned int);

	virtual unsigned int edges();

	virtual const char *toString();

	virtual void setEdge(unsigned int, float);
};

#endif
