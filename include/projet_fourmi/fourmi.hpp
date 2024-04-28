#ifndef FOURMI_HPP
#define FOURMI_HPP

#include <projet_fourmi/coord.hpp>

class Fourmi{
private:
    Coord coords;
    int num;
    bool porte_sucre;
    bool is_alive;
    int colony;
public: 
    Fourmi(Coord c, int id, int colony);
    Coord getCoords() const;
    int getNum() const;
    int getColony() const;
    bool isAlive() const;
    bool porteSucre() const;
    void prendSucre();
    void poseSucre();
    void deplace(Coord c);
    bool searchingSugar() const;
    bool goingToTheNid() const;
    void killFourmi();
};

vector<Fourmi> createListFourmis(EnsCoord ens);

bool operator==(const Fourmi& f1, const Fourmi& f2);
bool operator!=(const Fourmi& f1, const Fourmi& f2);

#endif