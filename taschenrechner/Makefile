all: taschenrechner

clean:
	rm -rf taschenrechner *.o

taschenrechner: main.o io.o
	g++ -o $@ $^ 

io.o: io.cpp io.h
	g++ -c -o $@ $<

main.o: main.cpp math.h
	g++ -c -o $@ $<

