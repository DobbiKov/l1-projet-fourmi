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

TEST_SUITE_BEGIN("Place");
TEST_CASE("Constructor"){
    Place p = Place(Coord(3, 5));
    CHECK(p.getCoords() == Coord(3, 5));
    CHECK(p.getFourmiID() == -1);
    CHECK(p.getPheroNid() == 0);
    CHECK(p.getNidColonyId() == -1);
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        CHECK(p.getPheroSugar(i) == 0);
    }

    CHECK_FALSE(p.containNid());
    CHECK_FALSE(p.containSugar());
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        CHECK_FALSE(p.estSurUnePiste(i));
    }
    CHECK(p.isEmpty());
}

TEST_CASE("Place estSurUnePiste"){
    Place p = Place(Coord(3, 5));
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        CHECK_FALSE(p.estSurUnePiste(i));
    }
    CHECK_FALSE(p.estSurUneAnyPiste());
    CHECK_THROWS_AS(p.getColoniesOfThePiste(), runtime_error);

    int colony = 1;
    p.setPheroSugar(colony);

    CHECK(p.estSurUnePiste(colony));
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        if(i == colony) continue;
        CHECK_FALSE(p.estSurUnePiste(i));
    }
    CHECK(p.estSurUneAnyPiste());
    int c_s_p = p.getColoniesOfThePiste();
    CHECK(c_s_p == colony);
}

TEST_CASE("Place sugar"){
    Place p1 = Place(Coord(11, 4));
    p1.setNid(NUMBER_OF_COLONIES-1);
    CHECK_FALSE(p1.isEmpty());
    CHECK_THROWS_AS(p1.setSugar(), runtime_error);
    
    Place p = Place(Coord(3, 5));
    CHECK_FALSE(p.containSugar());
    for(int i = 0; i < NUMBER_OF_COLONIES; i++)
        CHECK(p.getPheroSugar(i) == 0);
    CHECK(p.isEmpty());

    p.setSugar();
    CHECK_FALSE(p.isEmpty());

    Caste cast = Caste::ouvrier;

    CHECK_THROWS_AS(p1.setNid(NUMBER_OF_COLONIES-1), runtime_error);
    CHECK_THROWS_AS(p1.setSugar(), runtime_error);
    CHECK_THROWS_AS(p1.setFourmi(Fourmi(Coord(0, 0), 1, NUMBER_OF_COLONIES-1, cast)), runtime_error);

    CHECK(p.containSugar());
    p.removeSugar();
    CHECK(p.containSugar());
    int count_to_delete = (AMOUNT_OF_SUGAR_TO_SET/AMOUT_OF_SUGAR_TO_REMOVE) - 1;
    for(int i = 0; i < count_to_delete; i++){
        p.removeSugar();
        if(i < count_to_delete-1)
            CHECK(p.containSugar());
        else CHECK_FALSE(p.containSugar());
    }
    CHECK(!p.containSugar());
    CHECK_THROWS_AS(p.removeSugar(), runtime_error);
    CHECK(p.isEmpty());
}

TEST_CASE("Place phero sugar"){
    Place p = Place(Coord(3, 5));
    CHECK(p.getPheroSugar(1) == 0);
    for(int i = 0; i < NUMBER_OF_COLONIES; i++)
        CHECK_FALSE(p.estSurUnePiste(i));

    p.setPheroSugar(1);
    p.setPheroSugar(2);
    CHECK(p.getPheroSugar(1) == MAX_PHERO_SUGAR_INTENSITY);
    CHECK(p.getPheroSugar(2) == MAX_PHERO_SUGAR_INTENSITY);
    CHECK_FALSE(p.getPheroSugar(0) == MAX_PHERO_SUGAR_INTENSITY);
    CHECK_FALSE(p.estSurUnePiste(0));
    CHECK(p.estSurUnePiste(2));
    CHECK(p.estSurUnePiste(1));

    p.decreasePheroSugar();
    CHECK(p.getPheroSugar(0) == 0);
    CHECK(p.getPheroSugar(1) == MAX_PHERO_SUGAR_INTENSITY - AMOUT_OF_PHERO_SUGAR_TO_REMOVE);
    CHECK(p.getPheroSugar(2) == MAX_PHERO_SUGAR_INTENSITY - AMOUT_OF_PHERO_SUGAR_TO_REMOVE);
    CHECK(p.estSurUnePiste(1));
    CHECK(p.estSurUnePiste(2));
    while(p.getPheroSugar(1) > 0)
        p.decreasePheroSugar();
    CHECK_FALSE(p.estSurUnePiste(1));
    CHECK(p.getPheroSugar(1) == 0);
}

