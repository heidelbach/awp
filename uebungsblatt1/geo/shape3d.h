
#ifndef __SHAPE_3D_H__
#define __SHAPE_3D_H__

#include "shape.h"

class Shape3D : public Shape
{
public:
	Shape3D();

	virtual ~Shape3D();

	virtual float volume() = 0;

	virtual bool is2D();
};
#endif
