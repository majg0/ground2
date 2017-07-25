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
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

clean:
	find . -name "*.o" -type f -delete
	rm $(TARGET)