TEST_CASE("Place nid"){
    Place p1 = Place(Coord(11, 4));
    p1.setSugar();
    CHECK_THROWS_AS(p1.setNid(NUMBER_OF_COLONIES-1), runtime_error);

    Place p = Place(Coord(3, 5));
    CHECK_FALSE(p.containNid());
    CHECK(p.isEmpty());

    p.setNid(NUMBER_OF_COLONIES-1);
    CHECK_FALSE(p.isEmpty());
    CHECK(p.containNid());

    Caste cast = Caste::ouvrier;

    CHECK_THROWS_AS(p1.setNid(NUMBER_OF_COLONIES-1), runtime_error);
    CHECK_THROWS_AS(p1.setSugar(), runtime_error);
    CHECK_THROWS_AS(p1.setFourmi(Fourmi(Coord(0, 0), 1, NUMBER_OF_COLONIES-1, cast)), runtime_error);
}

TEST_CASE("Place phero nid"){
    Place p = Place(Coord(1, 3));
    CHECK(p.getPheroNid() == 0);
    p.setPheroNid(1);
    CHECK(p.getPheroNid() == 1);
    p.setPheroNid(0.587);
    CHECK(float_equal(p.getPheroNid(), 0.587));

    CHECK(p.getPheroNidByColony(1) == 0);
    CHECK(p.getPheroNidByColony(0) == 0);
    p.setPheroNidByColony(1, 1);
    CHECK(p.getPheroNidByColony(1) == 1);
    CHECK_FALSE(p.getPheroNidByColony(0) == 1);
    p.setPheroNidByColony(1, 0.587);
    CHECK(float_equal(p.getPheroNidByColony(1), 0.587));
    CHECK_FALSE(float_equal(p.getPheroNidByColony(0), 0.587));
}

TEST_CASE("Place fourmi"){
    Caste cast = Caste::ouvrier;
    Fourmi f = Fourmi(Coord(1, 3), 1, NUMBER_OF_COLONIES-1, cast);

    Place p1 = Place(Coord(2, 4));
    Fourmi f1 = Fourmi(Coord(2, 4), 2, NUMBER_OF_COLONIES-1, cast);
    CHECK_THROWS_AS(p1.setFourmi(f), invalid_argument);
    p1.setSugar();
    CHECK_THROWS_AS(p1.setFourmi(f1), runtime_error);

    Place p = Place(Coord(1, 3));
    CHECK(p.isEmpty());
    CHECK(p.getFourmiID() == -1);

    p.setFourmi(f);
    CHECK_FALSE(p.isEmpty());
    CHECK(p.getFourmiID() == f.getNum());

    p.removeFourmi();
    CHECK(p.isEmpty());
    CHECK_FALSE(p.getFourmiID() == f.getNum());
    CHECK(p.getFourmiID() == -1);
    CHECK_THROWS_AS(p.removeFourmi(), runtime_error);
}

TEST_CASE("Place setFourmi and nid"){
    
}

TEST_CASE("Place replaceFourmi func"){
    Caste cast = Caste::ouvrier;
    Fourmi f = Fourmi(Coord(1, 3), 1, NUMBER_OF_COLONIES-1, cast);
    Place p = Place(Coord(1, 3));


    Place p1 = Place(Coord(1, 4));
    Fourmi f1 = Fourmi(Coord(1, 4), 2, NUMBER_OF_COLONIES-1, cast);

    p.setFourmi(f);

    p1.setFourmi(f1);

    CHECK_THROWS_AS_MESSAGE(replaceFourmi(f, p, p1), invalid_argument, "The place where you want to replace the ant to isn't empty!");
    CHECK_THROWS_AS_MESSAGE(replaceFourmi(f, p1, p), invalid_argument, "The place doesn't contain this ant!");
    CHECK_THROWS_AS_MESSAGE(replaceFourmi(f, p, p), invalid_argument, "The same places were provided!");

    p1.removeFourmi();

    CHECK(p.getFourmiID() == f.getNum());
    CHECK(f.getCoords() == p.getCoords());
    CHECK(p1.getFourmiID() == -1);
    CHECK(p1.isEmpty());
    CHECK_FALSE(p.isEmpty());

    replaceFourmi(f, p, p1);

    CHECK_FALSE(p.getFourmiID() == f.getNum());
    CHECK_FALSE(f.getCoords() == p.getCoords());
    CHECK(p1.getFourmiID() == f.getNum());
    CHECK(f.getCoords() == p1.getCoords());
    CHECK(p.getFourmiID() == -1);
    CHECK(p.isEmpty());
    CHECK_FALSE(p1.isEmpty());
}

