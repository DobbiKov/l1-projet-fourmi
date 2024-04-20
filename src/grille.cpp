#include <projet_fourmi/grille.hpp>

using namespace std;

Grille::Grille():places{vector<Place>()}{
    for(int i = 0; i < TAILLEGRILLE; i++){
        for(int j = 0; j < TAILLEGRILLE; j++){
            Place p = Place(Coord(i, j));
            places.push_back(p);
        }
    }
}

Place Grille::loadPlace(const Coord& c) const{
    int idx = getCoordIdx(c);
    return places[idx];
}

void Grille::changePlace(Place p){
    int idx = getCoordIdx(p.getCoords());
    places[idx] = p;
}

int Grille::getCoordIdx(const Coord& c) const{
    int i = c.getLine();
    int j = c.getColumn();
    int idx = j+(i*20);
    if(idx >= places.size())
        throw invalid_argument("The coordinates are out of Grille!");
    return idx;
}

void Grille::decreasePheroSugar(){
    for(int i = 0; i < places.size(); i++){
        places[i].decreasePheroSugar();
    }
}

