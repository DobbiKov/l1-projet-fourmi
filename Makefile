CXX=clang++
CXXFLAGS=-std=c++11 -Wall
EXEC_FILES=main

all: 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

coord.o: coord.hpp


main: main.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o $(EXEC_FILES)