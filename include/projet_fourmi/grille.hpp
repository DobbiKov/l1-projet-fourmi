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
    vector<Place> getPlaces() const {return places;}
};

//TODO: 
void setNid(Grille& g, EnsCoord ens);
void setFourmis(Grille& g, vector<Fourmi> fourmis);
Grille initializeGrille(vector<Fourmi> fourmis, EnsCoord sugar_coords, EnsCoord nid_coords);
void linearizePheroNid(Grille& g);
void decreasePheroSugar(Grille& g);
#endif