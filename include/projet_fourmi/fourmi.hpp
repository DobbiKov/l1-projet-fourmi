#ifndef FOURMI_HPP
#define FOURMI_HPP

#include <projet_fourmi/coord.hpp>

class Fourmi{
private:
    Coord coords;
    int num;
    bool porte_sucre;
public: 
    Fourmi(Coord c, int id);
    Coord getCoords() const;
    int getNum() const;
    bool porteSucre() const;
    void prendSucre();
    void poseSucre();
    void deplace(Coord c);
};

#endif