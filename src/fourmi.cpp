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

bool Fourmi::porteSucre() const{
    return porteSucre;
}

void Fourmi::prendSucre(){
    porte_sucre = true;
}

void Fourmi::deplace(Coord c){
    coords = c;
}