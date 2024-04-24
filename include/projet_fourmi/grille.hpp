#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/fourmi.hpp>

using namespace std;

class Grille{
private:
    vector<Place> places;

public:
    Grille();
    Place loadPlace(const Coord& c) const;
    void changePlace(Place p);
    void decreasePheroSugar();
    int getCoordIdx(const Coord& c) const;
    Place loadPlaceById(int id) const;
    vector<Place> getPlaces() const {return places;}
    //la taille du tableau places
    int numOfPlaces() const {return places.size(); }
};

void setNid(Grille& g, EnsCoord ens);
void setSugar(Grille& g, EnsCoord ens);
void setFourmis(Grille& g, vector<Fourmi> fourmis);
Grille initializeGrille(vector<Fourmi> fourmis, EnsCoord sugar_coords, EnsCoord nid_coords);
void linearizePheroNid(Grille& g);
void decreasePheroSugar(Grille& g);

void areFourmiGrilleCoherent(const Grille &g, const Fourmi &f);

// returns the coordinates of places around the nid (can be used for the coordinates of fourmis)
EnsCoord coordsAroundNid(EnsCoord ens_nid);

// returns the biggest intensity of the pheromons of the place among the neigbours
float getMaximalNeighbourPheroNid(Grille& g, Place p);
#endif