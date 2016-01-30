CXX=g++
LN=g++
CXX_FLAGS=-std=c++11 -g
LN_FLAGS=-lpthread

all: multithreaded_sort

clean:
	rm -rf *.o 

multithreaded_sort: main.o io.o numbers.o sort.o
	$(LN) $^ $(CXX_FLAGS) $(LN_FLAGS) -o $@

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

%.o: %.cpp %.h
	$(CXX) $(CXX_FLAGS) -c -o $@ $<
