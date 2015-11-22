#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "shape3d.h"

class Sphere : public Shape3D
{
private:
	float r;

public:
	Sphere();

	virtual ~Sphere();

	virtual float area();
	
	virtual float volume();

	virtual const char *edgeName(unsigned int);

	virtual unsigned int edges();

	virtual const char *toString();

	virtual void setEdge(unsigned int, float);
};

#endif
