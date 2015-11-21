
#ifndef __SHAPE_H__
#define __SHAPE_H__

class Shape
{
public:
	Shape();

	virtual ~Shape();

	virtual float area() = 0;

	virtual unsigned int edges() = 0;

	virtual void setEdge(unsigned int id, float length) = 0;

	virtual const char *toString() = 0;

	virtual const char *edgeName(unsigned int id) = 0;

	virtual bool is2D() = 0;
};
#endif
