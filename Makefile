CXX=clang++
CXXFLAGS=-Wall -g -std=c++11

SOURCE=main.cpp

OBJECT=main.o

all: ground2

ground2: $(OBJECT)
	$(CXX) $(OBJECT) -o ground2

clean: rm -f ground2 $(OBJECT)
