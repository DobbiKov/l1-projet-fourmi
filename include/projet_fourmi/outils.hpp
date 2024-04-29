#ifndef OUTILS_HPP
#define OUTILS_HPP

#include <vector>
#include <projet_fourmi/coord.hpp>
using namespace std;

bool operator==(vector<Coord> v1, vector<Coord> v2);
bool operator!=(vector<Coord> v1, vector<Coord> v2);

/// @brief returns absolute value
/// @param num 
/// @return absolute value of the given number
float val_abs(float num);

/// @brief compares to float numbers
/// @param a num 1
/// @param b num 2
/// @return returns true if two numbers are approximately equal, false in the other case
bool float_equal(float a, float b);

vector<int> sort_by(vector<int> ints, vector<float> floats);

#endif