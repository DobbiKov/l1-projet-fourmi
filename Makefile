CXX=clang++
PROJECT_BASE=projet_fourmi
CXXFLAGS=-std=c++11 -Wall --include-directory=include --include-directory=./
SFML_PATH=/opt/homebrew/Cellar/sfml
SFML_FLAGS=-I$(SFML_PATH)/2.6.1/include -L$(SFML_PATH)/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE_DIR=include/projet_fourmi
SRC_DIR=src
TEST_DIR=tests
BUILD_DIR=build
BIN_DIR=bin
EXEC_FILES=$(BIN_DIR)/test $(BIN_DIR)/sfml
MAIN_HEADERS=$(INCLUDE_DIR)/consts.hpp $(INCLUDE_DIR)/team_consts.hpp $(INCLUDE_DIR)/outils.hpp $(INCLUDE_DIR)/coord.hpp $(INCLUDE_DIR)/fourmi.hpp $(INCLUDE_DIR)/fourmi_eng.hpp $(INCLUDE_DIR)/place.hpp $(INCLUDE_DIR)/grille.hpp
TEST_FILES=$(TEST_DIR)/coord_test.cpp $(TEST_DIR)/enscoord_test.cpp $(TEST_DIR)/coord_funcs_test.cpp $(TEST_DIR)/place_test.cpp $(TEST_DIR)/fourmi_test.cpp $(TEST_DIR)/grille_test.cpp $(TEST_DIR)/fourmi_eng_test.cpp

$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(BIN_DIR))

OBJ_test=$(BUILD_DIR)/coord.o $(BUILD_DIR)/outils.o $(BUILD_DIR)/test.o $(BUILD_DIR)/fourmi.o $(BUILD_DIR)/fourmi_eng.o  $(BUILD_DIR)/place.o $(BUILD_DIR)/grille.o
OBJ_sfml=$(BUILD_DIR)/coord.o $(BUILD_DIR)/outils.o $(BUILD_DIR)/sfml.o $(BUILD_DIR)/fourmi.o $(BUILD_DIR)/fourmi_eng.o $(BUILD_DIR)/place.o $(BUILD_DIR)/grille.o

# Pattern rule for compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test.o: $(TEST_DIR)/test.cpp $(TEST_FILES) $(MAIN_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/sfml.o: $(SRC_DIR)/sfml.cpp $(MAIN_HEADERS)
	$(CXX) $(CXXFLAGS) $(SFML_FLAGS) -c $< -o $@


$(BIN_DIR)/sfml: $(OBJ_sfml)
	$(CXX) $(CXXFLAGS) $(SFML_FLAGS) -o $@ $(OBJ_sfml)

$(BIN_DIR)/test: $(OBJ_test)
	$(CXX) $(CXXFLAGS) $(SFML_FLAGS) -o $@ $(OBJ_test)


clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC_FILES) include/projet_fourmi/*.gch