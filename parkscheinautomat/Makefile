.PHONY: all clean

SRC_PLAIN=automat.cpp main.cpp
SRC=$(addprefix src/,$(SRC_PLAIN))
OBJS=$(patsubst src/%.cpp,bin/%.o,$(SRC))

STD=-std=c++11

CXX=g++
LN=$(CXX)
CC_FLAGS=-g -c $(STD) -o
LN_FLAGS=-g $(STD) -o

all: automat

bin/%.o: src/%.cpp src/%.h
	$(CXX) $(CC_FLAGS) $@ $<

bin/%.o: src/%.cpp 
# for main and source files not having header files
	$(CXX) $(CC_FLAGS) $@ $<

automat: $(OBJS)
	$(LN) $(LN_FLAGS) $@ $^

clean:
	rm -rf automat $(OBJS)
