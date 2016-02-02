CC=gcc
LD=$(CC)
CC_FLAGS=-Wall -pedantic

all: noten

clean:
	rm -f *.o

noten: noten.o numbers.o io.o
	$(LD) $(LD_FLAGS) -o $@ $^

numbers.o: numbers.c numbers.h io.h
	$(CC) $(CC_FLAGS) -c -o $@ $<

io.o: io.c io.h
	$(CC) $(CC_FLAGS) -c -o $@ $<

noten.o: noten.c io.h
	$(CC) $(CC_FLAGS) -c -o $@ $<
