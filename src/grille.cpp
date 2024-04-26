#include <projet_fourmi/grille.hpp>

using namespace std;

void Grille::initialiser_places(){
    for(int i = 0; i < TAILLEGRILLE; i++){
        for(int j = 0; j < TAILLEGRILLE; j++){
            Place p = Place(Coord(i, j));
            places.push_back(p);
        }
    }
}

Grille::Grille():places{vector<Place>()}, fourmis{vector<Fourmi>()}{
    initialiser_places();
}

Grille::Grille(vector<Fourmi> _fourmis):places{vector<Place>()}, fourmis{vector<Fourmi>()}{
    initialiser_places();
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

Place Grille::loadPlaceById(int id) const{
    if(id >= places.size() || id < 0) 
        throw invalid_argument("The id is out of range!");
    return places[id];
}

void Grille::decreasePheroSugar(){
    for(int i = 0; i < places.size(); i++){
        places[i].decreasePheroSugar();
    }
}

void setNid(Grille &g, EnsCoord ens){
    for(int i = 0; i < ens.getCoords().size(); i++){
        Coord c = ens.ieme(i);
        Place p = g.loadPlace(c);
        p.setNid();
        p.setPheroNid(1);
        g.changePlace(p);
    }
}

void setSugar(Grille& g, EnsCoord ens){
    for(int i = 0; i < ens.getCoords().size(); i++){
        Coord c = ens.ieme(i);
        Place p = g.loadPlace(c);
        p.setSugar();
        g.changePlace(p);
    }
}

void setFourmis(Grille& g, vector<Fourmi> fourmis){
    for(int i = 0; i < fourmis.size(); i++){
        Fourmi f = fourmis[i];
        Coord c = f.getCoords();
        Place p = g.loadPlace(c);
        p.setFourmi(f);
        g.changePlace(p);
    }
}



float getMaximalNeighbourPheroNid(Grille& g, Place p){
    EnsCoord voisins = voisines(p.getCoords());
    float max = 0;
    for(Coord c: voisins.getCoords()){
        Place p = g.loadPlace(c);
        if(p.getPheroNid() > max)
            max = p.getPheroNid();
    }
    return max;
}

void linearizePheroNid(Grille& g){
    for(int i = 0; i < TAILLEGRILLE; i++){
        for(int i = 0; i < g.numOfPlaces(); i++){
            Place p = g.loadPlaceById(i);
            if(p.getPheroNid() >= 1) continue;

            float max_vois = getMaximalNeighbourPheroNid(g, p);
            float new_intensity = max_vois - (1/TAILLEGRILLE);
            p.setPheroNid( 
                new_intensity > 0 ? new_intensity : 0
            );
            g.changePlace(p);
        }
    }
}

Grille initializeGrille(vector<Fourmi> fourmis, EnsCoord sugar_coords, EnsCoord nid_coords){
    Grille g = Grille();
    setNid(g, nid_coords);
    setSugar(g, sugar_coords);
    setFourmis(g, fourmis);

    linearizePheroNid(g);
    return g;
}

EnsCoord coordsAroundNid(EnsCoord ens_nid){
    EnsCoord res = EnsCoord();
    for(Coord c: ens_nid.getCoords()){
        EnsCoord voisins = voisines(c);
        for(Coord v: voisins.getCoords()){
            if(res.contient(v) || ens_nid.contient(v)) continue;
            res.ajoute(v);
        }
    }
    return res;
}

void areFourmiGrilleCoherent(const Grille &g, const Fourmi &f){
    Coord c = f.getCoords();
    Place p = g.loadPlace(c);

    if(p.getFourmiID() != f.getNum()) 
        throw runtime_error("The state of the program isn't coherent! Error: Grille and Fourmi");
}

vector<Place> loadPlacesByCoords(const Grille &g, EnsCoord ens){
        vector<Place> places{{}};
        for(Coord c: ens.getCoords()){
            places.push_back(g.loadPlace(c));
        }  
        return places;
}

