#include "circle.h"
#include "cuboid.h"
#include "cylinder.h"
#include "rectangle.h"
#include "shape.h"
#include "shape2d.h"
#include "shape3d.h"
#include "sphere.h"
#include "triangle.h"

#include <cstdio>
#include <cstdlib>

enum ShapeIds {
	rectID = 1, 
	triangleID,
	circleID,
	cuboidID,
	sphereID,
	cylinderID
};

static Shape *selectShape()
{
	start: 
	printf("Please enter\n");
	printf("%2d: Rectangle\n", rectID);
	printf("%2d: Triangle\n", triangleID);
	printf("%2d: Circle\n", circleID);
	printf("%2d: Cuboid\n", cuboidID);
	printf("%2d: Sphere\n", sphereID);
	printf("%2d: Cylinder\n", cylinderID);
	printf("to select the shape: ");
	const signed int c = getchar();	
	if (c == -1) {
		printf("\n");
		return NULL;
	}
	if (c >= '0' && c <= '9') {
		const int i = c - '0';
		switch(i) {
			case rectID:
				return new Rectangle();
			case circleID:
				return new Circle();
			case triangleID:
				return new Triangle();
			case cuboidID:
				return new Cuboid();
			case cylinderID:
				return new Cylinder();
			case sphereID:
				return new Sphere();
		}
	}
	printf("\n\nSorry wrong number, please try again\n");
	goto start;
}

static void getDimension(Shape *shape)
{
	const unsigned int edges = shape->edges();
	printf("\nSelected: %s\n", shape->toString());
	for (unsigned int edge = 0; edge < edges; ++edge) {
		printf("\rPlease enter the %s: ", shape->edgeName(edge));
		float length;
		int read = scanf("%f", &length);
		if (read < 0) {
			abort();
		} else if (read == 0) {
			--edge;
			continue;
		   }
		shape->setEdge(edge, length);
	}
}

static void calculate(Shape2D *shape)
{
	printf("area:       %7f\n", shape->area());
	printf("perimeter:  %7f\n", shape->perimeter());
}

static void calculate(Shape3D *shape)
{
	printf("area:       %7f\n", shape->area());
	printf("volume:     %7f\n", shape->volume());
}

static void calculate(Shape *shape)
{
	if (shape->is2D())
		calculate((Shape2D *) shape);
	else
		calculate((Shape3D *) shape);
}

int main(int argc, char **argv)
{
	Shape *shape = selectShape();
	if (shape == NULL)
		return 0;
	getDimension(shape);
	calculate(shape);
	return 0;
}
