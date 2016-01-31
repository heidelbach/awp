CC=gcc
CXX=g++
CC_FLAGS=-Wall -pedantic -std=gnu11
CXX_FLAGS=-Wall -pedantic -std=c++11

all: non_buffered_input

clean:
	rm -f *.o

non_buffered_input: non_buffered_input.o
	$(CC) $(LD_FLAGS) -o $@ $^

non_buffered_input.o: non_buffered_input.c ../stdLib_c/disable_buffer.h
	$(CC) $(CC_FLAGS) -c -o $@ $<
