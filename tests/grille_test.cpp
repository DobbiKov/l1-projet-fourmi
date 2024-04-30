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

TEST_SUITE_BEGIN("Grille");
TEST_CASE("Grille constructor and load"){
    Grille g = Grille();
    CHECK(g.getPlaces().size() == TAILLEGRILLE*TAILLEGRILLE);


    Coord c = Coord(1, 3);
    Place p = g.loadPlace(c);
    CHECK(p.getCoords() == c);
}

TEST_CASE("Grille getCoordIdx"){
    Grille g = Grille();
    Coord c = Coord(11, 4);
    int idx = g.getCoordIdx(c);
    CHECK(idx == 11*TAILLEGRILLE + 4);
    CHECK(g.loadPlace(c).getCoords() == c);
}

TEST_CASE("Grille load and change place"){
    Grille g = Grille();

    Coord c = Coord(1, 3);
    Place p = g.loadPlace(c);
    CHECK_FALSE(p.containNid());
    p.setNid(NUMBER_OF_COLONIES-1);

    g.changePlace(p);
    Place p1 = g.loadPlace(c);
    CHECK(p1.containNid());
    CHECK(p1.getColonyId() == NUMBER_OF_COLONIES-1);
}

TEST_CASE("Grille setNid"){
    vector<Coord> nidCoords{{
            Coord(3, 4),
            Coord(3, 5),
            Coord(4, 4),
            Coord(4, 5)
        }};
    EnsCoord ens = EnsCoord(nidCoords);

    Grille g = Grille();

    for(Coord c: nidCoords){
        CHECK( g.loadPlace(c).isEmpty() );
        CHECK_FALSE( g.loadPlace(c).containNid() );
        CHECK( g.loadPlace(c).getPheroNid() == 0 );
    }
    
    int colony = NUMBER_OF_COLONIES-1;
    setNid(g, ens, colony);
    
    for(Coord c: nidCoords){
        CHECK_FALSE( g.loadPlace(c).isEmpty() );
        CHECK( g.loadPlace(c).containNid() );
        CHECK( g.loadPlace(c).getPheroNid() == 1 );
        CHECK( g.loadPlace(c).getPheroNidByColony(colony) == 1 );
        for(int i = 0; i < colony; i++){
            CHECK( g.loadPlace(c).getPheroNidByColony(i) == 0 );
        }
    }
    EnsCoord got_ens = g.getNid(colony);
    for(int i = 0; i < got_ens.taille(); i++){
        CHECK(got_ens.ieme(i) == ens.ieme(i));
    }
    CHECK_THROWS(setNid(g, ens, colony));
    CHECK_THROWS(setSugar(g, ens));
}

TEST_CASE("Grille setSugar"){
    vector<Coord> sugarCoords{{
            Coord(3, 4),
            Coord(3, 5),
            Coord(4, 4),
            Coord(4, 5)
        }};
    EnsCoord ens = EnsCoord(sugarCoords);

    Grille g = Grille();

    for(Coord c: sugarCoords){
        CHECK( g.loadPlace(c).isEmpty() );
        CHECK_FALSE( g.loadPlace(c).containSugar() );
    }
    
    setSugar(g, ens);
    
    for(Coord c: sugarCoords){
        CHECK_FALSE( g.loadPlace(c).isEmpty() );
        CHECK( g.loadPlace(c).containSugar() );
    }
    CHECK_THROWS(setNid(g, ens, NUMBER_OF_COLONIES-1));
    CHECK_THROWS(setSugar(g, ens));
}

TEST_CASE("Grille setFourmis"){
    vector<Coord> fourmiCoords{{
            Coord(3, 4),
            Coord(3, 5),
            Coord(4, 4),
            Coord(4, 5)
        }};
    EnsCoord ens = EnsCoord(fourmiCoords);
    vector<Fourmi> fourmis = vector<Fourmi>();

    Caste cast = Caste::ouvrier;
    for(int i = 0; i < fourmiCoords.size(); i++){
        Coord c = fourmiCoords[i];
        Fourmi f = Fourmi(c, i, NUMBER_OF_COLONIES-1, cast);
        fourmis.push_back(f);
    }

    Grille g = Grille();
    Grille g_bad = Grille();

    setSugar(g_bad, ens);

    CHECK_THROWS(setFourmis(g_bad, fourmis));

    for(Coord c: fourmiCoords){
        CHECK( g.loadPlace(c).isEmpty() );
        CHECK( g.loadPlace(c).getFourmiID() == -1 );
    }
    
    setFourmis(g, fourmis);


    for(int i = 0; i < fourmiCoords.size(); i++){
        Coord c = fourmiCoords[i];
        CHECK_FALSE( g.loadPlace(c).isEmpty() );
        CHECK_FALSE( g.loadPlace(c).getFourmiID() == -1 );
        CHECK( g.loadPlace(c).getFourmiID() == i );
    }

    CHECK_THROWS(setNid(g, ens, NUMBER_OF_COLONIES-1));
    CHECK_THROWS(setSugar(g, ens));
}

