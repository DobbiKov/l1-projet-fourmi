#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/consts.hpp>

using namespace std;

Fourmi::Fourmi(Coord c, int id):coords{c}, num{id}, porte_sucre{false}, is_alive{true}{}

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

bool Fourmi::searchingSugar() const{
    return !porteSucre();
}

bool Fourmi::goingToTheNid() const{
    return porteSucre();
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

void Fourmi::killFourmi(){
    if(isAlive() == false) throw runtime_error("The ant is already dead!");
    is_alive = false;
}

bool operator==(const Fourmi& f1, const Fourmi& f2){
    return (
        f1.getCoords() == f2.getCoords() && 
        f1.getNum() == f2.getNum() && 
        f1.isAlive() == f2.isAlive() && 
        f1.goingToTheNid() == f2.goingToTheNid() &&
        f1.searchingSugar() == f2.searchingSugar() &&
        f1.porteSucre() == f2.porteSucre()
    );
}

bool operator!=(const Fourmi& f1, const Fourmi& f2) {
    return !(f1 == f2);
}