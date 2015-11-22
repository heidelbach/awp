CXX = g++

all: block1

clean:
	rm -rf *.o geo

geo: block1.o shape.o shape2d.o shape3d.o circle.o rectangle.o cylinder.o triangle.o cuboid.o sphere.o
	$(CXX) -o $@ $^ 

%.o: %.cpp %.h
	$(CXX) -c $<