TEST_CASE("Empty places"){
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    Place p3 = Place(Coord(5, 5));
    Place p4 = Place(Coord(5, 7));
    Place p5 = Place(Coord(3, 11));
    p2.setSugar();
    p5.setNid(NUMBER_OF_COLONIES-1);
    vector<Place> places{{
        p1, p2, p3, p4, p5
    }};

    vector<Place> empty_places = emptyPlaces(places);
    CHECK(empty_places[0].getCoords() == p1.getCoords());
    CHECK(empty_places[1].getCoords() == p3.getCoords());
    CHECK(empty_places[2].getCoords() == p4.getCoords());
}
TEST_CASE("closest to the nid"){
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    p1.setPheroNid(0.8f);
    p2.setPheroNid(0.4f);
    CHECK(isTheClosestNid(p1, p2));
    CHECK_FALSE(isTheClosestNid(p2, p1));
}
TEST_CASE("farest to the nid"){
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    p1.setPheroNid(0.8f);
    p2.setPheroNid(0.4f);
    CHECK_FALSE(isTheFarestNid(p1, p2));
    CHECK(isTheFarestNid(p2, p1));
}

TEST_CASE("closest to the nid by colony"){
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    int colony = 1;
    int s_colony = 2;
    p1.setPheroNidByColony(colony, 0.8f);
    p2.setPheroNidByColony(colony, 0.4f);

    p1.setPheroNidByColony(s_colony, 0.4f);
    p2.setPheroNidByColony(s_colony, 0.8f);
    CHECK(isTheClosestNidByColony(p1, p2, colony));
    CHECK_FALSE(isTheClosestNidByColony(p2, p1, colony));

    CHECK(isTheClosestNidByColony(p2, p1, s_colony));
    CHECK_FALSE(isTheClosestNidByColony(p1, p2, s_colony));
}
TEST_CASE("farest to the nid by colony"){
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    int colony = 1;
    int s_colony = 2;
    p1.setPheroNidByColony(colony, 0.8f);
    p2.setPheroNidByColony(colony, 0.4f);

    p1.setPheroNidByColony(s_colony, 0.4f);
    p2.setPheroNidByColony(s_colony, 0.8f);

    CHECK_FALSE(isTheFarestNidByColony(p1, p2, colony));
    CHECK(isTheFarestNidByColony(p2, p1, colony));
     
    CHECK(isTheFarestNidByColony(p1, p2, s_colony));
    CHECK_FALSE(isTheFarestNidByColony(p2, p1, s_colony));
}

TEST_CASE("the closest to the nid among places"){
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    Place p3 = Place(Coord(5, 5));
    Place p4 = Place(Coord(5, 7));
    Place p5 = Place(Coord(3, 11));
    p1.setPheroNid(0.8f);
    p2.setPheroNid(0.4f);
    p3.setPheroNid(0.5f);
    p4.setPheroNid(0.9f);
    p5.setPheroNid(0.1f);
    vector<Place> places{{p1, p2, p3, p4, p5}};
    CHECK(closestPlaceToTheNid(places).getCoords() == p4.getCoords());
}

