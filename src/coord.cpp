#include <stdexcept>
#include <iostream>
#include <projet_fourmi/coord.hpp>
#include <random>
#include <time.h>


using namespace std;

Coord::Coord(int lig, int col):line{lig}, column{col} {
    if(lig >= TAILLEGRILLE || col >= TAILLEGRILLE || lig < 0 || col < 0)
        throw invalid_argument("Incorrect coordinates");
}

ostream& operator<<(ostream& out, Coord c){
    out << "(" << c.getLine() << ", " << c.getColumn() << ")";
    return out;
}

bool operator==(Coord c1, Coord c2){
    return c1.getLine() == c2.getLine() && c1.getColumn() == c2.getColumn();
}

bool operator!=(Coord c1, Coord c2){
    return !(c1 == c2);
}
vector<Coord> EnsCoord::getCoords() const{
    return coords;
}
int EnsCoord::position(Coord c) const{
    for(int i = 0; i < coords.size(); i++){
        if(coords[i] == c) return i;
    }
    return -1;
}
bool EnsCoord::contient(Coord c) const{
    return position(c) != -1;
}

void EnsCoord::ajoute(Coord c){
    if(contient(c)) return;

    coords.push_back(c);
    coords_size++;
}

bool EnsCoord::estVide() const{
    return coords_size == 0 && coords.size() == 0;
}

int EnsCoord::taille() const{
    return coords_size;
}

Coord EnsCoord::ieme(int n) const{
    if(n >= taille() || n < 0)
        throw invalid_argument("The argument n is out of range!");
    return coords[n];
}

void EnsCoord::supprime(Coord c){
    if(!contient(c))
        throw invalid_argument("The set of coordiantes does not contain the coordinate c");
    
    int pos = position(c);
    swap(coords[pos], coords[coords.size()-1]);
    coords.pop_back();
    coords_size--;
}

ostream& operator<<(ostream& out, EnsCoord ens){
    vector<Coord> coords = ens.getCoords();
    for(int i = 0; i < coords.size(); i++){
        out << coords[i];
        if(i < coords.size() - 1)
            out << ", ";
    }
    return out;
}

Coord EnsCoord::choixHasard() const{
    if(coords.size() == 0)
        throw runtime_error("L'ensemble est vide!");
    srand (time(NULL));
    int n = rand() % coords.size();
    return coords[n];
}

EnsCoord voisines(Coord c){
    EnsCoord ens = EnsCoord();
    int l = c.getLine();
    int col = c.getColumn();
    for(int i = l-1; i <= l+1; i++){
        if(i < 0 || i >= TAILLEGRILLE) continue;
        for(int j = col-1; j <= col+1; j++){
            if(j < 0 || j >= TAILLEGRILLE) continue;  
            if(i == l && j == col) continue; 
            ens.ajoute(Coord(i, j)); 
        }
    }
    return ens;
}
