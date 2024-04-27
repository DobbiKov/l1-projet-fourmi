#include <stdexcept>
#include <iostream>
#include <vector>

#include <projet_fourmi/outils.hpp>
#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/grille.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <lib/doctest.h>

using namespace std;

TEST_SUITE_BEGIN("Fourmi");
TEST_CASE("Fourmi constructor"){
    Fourmi f = Fourmi(Coord(1, 2), 1);
    CHECK(f.getCoords() == Coord(1, 2));
    CHECK(f.getNum() == 1);
    CHECK_FALSE(f.porteSucre());
    CHECK(f.isAlive() == true);
}

TEST_CASE("Fourmi functions"){
    Fourmi f = Fourmi(Coord(1, 2), 1);

    f.prendSucre();
    CHECK(f.porteSucre() == true);
    CHECK_THROWS_AS(f.prendSucre(), runtime_error);
    f.poseSucre();
    CHECK_FALSE(f.porteSucre());
    CHECK_THROWS_AS(f.poseSucre(), runtime_error);
    CHECK_THROWS_AS(f.deplace(Coord(3, 9)), invalid_argument);
    f.deplace(Coord(1, 3));
    CHECK(f.getCoords() == Coord(1, 3));
}

TEST_CASE("Fourmi fourmi list"){
    vector<Coord> coords = vector<Coord>{{
        Coord(1, 2),
        Coord(11, 4),
        Coord(5, 8),
        Coord(5, 6)
    }};
    EnsCoord ens = EnsCoord(coords);
    vector<Fourmi> list_fourmis = createListFourmis(ens);
    CHECK(list_fourmis.size() == coords.size());
    for(int i = 0; i < coords.size(); i++){
        CHECK(list_fourmis[i].getCoords() == coords[i]);
        CHECK(list_fourmis[i].getCoords() == ens.getCoords()[i]);
        CHECK(list_fourmis[i].getNum() == i);
    }
}

TEST_SUITE_END();