TEST_CASE("Grille coordAroundNid"){
    vector<Coord> nid_coords{{
        Coord(4, 7),
        Coord(4, 8),
        Coord(5, 7),
        Coord(5, 8)
    }};
    EnsCoord nid_ens = EnsCoord(nid_coords);

    EnsCoord res = coordsAroundNid(nid_ens);

    CHECK(res.taille() == 12);

    vector<Coord> around_coords{{
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
    for(Coord c: around_coords){
        CHECK(res.contient(c));
    }
}

TEST_CASE("Grille initializeGrille"){
    vector<Coord> nid_coords{{
        Coord(4, 7),
        Coord(4, 8),
        Coord(5, 7),
        Coord(5, 8)
    }};
    EnsCoord nid_ens = EnsCoord(nid_coords);

    vector<Coord> sugar_coords{{
        Coord(2, 7),
        Coord(4, 12),
        Coord(11, 7),
        Coord(10, 2)
    }};
    EnsCoord sugar_ens = EnsCoord(sugar_coords);

    EnsCoord fourmis_coords = coordsAroundNid(nid_ens);
    vector<Fourmi> fourmis{{}};
    Caste cast = Caste::ouvrier;
    for(int i = 0; i < fourmis_coords.taille(); i++){
        Fourmi f = Fourmi(fourmis_coords.ieme(i), i, NUMBER_OF_COLONIES-1, cast);
        fourmis.push_back(f);
    }

    Grille g = initializeGrille(fourmis, sugar_ens, NUMBER_OF_COLONIES);

    for(int i = 0; i < fourmis_coords.taille(); i++){
        Coord c = fourmis_coords.ieme(i);
        CHECK_FALSE( g.loadPlace(c).isEmpty() );
        CHECK_FALSE( g.loadPlace(c).getFourmiID() == -1 );
        CHECK( g.loadPlace(c).getFourmiID() == i );
    }

    for(Coord c: sugar_ens.getCoords()){
        CHECK_FALSE( g.loadPlace(c).isEmpty() );
        CHECK( g.loadPlace(c).containSugar() );
    }

    for(int col = 0; col < NUMBER_OF_COLONIES; col++){
        EnsCoord nid_c = g.getNid(col);
        for(int i = 0; i < nid_c.taille(); i++){
            CHECK(nid_c.ieme(i) == NIDS_COORDS[col][i]);
        }
    }
}

TEST_CASE("Grille linearizePheroNid"){
    Grille g = Grille();

    vector<Coord> nid_coords{{
        Coord(4, 7),
        Coord(4, 8),
        Coord(5, 7),
        Coord(5, 8)
    }};
    EnsCoord nid_ens = EnsCoord(nid_coords);

    CHECK(g.loadPlace(Coord(4, 7)).getPheroNid() == 0);
    CHECK( g.loadPlace(Coord(3, 7)).getPheroNid() == 0 );

    int colony = NUMBER_OF_COLONIES-1;
    int s_colony = 0;

    setNid(g, nid_ens, colony);

    CHECK(g.loadPlace(Coord(4, 7)).getPheroNid() == 1);
    CHECK( g.loadPlace(Coord(3, 7)).getPheroNid() == 0 );

    CHECK(g.loadPlace(Coord(4, 7)).getPheroNidByColony(colony) == 1);
    CHECK( g.loadPlace(Coord(3, 7)).getPheroNidByColony(colony) == 0 );

    linearizePheroNid(g);

    CHECK( float_equal(g.loadPlace(Coord(3, 7)).getPheroNid(), 1.0f - (1.0f/TAILLEGRILLE)) );
    CHECK( float_equal(g.loadPlace(Coord(2, 7)).getPheroNid(), (1.0f - (1.0f/TAILLEGRILLE))) - (1.0f/TAILLEGRILLE) );
    CHECK( float_equal(g.loadPlace(Coord(3, 7)).getPheroNidByColony(colony), 1.0f - (1.0f/TAILLEGRILLE)) );
    CHECK( float_equal(g.loadPlace(Coord(2, 7)).getPheroNidByColony(colony), (1.0f - (1.0f/TAILLEGRILLE))) - (1.0f/TAILLEGRILLE) );

    CHECK_FALSE( float_equal(g.loadPlace(Coord(3, 7)).getPheroNidByColony(s_colony), 1.0f - (1.0f/TAILLEGRILLE)) );
    CHECK( float_equal(g.loadPlace(Coord(2, 7)).getPheroNidByColony(s_colony), 0.0f ));

}

TEST_CASE("Grille loadPlacesByCoords"){
    Grille g = Grille();
    vector<Coord> coords{{
        Coord(4, 7),
        Coord(4, 8),
        Coord(5, 7),
        Coord(5, 8)
    }};
    EnsCoord ens = EnsCoord(coords);
    vector<Place> places = loadPlacesByCoords(g, ens);

    for(int i = 0; i < coords.size(); i++){
        CHECK(places[i].getCoords() == coords[i]);
    }
}

TEST_CASE("Grille isNidNeighbour"){
    Grille g = Grille();
    Coord c1 = Coord(5, 6);
    Coord c1n = Coord(5, 7);

    Coord c2 = Coord(6, 9);

    Place p = g.loadPlace(c1);
    p.setNid(NUMBER_OF_COLONIES-1);
    g.changePlace(p);

    CHECK(isFourmiNearNid(g, c1n));
    CHECK_FALSE(isFourmiNearNid(g, c2));
}

TEST_CASE("Grille isSugarNeighbour"){
    Grille g = Grille();
    Coord c1 = Coord(5, 6);
    Coord c1n = Coord(5, 7);

    Coord c2 = Coord(6, 9);

    Place p = g.loadPlace(c1);
    p.setSugar();
    g.changePlace(p);

    CHECK(isSugarNeighbour(g, c1n));
    CHECK_FALSE(isSugarNeighbour(g, c2));
}

TEST_CASE("Grille isFourmiNeighbour"){
    Grille g = Grille();
    Coord c1 = Coord(5, 6);
    Coord c1n = Coord(5, 7);

    Caste cast = Caste::ouvrier;
    Fourmi f = Fourmi(c1, 1, NUMBER_OF_COLONIES-1, cast);

    Coord c2 = Coord(6, 9);

    Place p = g.loadPlace(c1);
    p.setFourmi(f);
    g.changePlace(p);

    CHECK(isFourmiNeighbour(g, c1n));
    CHECK_FALSE(isFourmiNeighbour(g, c2));
}

TEST_CASE("Grille getNeigbourNidPlace"){
    Grille g = Grille();
    Coord c1 = Coord(5, 6);
    Coord c1n = Coord(5, 7);

    Coord c2 = Coord(6, 9);

    Place p = g.loadPlace(c1);
    p.setNid(NUMBER_OF_COLONIES-1);
    g.changePlace(p);

    CHECK(isFourmiNearNid(g, c1n));
    CHECK_FALSE(isFourmiNearNid(g, c2));

    Place p1 = getNeigbourNidPlace(g, c1n);
    CHECK(p1.getCoords() == c1);

    CHECK_THROWS_AS_MESSAGE(getNeigbourNidPlace(g, c2), invalid_argument, "There's not neighbour nid around this coordinate!");
}

TEST_CASE("Grille getNeigbourSugarPlace"){
    Grille g = Grille();
    Coord c1 = Coord(5, 6);
    Coord c1n = Coord(5, 7);

    Coord c2 = Coord(6, 9);

    Place p = g.loadPlace(c1);
    p.setSugar();
    g.changePlace(p);

    CHECK(isSugarNeighbour(g, c1n));
    CHECK_FALSE(isSugarNeighbour(g, c2));

    Place p1 = getNeigbourSugarPlace(g, c1n);
    CHECK(p1.getCoords() == c1);

    CHECK_THROWS_AS_MESSAGE(getNeigbourSugarPlace(g, c2), invalid_argument, "There's not neighbour sugar around this coordinate!");
}

TEST_CASE("Grille getNeigbourSugarPlace"){
    Grille g = Grille();
    Coord c1 = Coord(5, 6);
    Coord c1n = Coord(5, 7);

    Caste cast = Caste::ouvrier;
    Fourmi f = Fourmi(c1, 1, NUMBER_OF_COLONIES-1, cast);

    Coord c2 = Coord(6, 9);

    Place p = g.loadPlace(c1);
    p.setFourmi(f);
    g.changePlace(p);

    CHECK(isFourmiNeighbour(g, c1n));
    CHECK_FALSE(isFourmiNeighbour(g, c2));

    Place p1 = getNeigbourFourmiPlace(g, c1n);
    CHECK(p1.getCoords() == c1);

    CHECK_THROWS_AS_MESSAGE(getNeigbourFourmiPlace(g, c2), invalid_argument, "There's not neighbour fourmi around this coordinate!");
}

TEST_CASE("Grille isFourmiNearNid"){
    int colony = 1;
    int s_colony = 2;

    Caste cast = Caste::ouvrier;
    Fourmi f1 = Fourmi(Coord(1, 2), 1, colony, cast);
    Fourmi f3 = Fourmi(Coord(4, 2), 3, colony, cast);
    Fourmi f2 = Fourmi(Coord(2, 2), 2, s_colony, cast);

    vector<Fourmi> fourmis{{f1, f2, f3}};

    EnsCoord nid(
        vector<Coord>{{
            Coord(1,3),
            Coord(1,4),
            Coord(2,3),
            Coord(2,4),
        }}
    );

    Grille g = Grille();
    setNid(g, nid, colony);
    setFourmis(g, fourmis);
    linearizePheroNid(g);

    CHECK(isFourmiNearItsNid(f1, g));
    CHECK_FALSE(isFourmiNearItsNid(f2, g));
    CHECK_FALSE(isFourmiNearItsNid(f3, g));
}

TEST_CASE("Grille getMaximalNeighbourPheroNidByColony"){

    Coord c1 = Coord(1,1);
    Coord c2 = Coord(1,2);
    Coord c3 = Coord(2,1);
    Coord c4 = Coord(1,3);
    Grille g = Grille();

    Place p1 = g.loadPlace(c1);
    Place p2 = g.loadPlace(c2);
    Place p3 = g.loadPlace(c3);
    Place p4 = g.loadPlace(c4);

    p1.setPheroNid(0.95f);
    p2.setPheroNid(0.85f);

    g.changePlace(p1);
    g.changePlace(p2);

    CHECK( float_equal(getMaximalNeighbourPheroNid(g, p3), 0.95f) );
    CHECK( float_equal(getMaximalNeighbourPheroNid(g, p4), 0.85f) );
}

TEST_CASE("Grille getMaximalNeighbourPheroNidByColony"){
    int colony = 1;
    int s_colony = 2;

    Coord c1 = Coord(1,1);
    Coord c2 = Coord(1,2);
    Coord c3 = Coord(2,1);
    Coord c4 = Coord(1,3);
    Coord c5 = Coord(1,0);
    Grille g = Grille();

    Place p1 = g.loadPlace(c1);
    Place p2 = g.loadPlace(c2);
    Place p3 = g.loadPlace(c3);
    Place p4 = g.loadPlace(c4);
    Place p5 = g.loadPlace(c5);

    p1.setPheroNidByColony(colony, 0.95f);
    p2.setPheroNidByColony(colony, 0.85f);
    p1.setPheroNidByColony(s_colony, 0.85f);
    p2.setPheroNidByColony(s_colony, 0.95f);

    g.changePlace(p1);
    g.changePlace(p2);

    CHECK( float_equal(getMaximalNeighbourPheroNidByColony(g, p3, colony), 0.95f) );
    CHECK( float_equal(getMaximalNeighbourPheroNidByColony(g, p4, colony), 0.85f) );
    CHECK( float_equal(getMaximalNeighbourPheroNidByColony(g, p3, s_colony), 0.95f) );
    CHECK( float_equal(getMaximalNeighbourPheroNidByColony(g, p4, s_colony), 0.95f) );
    CHECK( float_equal(getMaximalNeighbourPheroNidByColony(g, p5, s_colony), 0.85f) );
}

TEST_SUITE_END();