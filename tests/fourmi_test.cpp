#include <stdexcept>
#include <iostream>
#include <vector>

#include <projet_fourmi/outils.hpp>
#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/team_consts.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <lib/doctest.h>

using namespace std;

TEST_SUITE_BEGIN("Fourmi");
TEST_CASE("Fourmi constructor"){
    Caste cast = Caste::guerrier;
    Fourmi f = Fourmi(Coord(1, 2), 1, NUMBER_OF_COLONIES-1, cast);
    CHECK(f.getCoords() == Coord(1, 2));
    CHECK(f.getNum() == 1);
    CHECK_FALSE(f.porteSucre());
    CHECK(f.isAlive() == true);
    CHECK(f.getColony() == NUMBER_OF_COLONIES-1);
    CHECK(f.getCaste() == cast);
}

TEST_CASE("Verify colony"){
    CHECK_THROWS_AS(verify_colony(NUMBER_OF_COLONIES), invalid_argument);
    CHECK_THROWS_AS(verify_colony(-1), invalid_argument);
    verify_colony(NUMBER_OF_COLONIES-1);
    verify_colony(0);
}

TEST_CASE("Fourmi functions"){
    Caste cast = Caste::ouvrier;
    Fourmi f = Fourmi(Coord(1, 2), 1, NUMBER_OF_COLONIES-1, cast);
    Fourmi f1 = Fourmi(Coord(2, 2), 2, NUMBER_OF_COLONIES-1, Caste::guerrier);

    CHECK_THROWS_AS(f1.prendSucre(), runtime_error);

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
    Caste cast = Caste::guerrier;
    vector<Coord> coords = vector<Coord>{{
        Coord(1, 2),
        Coord(11, 4),
        Coord(5, 8),
        Coord(5, 6)
    }};
    EnsCoord ens = EnsCoord(coords);
    vector<Fourmi> list_fourmis = createListFourmis(ens, NUMBER_OF_COLONIES-1, cast);
    CHECK(list_fourmis.size() == coords.size());
    for(int i = 0; i < coords.size(); i++){
        CHECK(list_fourmis[i].getCoords() == coords[i]);
        CHECK(list_fourmis[i].getCoords() == ens.getCoords()[i]);
        CHECK(list_fourmis[i].getNum() == i);
        CHECK(list_fourmis[i].getColony() == NUMBER_OF_COLONIES-1);
        CHECK(list_fourmis[i].getCaste() == cast);
    }
}

TEST_CASE("Fourmi killFourmi"){
    Caste cast = Caste::guerrier;
    Fourmi f1 = Fourmi(Coord(1, 3), 1, 1, cast);

    CHECK(f1.isAlive());

    f1.killFourmi();

    CHECK_FALSE(f1.isAlive());

    CHECK_THROWS_AS_MESSAGE(f1.killFourmi(), runtime_error, "The ant is already dead!");
}

TEST_CASE("Fourmi operator=="){
    Fourmi f1 = Fourmi(Coord(1, 3), 1, 1, Caste::ouvrier);
    Fourmi f2 = Fourmi(Coord(1, 3), 2, 1, Caste::ouvrier);
    Fourmi f5 = Fourmi(Coord(1, 3), 1, 1, Caste::guerrier);
    Fourmi f3 = Fourmi(Coord(2, 4), 1, 1, Caste::ouvrier);

    Fourmi f4 = Fourmi(Coord(1, 3), 1, 1, Caste::ouvrier);

    CHECK(f1 == f4);
    CHECK_FALSE(f1 == f2);
    CHECK_FALSE(f1 == f3);
    CHECK_FALSE(f2 == f3);

    CHECK_FALSE(f1 == f5);

    CHECK_FALSE(f1 != f4);
    CHECK(f1 != f2);
    CHECK(f1 != f3);
    CHECK(f2 != f3);

    f4.prendSucre();
    CHECK_FALSE(f1 == f4);

}

TEST_CASE("Fourmi getCastByNumber"){
    CHECK_THROWS_AS(getCastByNumber(-1), invalid_argument);
    CHECK_THROWS_AS(getCastByNumber(3), invalid_argument);
    CHECK(getCastByNumber(0) == Caste::ouvrier);
    CHECK(getCastByNumber(1) == Caste::guerrier);
    CHECK(getCastByNumber(2) == Caste::reproductrice);
}

TEST_CASE("Fourmi canCaste"){
    Caste c_ouvr = Caste::ouvrier;
    Caste c_guer = Caste::guerrier;
    Caste c_rep = Caste::reproductrice;

    CHECK(canCasteTakeSugar(c_ouvr));
    CHECK(canCasteTakeSugar(c_rep));
    CHECK_FALSE(canCasteTakeSugar(c_guer));

    CHECK(canCasteBattle(c_guer));
    CHECK_FALSE(canCasteBattle(c_ouvr));
    CHECK_FALSE(canCasteBattle(c_rep));
}

TEST_SUITE_END();