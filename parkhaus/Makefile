.PHONY: all clean

all: parkhaus

clean:
	rm -rf *.o

parkhaus: parkhaus.o parkplatz.h color.o
	g++ -Wall -Werror -std=c++11 -o $@ $^

color.o: color.cpp color.h
	g++ -Wall -Werror -std=c++11 -c -o $@ $<

parkhaus.o: parkhaus.cpp parkhaus.h color.h parkplatz.h
	g++ -Wall -Werror -std=c++11 -c -o $@ $<
