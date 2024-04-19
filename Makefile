CXX=clang++
PROJECT_BASE=projet_fourmi
CXXFLAGS=-std=c++11 -Wall --include-directory=include --include-directory=./
INCLUDE_DIR=include/projet_fourmi
SRC_DIR=src
TEST_DIR=tests
BUILD_DIR=build
BIN_DIR=bin
EXEC_FILES=$(BIN_DIR)/test

$(shell mkdir -p $(BUILD_DIR))

OBJ=$(BUILD_DIR)/coord.o $(BUILD_DIR)/outils.o $(BUILD_DIR)/test.o $(BUILD_DIR)/fourmi.o $(BUILD_DIR)/place.o

# Pattern rule for compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test.o: $(TEST_DIR)/test.cpp $(INCLUDE_DIR)/outils.hpp $(INCLUDE_DIR)/coord.hpp $(INCLUDE_DIR)/fourmi.hpp $(INCLUDE_DIR)/place.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for linking
$(EXEC_FILES): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC_FILES) include/projet_fourmi/*.gch