#ifndef COORD_HPP
#define COORD_HPP

#include <vector>
#include <projet_fourmi/consts.hpp>

using namespace std;


class Coord{
public:
    Coord(int lig, int col);
    int getLine() const { return line; }
    int getColumn() const { return column; }
private:
    int line;
    int column;
};

ostream& operator<<(ostream& out, Coord c);
bool operator==(Coord c1, Coord c2);
bool operator!=(Coord c1, Coord c2);


class EnsCoord{
public: 
    EnsCoord(): coords{vector<Coord>()}, coords_size{0} {}
    EnsCoord(vector<Coord> cs): coords{cs}, coords_size{0} { coords_size = cs.size(); }
    vector<Coord> getCoords() const;
    bool contient(Coord c) const;
    void ajoute(Coord c);
    void supprime(Coord c);
    bool estVide() const;
    int taille() const;
    Coord ieme(int n) const;
    Coord choixHasard() const;
private:
    vector<Coord> coords;
    int coords_size;

    int position(Coord c) const;
};
ostream& operator<<(ostream& out, EnsCoord ens);

/// @brief returns the set of coordinates that are neighbours to the given coordinate
/// @param c coordinate
/// @return the set of coordinates that are neighbours to the given coordinate
EnsCoord voisines(Coord c);

#endif
