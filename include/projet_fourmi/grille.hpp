#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/consts.hpp>

using namespace std;

class Grille{
private:
    vector<Place> places;
    vector<EnsCoord> nids;
    void initialiser_places();
    vector<int> amount_of_sugar_in_each_colony;

    void addSugar(int colony) { amount_of_sugar_in_each_colony[colony] += AMOUNT_OF_SUGAR_FOURMI_PORTE; }

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

    int getAmountOfSugar(int colony) const { return amount_of_sugar_in_each_colony[colony]; }
    void descreaseAmountOfSugar(int colony, int amount) { amount_of_sugar_in_each_colony[colony] -= amount; }
    void poseSugarFromFourmi(Fourmi f);
    void setNid(EnsCoord coords, int colony);
    EnsCoord getNid(int colony) const;
};

void setNid(Grille& g, EnsCoord ens, int colony);
void setSugar(Grille& g, EnsCoord ens);
void setFourmis(Grille& g, vector<Fourmi> fourmis);
Grille initializeGrille(vector<Fourmi> fourmis, EnsCoord sugar_coords, int number_of_colonies);
void linearizePheroNid(Grille& g);
void decreasePheroSugar(Grille& g);

//return the places from the Grid by Coordinates
vector<Place> loadPlacesByCoords(const Grille &g, EnsCoord ens);

void areFourmiGrilleCoherent(const Grille &g, const Fourmi &f);

/// returns the coordinates of places around the nid (can be used for the coordinates of fourmis)
EnsCoord coordsAroundNid(EnsCoord ens_nid);

/// returns the biggest intensity of the pheromons of the place among the neigbours
float getMaximalNeighbourPheroNid(Grille& g, Place p);

Place getNextRandomPlaceToGo(const Fourmi &f, const Grille &g);

/// return true if the nid is neighbour to the place in the given coordinates, false in the other case
bool isNidNeighbour(const Grille &g, Coord c);

/// return true if a sugar is neighbour to the place in the given coordinates, false in the other case
bool isSugarNeighbour(const Grille &g, Coord c);

/// return true if a fourmi nid is neighbour to the place in the given coordinates, false in the other case
bool isFourmiNeighbour(const Grille &g, Coord c);

/// return the place of the neigbour nid around coordinates and error if there is not
Place getNeigbourNidPlace(const Grille &g, Coord c);

/// return the place of the neigbour sugar around coordinates and error if there is not
Place getNeigbourSugarPlace(const Grille &g, Coord c);

/// return the place of the neigbour fourmi around coordinates and error if there is not
Place getNeigbourFourmiPlace(const Grille &g, Coord c);

/// @brief returns random empty place
/// @param g - the grid
/// @return random empty place
Place getRandomEmptyPlace(const Grille &g);

/// @brief Puts sugar in random place
/// @param g the reference to the grid
void putSugarInRandomPlace(Grille &g);
#endif