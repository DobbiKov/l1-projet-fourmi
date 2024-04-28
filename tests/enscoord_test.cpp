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

TEST_SUITE_BEGIN("EnsCoord");
TEST_CASE("EnsCoord constructor"){
    EnsCoord n1 = EnsCoord();
    CHECK(n1.taille() == 0);
    CHECK(n1.getCoords() == vector<Coord>());
    CHECK(n1.estVide());
    CHECK_THROWS_AS(n1.ieme(0), invalid_argument);

    EnsCoord n2 = EnsCoord(vector<Coord>{{
        Coord(5, 4), Coord(3, 4)
    }});
    CHECK(n2.taille() == 2);
    CHECK(n2.getCoords() == vector<Coord>{{Coord(5, 4), Coord(3, 4)}});
    CHECK_FALSE(n2.estVide());
    CHECK(n2.ieme(0) == Coord(5, 4));
}

TEST_CASE("EnsCoord ajoute"){
    EnsCoord n1 = EnsCoord();
    n1.ajoute(Coord(1, 2));
    CHECK(n1.taille() == 1);
    CHECK(n1.getCoords() == vector<Coord>{{ Coord(1, 2) }});
    CHECK_FALSE(n1.estVide());
    CHECK(n1.ieme(0) == Coord(1, 2));

    EnsCoord n2 = EnsCoord(vector<Coord>{{
        Coord(5, 4), Coord(3, 4)
    }});
    CHECK(n2.taille() == 2);
    CHECK_FALSE(n2.estVide());
    CHECK(n2.ieme(0) == Coord(5, 4));
    CHECK(n2.ieme(1) == Coord(3, 4));
    CHECK_THROWS_AS(n2.ieme(2), invalid_argument);
    CHECK_THROWS_AS(n2.ieme(-1), invalid_argument);

    n2.ajoute(Coord(11, 3));
    CHECK(n2.taille() == 3);
    CHECK(n2.ieme(0) == Coord(5, 4));
    CHECK(n2.ieme(1) == Coord(3, 4));
    CHECK(n2.ieme(2) == Coord(11, 3));
    CHECK(n2.getCoords() == vector<Coord>{{Coord(5, 4), Coord(3, 4), Coord(11, 3)}});
}

TEST_CASE("EnsCoord contient"){
    EnsCoord n1 = EnsCoord();
    CHECK_FALSE(n1.contient( Coord(5, 4) ));

    EnsCoord n2 = EnsCoord(vector<Coord>{{
        Coord(5, 4), Coord(3, 4)
    }});
    CHECK(n2.contient( Coord(5, 4) ));
    CHECK(n2.contient( Coord(3, 4) ));
}

TEST_CASE("EnsCoord supprime"){
    EnsCoord n1 = EnsCoord();
    CHECK_THROWS_AS(n1.supprime( Coord(3, 4) ), invalid_argument);

    EnsCoord n2 = EnsCoord(vector<Coord>{{
        Coord(5, 4), Coord(3, 4)
    }});
    CHECK_THROWS_AS(n1.supprime( Coord(4, 4) ), invalid_argument);
    CHECK(n2.getCoords() == vector<Coord>{{Coord(5, 4), Coord(3, 4)}});
    
    n2.supprime( Coord(5, 4) );
    CHECK( n2.taille() == 1 );
    CHECK(n2.getCoords() == vector<Coord>{{Coord(3, 4)}});
    CHECK_THROWS_AS(n2.ieme(1), invalid_argument);
    CHECK(n2.ieme(0) == Coord(3, 4));

    n2.supprime( Coord(3, 4) );
    CHECK( n2.taille() == 0 );
    CHECK(n2.getCoords() == vector<Coord>());
}

TEST_SUITE_END();