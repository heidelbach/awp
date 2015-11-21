TARGET=
CXX=g++
CXX_FLAGS=-std=c++11 -g -o
LN_FLAGS=
OBJS=weichnachtsbaum.o

TARGET=weihnachtsbaum

weihnachtsbaum: weihnachtsbaum.o
	$(CXX) $(LN_FLAGS) $(CXX_FLAGS) $@ $^

clean:
	rm -f $(TARGET) *.o

%.o: %.cpp
	$(CXX) -c $(CXX_FLAGS) $@ $^
