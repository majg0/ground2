CXX=clang++
CXXFLAGS=-Wall -g -std=c++14
LDFLAGS=
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=ground2

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) 

%.o: %.c %.h
	$(CXX) $(CCFLAGS) -c $<

%.o: %.c
	$(CXX) $(CCFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
