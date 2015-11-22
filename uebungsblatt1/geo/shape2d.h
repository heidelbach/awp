
#ifndef __SHAPE_2D_H__
#define __SHAPE_2D_H__

#include "shape.h"

class Shape2D : public Shape
{
public:
	Shape2D();

	virtual ~Shape2D();

	virtual float perimeter() = 0;

	virtual bool is2D();
};
#endif
