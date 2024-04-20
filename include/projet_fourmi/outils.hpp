#ifndef OUTILS_HPP
#define OUTILS_HPP

#include <vector>
#include <projet_fourmi/coord.hpp>
using namespace std;

bool operator==(vector<Coord> v1, vector<Coord> v2);
bool operator!=(vector<Coord> v1, vector<Coord> v2);

float val_abs(float num);

bool float_equal(float a, float b);

#endif