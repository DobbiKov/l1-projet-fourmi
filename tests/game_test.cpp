#include <stdexcept>
#include <iostream>
#include <vector>

#include <projet_fourmi/outils.hpp>
#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/game.hpp>
#include <projet_fourmi/team_consts.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <lib/doctest.h>

using namespace std;

TEST_CASE("Game Initialisation"){
    FourmiEng f_eng = initializeFourmiEng();
    Grille grille = initializeGrille(f_eng.getFourmis(), EnsCoord(vector<Coord>{{}}), NUMBER_OF_COLONIES);

    int number_of_fourmi_around_nid = 12;
    CHECK(f_eng.getFourmiTabSize() == NUMBER_OF_COLONIES*number_of_fourmi_around_nid);
    CHECK(f_eng.getNumberOfFourmi() == NUMBER_OF_COLONIES*number_of_fourmi_around_nid);

    for(int c = 0; c < NUMBER_OF_COLONIES; c++){
        CHECK(grille.getNid(c) == NIDS_COORDS[c]);
        CHECK(f_eng.getNumberOfFourmiInColony(c) == number_of_fourmi_around_nid);
    }
}