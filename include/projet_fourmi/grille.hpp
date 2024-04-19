#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/fourmi.hpp>

using namespace std;

class Grille{
private:
    int h;

public:
    Grille();
    Place loadPlace(Coord c) const;
    void changePlace(Place p) const;
    void decreasePheroSugar();
};

void setNid(Grille& g, EnsCoord ens);
void setFourmis(Grille& g, vector<Fourmi> fourmis);
Grille initializeGrille(vector<Fourmi> fourmis, EnsCoord sugar_coords, EnsCoord nid_coords);
void linearizePheroNid(Grille& g);
void decreasePheroSugar(Grille& g);
#endif