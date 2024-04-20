#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>

using namespace std;

Fourmi::Fourmi(Coord c, int id):coords{c}, num{id}, porte_sucre{false}{}

Coord Fourmi::getCoords() const{
    return coords;
}

int Fourmi::getNum() const{
    return num;
}

bool Fourmi::isAlive() const{
    return is_alive;
}

bool Fourmi::porteSucre() const{
    return porte_sucre;
}

void Fourmi::prendSucre(){
    if(porteSucre()) 
        throw runtime_error("The ant is already carrying sugar.");
    porte_sucre = true;
}

void Fourmi::poseSucre(){
    if(!porteSucre()) 
        throw runtime_error("The ant doesn't carry sugar.");
    porte_sucre = false;
}

void Fourmi::deplace(Coord c){
    Coord current = getCoords();
    EnsCoord ens = voisines(current);
    if(!ens.contient(c)){
        throw invalid_argument("The coordinates aren't neighbours to the place where the ant is placed.");
    }

    coords = c;
}

vector<Fourmi> createListFourmis(EnsCoord ens){
    vector<Fourmi> res = vector<Fourmi>();
    for(int i = 0; i < ens.getCoords().size(); i++){
        Fourmi f = Fourmi(ens.getCoords()[i], i);
        res.push_back(f);
    }
    return res;
}