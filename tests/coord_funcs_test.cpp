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

TEST_SUITE_BEGIN("voisines");
TEST_CASE("voisines"){
    EnsCoord n1 = voisines(Coord(2, 1));

    CHECK(n1.getCoords() == vector<Coord>{{
        Coord(1, 0), Coord(1, 1), Coord(1, 2), Coord(2, 0), Coord(2, 2), Coord(3, 0), Coord(3, 1), Coord(3, 2)
    }});

    EnsCoord n2 = voisines(Coord(3, 4));
    CHECK(n2.getCoords() == vector<Coord>{{
        Coord(2, 3), Coord(2, 4), Coord(2, 5), Coord(3, 3), Coord(3, 5), Coord(4, 3), Coord(4, 4), Coord(4, 5)
    }});

    EnsCoord n3 = voisines(Coord(0, 0));
    CHECK(n3.getCoords() == vector<Coord>{{
        Coord(0, 1), Coord(1, 0), Coord(1, 1)
    }});

    EnsCoord n4 = voisines(Coord(TAILLEGRILLE-1, TAILLEGRILLE-1));
    CHECK(n4.getCoords() == vector<Coord>{{
        Coord(TAILLEGRILLE-2, TAILLEGRILLE-2), Coord(TAILLEGRILLE-2, TAILLEGRILLE-1), Coord(TAILLEGRILLE-1, TAILLEGRILLE-2)
    }});

    EnsCoord n5 = voisines(Coord(TAILLEGRILLE-2, TAILLEGRILLE-1));
    CHECK(n5.getCoords() == vector<Coord>{{
        Coord(TAILLEGRILLE-3, TAILLEGRILLE-2), 
        Coord(TAILLEGRILLE-3, TAILLEGRILLE-1), 
        Coord(TAILLEGRILLE-2, TAILLEGRILLE-2), 
        Coord(TAILLEGRILLE-1, TAILLEGRILLE-2), 
        Coord(TAILLEGRILLE-1, TAILLEGRILLE-1)
    }});

    EnsCoord n6 = voisines(Coord(TAILLEGRILLE-2, TAILLEGRILLE-2));
    CHECK(n6.getCoords() == vector<Coord>{{
        Coord(TAILLEGRILLE-3, TAILLEGRILLE-3), 
        Coord(TAILLEGRILLE-3, TAILLEGRILLE-2), 
        Coord(TAILLEGRILLE-3, TAILLEGRILLE-1), 
        Coord(TAILLEGRILLE-2, TAILLEGRILLE-3), 
        Coord(TAILLEGRILLE-2, TAILLEGRILLE-1), 
        Coord(TAILLEGRILLE-1, TAILLEGRILLE-3), 
        Coord(TAILLEGRILLE-1, TAILLEGRILLE-2), 
        Coord(TAILLEGRILLE-1, TAILLEGRILLE-1)
    }});

    EnsCoord n7 = voisines(Coord(0, 2));
    CHECK(n7.getCoords() == vector<Coord>{{
        Coord(0, 1), Coord(0, 3), Coord(1, 1), Coord(1, 2), Coord(1, 3)
    }});

    EnsCoord n8 = voisines(Coord(2, 0));
    CHECK(n8.getCoords() == vector<Coord>{{
        Coord(1, 0), Coord(1, 1), Coord(2, 1), Coord(3, 0), Coord(3, 1)
    }});
}
TEST_SUITE_END();

TEST_SUITE_BEGIN("choixHasard");
TEST_CASE("choixHasard"){
    EnsCoord n2 = EnsCoord(vector<Coord>{{
        Coord(5, 4), Coord(3, 4), Coord(6, 19), Coord(15, 8), Coord(1, 2)
    }});

    Coord c = n2.choixHasard();

    CHECK(n2.contient(c));

    c = n2.choixHasard();
    CHECK(n2.contient(c));

    EnsCoord n1 = EnsCoord();
    CHECK_THROWS_AS(n1.choixHasard(), runtime_error);
}
TEST_SUITE_END();