#include <stdexcept>
#include <iostream>

#include "coord.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

TEST_SUITE_BEGIN("Coord");

TEST_CASE("Coord constructor"){
    CHECK_THROWS_AS(Coord(TAILLEGRILLE, TAILLEGRILLE), invalid_argument);
    CHECK_THROWS_AS(Coord(TAILLEGRILLE, TAILLEGRILLE+1), invalid_argument);

    Coord c = Coord(10, 7);
    CHECK(c.getLine() == 10);
    CHECK(c.getColumn() == 7);

    CHECK(c == c);
    CHECK(Coord(10, 7) == c);
    CHECK(Coord(5, 4) == Coord(5, 4));
    CHECK_FALSE(Coord(5, 4) == Coord(6, 4));
    CHECK_FALSE(Coord(5, 4) != Coord(5, 4));
    CHECK(Coord(5, 4) != Coord(6, 4));
}
// TODO!!!!!! Test all the class EnsCoord
TEST_SUITE_END();