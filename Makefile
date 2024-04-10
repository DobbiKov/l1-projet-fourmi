CXX=clang++
CXXFLAGS=-std=c++11 -Wall
EXEC_FILES=test

all: 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

coord.o: coord.hpp
test.o: coord.hpp


test: test.o coord.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o $(EXEC_FILES)