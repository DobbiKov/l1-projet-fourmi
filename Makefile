CXX=clang++
PROJECT_BASE=projet_fourmi
CXXFLAGS=-std=c++11 -Wall --include-directory=include --include-directory=./
EXEC_FILES=test
INCLUDE=include/projet_fourmi
SRC=src
TEST=tests


coord.o: $(SRC)/coord.cpp $(INCLUDE)/coord.hpp
	$(CXX) $(CXXFLAGS) -c $<
outils.o: $(SRC)/outils.cpp $(INCLUDE)/outils.hpp $(INCLUDE)/coord.hpp
	$(CXX) $(CXXFLAGS) -c $<
test.o: $(TEST)/test.cpp $(INCLUDE)/outils.hpp $(INCLUDE)/coord.hpp
	$(CXX) $(CXXFLAGS) -c $<


test: test.o coord.o outils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o $(EXEC_FILES) include/projet_fourmi/*.gch