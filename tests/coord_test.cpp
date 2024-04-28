#include <stdexcept>
#include <iostream>
#include <vector>

#include <projet_fourmi/outils.hpp>
#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/consts.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <lib/doctest.h>

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
TEST_SUITE_END();

TEST_SUITE_BEGIN("outils");
TEST_CASE("operateur d'egalite de vector de coords"){
    CHECK(vector<Coord>{{}} == vector<Coord>{{}});
    CHECK(vector<Coord>{{Coord(5, 4), Coord(3, 4)}} == vector<Coord>{{Coord(5, 4), Coord(3, 4)}});
    CHECK(vector<Coord>{{Coord(5, 4), Coord(3, 4)}} != vector<Coord>{{Coord(5, 4), Coord(2, 4)}});
    CHECK(vector<Coord>{{Coord(3, 4), Coord(5, 4)}} != vector<Coord>{{Coord(5, 4), Coord(3, 4)}});

    CHECK(val_abs(-2) == 2);
    CHECK(val_abs(2) == 2);

    CHECK(float_equal(0.587, 0.587));
    CHECK_FALSE(float_equal(0.587, 0.586));
    // Coord(5, 4)
}
TEST_SUITE_END();