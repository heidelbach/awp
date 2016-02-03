CXX=g++
CC=$(CXX)
LD=$(CXX) -lpthread
CC_FLAGS=$(CXX_FLAGS)
CXX_FLAGS=-Wall -pedantic -std=gnu++11

all: noten

clean:
	rm -f *.o

noten: noten.o numbers.o io.o sort.o 
	$(LD) $(LD_FLAGS) -o $@ $^

node.o: node.hpp 
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

sort.o: sort.cpp sort.h
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

numbers.o: numbers.cpp numbers.h io.h sort.h node.hpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

io.o: io.c io.h
	$(CC) $(CC_FLAGS) -c -o $@ $<

noten.o: noten.c io.h numbers.h
	$(CC) $(CC_FLAGS) -c -o $@ $<
