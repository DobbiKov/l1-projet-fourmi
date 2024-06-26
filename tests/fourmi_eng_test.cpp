#include <stdexcept>
#include <iostream>
#include <vector>

#include <projet_fourmi/outils.hpp>
#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/fourmi_eng.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/team_consts.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <lib/doctest.h>

using namespace std;

TEST_SUITE_BEGIN("FourmiEng");

TEST_CASE("FourmiEng constructor"){
    vector<Coord> coords{{
        Coord(6, 6),
        Coord(5, 6),
        Coord(4, 6),
        Coord(3, 6),
        Coord(3, 7),
        Coord(3, 8),
        Coord(3, 9),
        Coord(4, 9),
        Coord(5, 9),
        Coord(6, 9),
        Coord(6, 8),
        Coord(6, 7),
    }};
    EnsCoord fourmis_coords = EnsCoord(coords);
    vector<Fourmi> fourmis{{}};

    Caste cast = Caste::ouvrier;
    for(int i = 0; i < fourmis_coords.taille(); i++){
        Fourmi f = Fourmi(fourmis_coords.ieme(i), i, NUMBER_OF_COLONIES-1, cast);
        fourmis.push_back(f);
    }
    Fourmi f_1 = Fourmi(Coord(1, 1), 12, 1, Caste::guerrier);
    Fourmi f_1_2 = Fourmi(Coord(1, 2), 13, 1, Caste::reproductrice);
    fourmis.push_back(f_1);
    fourmis.push_back(f_1_2);
    FourmiEng f_eng = FourmiEng(fourmis);

    CHECK(f_eng.getNumberOfFourmi() == fourmis.size());
    CHECK(f_eng.getNumberOfFourmi() == 14);
    CHECK(f_eng.getNumberOfFourmiInColony(NUMBER_OF_COLONIES-1) == 12);
    CHECK(f_eng.getNumberOfFourmiInColony(0) == 0);
    CHECK(f_eng.getNumberOfFourmiInColony(1) == 2);

    vector<Fourmi> loaded_fourmis = f_eng.getFourmis();
    CHECK(loaded_fourmis.size() == fourmis.size());
    for(int i = 0; i < loaded_fourmis.size(); i++){
        CHECK(loaded_fourmis[i] == fourmis[i]);
    }

    CHECK_THROWS_AS_MESSAGE(f_eng.loadFourmi(15), invalid_argument, "Index is out of range of the list of fourmis!");


    Fourmi f = f_eng.loadFourmi(1);
    CHECK(f == fourmis[1]);
    
    Fourmi f2 = f_eng.loadFourmi(f);
    CHECK(f2 == f);

    CHECK(f.getCoords() == Coord(5, 6));
    f.deplace(Coord(5, 7));
    f_eng.changeFourmi(f);
    Fourmi f_new = f_eng.loadFourmi(1);
    CHECK(f_new.getCoords() == Coord(5, 7));
}

TEST_CASE("FourmiEng loadFourmi"){
    vector<Coord> coords{{
        Coord(6, 6),
        Coord(5, 6),
        Coord(4, 6),
        Coord(3, 6),
        Coord(3, 7),
        Coord(3, 8),
        Coord(3, 9),
        Coord(4, 9),
        Coord(5, 9),
        Coord(6, 9),
        Coord(6, 8),
        Coord(6, 7),
    }};
    EnsCoord fourmis_coords = EnsCoord(coords);
    vector<Fourmi> fourmis{{}};

    Caste cast = Caste::ouvrier;
    for(int i = 0; i < fourmis_coords.taille(); i++){
        Fourmi f = Fourmi(fourmis_coords.ieme(i), i, NUMBER_OF_COLONIES-1, cast);
        fourmis.push_back(f);
    }

    FourmiEng f_eng = FourmiEng(fourmis);

    CHECK_THROWS_AS_MESSAGE(f_eng.loadFourmi(12), invalid_argument, "Index is out of range of the list of fourmis!");

    Fourmi fake_f = Fourmi(Coord(1, 3), 13, NUMBER_OF_COLONIES-1, cast);
    CHECK_THROWS_AS_MESSAGE(f_eng.loadFourmi(fake_f), invalid_argument, "The ant isn't in list of fourmis!");

    Fourmi f = f_eng.loadFourmi(1);
    CHECK(f == fourmis[1]);
    
    Fourmi f2 = f_eng.loadFourmi(f);
    CHECK(f2 == f);

    CHECK(f.getCoords() == Coord(5, 6));
    f.deplace(Coord(5, 7));
    f_eng.changeFourmi(f);
    Fourmi f_new = f_eng.loadFourmi(1);
    CHECK(f_new.getCoords() == Coord(5, 7));
}

TEST_CASE("FourmiEng killFourmi, birthFourmi"){
    vector<Coord> coords{{
        Coord(6, 6),
        Coord(5, 6),
        Coord(4, 6),
        Coord(3, 6),
        Coord(3, 7),
        Coord(3, 8),
        Coord(3, 9),
        Coord(4, 9),
        Coord(5, 9),
        Coord(6, 9),
        Coord(6, 8),
        Coord(6, 7),
    }};
    EnsCoord fourmis_coords = EnsCoord(coords);
    vector<Fourmi> fourmis{{}};

    Caste cast = Caste::ouvrier;
    for(int i = 0; i < fourmis_coords.taille(); i++){
        Fourmi f = Fourmi(fourmis_coords.ieme(i), i, NUMBER_OF_COLONIES-1, cast);
        fourmis.push_back(f);
    }

    FourmiEng f_eng = FourmiEng(fourmis);

    Fourmi f = f_eng.loadFourmi(2);
    CHECK(f == fourmis[2]);
    f_eng.killFourmi(f);
    CHECK_FALSE(f_eng.loadFourmi(2).isAlive());
    CHECK(f_eng.getNumberOfFourmi() == 11);

    Fourmi n_f = Fourmi(Coord(1, 13), 0, NUMBER_OF_COLONIES-1, cast);
    Fourmi new_fourmi = f_eng.birthFourmi(n_f);
    CHECK(new_fourmi.getNum() == 12);
    CHECK(f_eng.getFourmis().size() == 13);
    CHECK(f_eng.getNumberOfFourmi() == 12);
    CHECK(new_fourmi.getColony() == NUMBER_OF_COLONIES-1);
    CHECK(new_fourmi.getCaste() == cast);
}

TEST_SUITE_END();