TEST_CASE("the closest to the nid among places by colony"){
    int colony = 1;
    int s_colony = 2;

    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    Place p3 = Place(Coord(5, 5));
    Place p4 = Place(Coord(5, 7));
    Place p5 = Place(Coord(3, 11));
    p1.setPheroNidByColony(colony, 0.8f);
    p2.setPheroNidByColony(colony, 0.4f);
    p3.setPheroNidByColony(colony, 0.5f);
    p4.setPheroNidByColony(colony, 0.9f);
    p5.setPheroNidByColony(colony, 0.1f);

    p1.setPheroNidByColony(s_colony, 0.8f);
    p2.setPheroNidByColony(s_colony, 0.85f);
    p3.setPheroNidByColony(s_colony, 0.5f);
    p4.setPheroNidByColony(s_colony, 0.7f);
    p5.setPheroNidByColony(s_colony, 0.1f);
    vector<Place> places{{p1, p2, p3, p4, p5}};
    CHECK(closestPlaceToTheNidByColony(places, colony).getCoords() == p4.getCoords());
    CHECK_FALSE(closestPlaceToTheNidByColony(places, s_colony).getCoords() == p4.getCoords());
    CHECK(closestPlaceToTheNidByColony(places, s_colony).getCoords() == p2.getCoords());
}

TEST_CASE("closest to the sugar"){
    int colony = 1;
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    p1.setPheroSugar(colony);
    p2.setPheroSugar(colony);
    p2.decreasePheroSugar();
    CHECK(isTheClosestSugar(p1, p2, colony));
    CHECK_FALSE(isTheClosestSugar(p2, p1, colony));
}
TEST_CASE("farest to the sugar"){
    int colony = 1;
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    p1.setPheroSugar(colony);
    p2.setPheroSugar(colony);
    p2.decreasePheroSugar();
    CHECK_FALSE(isTheFarestSugar(p1, p2, colony));
    CHECK(isTheFarestSugar(p2, p1, colony));
}

TEST_CASE("the closest to the sugar among places"){
    int colony = 1;
    Place p1 = Place(Coord(3, 5));
    Place p2 = Place(Coord(4, 5));
    Place p3 = Place(Coord(5, 5));
    Place p4 = Place(Coord(5, 7));
    Place p5 = Place(Coord(3, 11));
    p1.setPheroSugar(colony);
    p2.setPheroSugar(colony);
    p3.setPheroSugar(colony);
    p4.setPheroSugar(colony);
    p5.setPheroSugar(colony);

    p1.decreasePheroSugar();
    p1.decreasePheroSugar();

    p2.decreasePheroSugar();
    p2.decreasePheroSugar();

    p3.decreasePheroSugar();
    p3.decreasePheroSugar();
    p3.decreasePheroSugar();

    p4.decreasePheroSugar();

    p5.decreasePheroSugar();
    p5.decreasePheroSugar();
    p5.decreasePheroSugar();
    p5.decreasePheroSugar();
    vector<Place> places{{p1, p2, p3, p4, p5}};
    CHECK(closestPlaceToTheSugar(places, 1).getCoords() == p4.getCoords());
}

TEST_CASE("Place canFourmiMoveToPlace"){
    Place p1 = Place(Coord(1, 3));
    Place p2 = Place(Coord(1, 3));
    Place p3 = Place(Coord(1, 3));

    int colony = 1;
    int s_colony = 2;
    Fourmi f1 = Fourmi(Coord(2, 3), 1, colony, Caste::ouvrier);
    Fourmi f2 = Fourmi(Coord(2, 3), 1, colony, Caste::guerrier);
    Fourmi f3 = Fourmi(Coord(2, 3), 1, colony, Caste::reproductrice);

    CHECK(canFourmiMoveToPlace(f1, p1));
    CHECK(canFourmiMoveToPlace(f2, p1));
    CHECK(canFourmiMoveToPlace(f3, p1));

    CHECK(canFourmiMoveToPlace(f1, p2));
    CHECK(canFourmiMoveToPlace(f2, p2));
    CHECK(canFourmiMoveToPlace(f3, p2));

    p2.setSugar();

    CHECK_FALSE(canFourmiMoveToPlace(f1, p2));
    CHECK_FALSE(canFourmiMoveToPlace(f2, p2));
    CHECK_FALSE(canFourmiMoveToPlace(f3, p2));

    p1.setNid(colony);
    p3.setNid(s_colony);

    CHECK_FALSE(canFourmiMoveToPlace(f1, p1));
    CHECK_FALSE(canFourmiMoveToPlace(f2, p1));
    CHECK(canFourmiMoveToPlace(f3, p1));
    
    CHECK_FALSE(canFourmiMoveToPlace(f3, p3));
}

TEST_SUITE_END();