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

TEST_SUITE_BEGIN("Place");
TEST_CASE("Constructor"){
    Place p = Place(Coord(3, 5));
    CHECK(p.getCoords() == Coord(3, 5));
    CHECK(p.getFourmiID() == -1);
    CHECK(p.getPheroNid() == 0);

    CHECK_FALSE(p.containNid());
    CHECK_FALSE(p.containSugar());
    CHECK_FALSE(p.estSurUnePiste());
    CHECK(p.isEmpty());
}

TEST_CASE("Place sugar"){
    Place p1 = Place(Coord(11, 4));
    p1.setNid();
    CHECK_THROWS_AS(p1.setSugar(), runtime_error);
    
    Place p = Place(Coord(3, 5));
    CHECK_FALSE(p.containSugar());
    CHECK(p.getPheroSugar() == 0);
    CHECK(p.isEmpty());

    p.setSugar();
    CHECK_FALSE(p.isEmpty());

    CHECK_THROWS_AS(p1.setNid(), runtime_error);
    CHECK_THROWS_AS(p1.setSugar(), runtime_error);
    CHECK_THROWS_AS(p1.setFourmi(Fourmi(Coord(0, 0), 1)), runtime_error);

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
    CHECK(p.getPheroSugar() == 0);
    CHECK_FALSE(p.estSurUnePiste());

    p.setPheroSugar();
    CHECK(p.getPheroSugar() == MAX_PHERO_SUGAR_INTENSITY);
    p.decreasePheroSugar();
    CHECK(p.getPheroSugar() == MAX_PHERO_SUGAR_INTENSITY - AMOUT_OF_PHERO_SUGAR_TO_REMOVE);
    CHECK(p.estSurUnePiste());
    while(p.getPheroSugar() > 0)
        p.decreasePheroSugar();
    CHECK_FALSE(p.estSurUnePiste());
    CHECK(p.getPheroSugar() == 0);
}

TEST_CASE("Place nid"){
    Place p1 = Place(Coord(11, 4));
    p1.setSugar();
    CHECK_THROWS_AS(p1.setNid(), runtime_error);

    Place p = Place(Coord(3, 5));
    CHECK_FALSE(p.containNid());
    CHECK(p.isEmpty());

    p.setNid();
    CHECK_FALSE(p.isEmpty());
    CHECK(p.containNid());

    CHECK_THROWS_AS(p1.setNid(), runtime_error);
    CHECK_THROWS_AS(p1.setSugar(), runtime_error);
    CHECK_THROWS_AS(p1.setFourmi(Fourmi(Coord(0, 0), 1)), runtime_error);
}

TEST_CASE("Place phero nid"){
    Place p = Place(Coord(1, 3));
    CHECK(p.getPheroNid() == 0);
    p.setPheroNid(1);
    CHECK(p.getPheroNid() == 1);
    p.setPheroNid(0.587);
    CHECK(float_equal(p.getPheroNid(), 0.587));
}

TEST_CASE("Place fourmi"){
    Fourmi f = Fourmi(Coord(1, 3), 1);

    Place p1 = Place(Coord(2, 4));
    Fourmi f1 = Fourmi(Coord(2, 4), 2);
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
TEST_SUITE_END();

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
    p.setNid();

    g.changePlace(p);
    Place p1 = g.loadPlace(c);
    CHECK(p1.containNid());
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
    
    setNid(g, ens);
    
    for(Coord c: nidCoords){
        CHECK_FALSE( g.loadPlace(c).isEmpty() );
        CHECK( g.loadPlace(c).containNid() );
        CHECK( g.loadPlace(c).getPheroNid() == 1 );
    }
    CHECK_THROWS(setNid(g, ens));
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
    CHECK_THROWS(setNid(g, ens));
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

    for(int i = 0; i < fourmiCoords.size(); i++){
        Coord c = fourmiCoords[i];
        Fourmi f = Fourmi(c, i);
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

    CHECK_THROWS(setNid(g, ens));
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
    for(int i = 0; i < fourmis_coords.taille(); i++){
        Fourmi f = Fourmi(fourmis_coords.ieme(i), i);
        fourmis.push_back(f);
    }

    Grille g = initializeGrille(fourmis, sugar_ens, nid_ens);

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

    for(Coord c: nid_ens.getCoords()){
        CHECK_FALSE( g.loadPlace(c).isEmpty() );
        CHECK( g.loadPlace(c).containNid() );
        CHECK( g.loadPlace(c).getPheroNid() == 1 );
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

    setNid(g, nid_ens);

    CHECK(g.loadPlace(Coord(4, 7)).getPheroNid() == 1);
    CHECK( g.loadPlace(Coord(3, 7)).getPheroNid() == 0 );

    linearizePheroNid(g);

    CHECK( float_equal(g.loadPlace(Coord(3, 7)).getPheroNid(), 1 - (1/TAILLEGRILLE)) );
    CHECK( float_equal(g.loadPlace(Coord(2, 7)).getPheroNid(), (1 - (1/TAILLEGRILLE))) - (1/TAILLEGRILLE) );

}

TEST_SUITE_END();