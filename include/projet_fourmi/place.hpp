#ifndef PLACE_HPP
#define PLACE_HPP

#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>

using namespace std;

class Place{
private:
    int fourmi_id;
    float phero_suagar;
    float phero_nid;
    Coord coords;

    int sugar;
    bool has_nid;
public: 
    Place(Coord c):coords{c}, fourmi_id{-1}, phero_suagar{0}, phero_nid{0}, sugar{0}, has_nid{false} {}
    Coord getCoords() const;
    float getPheroSugar() const;
    float getPheroNid() const;
    int getFourmiID() const;

    bool containSugar() const;
    bool containNid() const;
    bool estSurUnePiste() const;

    void setSugar();
    void removeSugar();
    void setNid();
    void setFourmi();
    void removeFourmi();
    void setPheroNid(float intensity);
    void setPheroSugar();
    void decreasePheroSugar();
};

void replaceFourmi(Fourmi f, Place from, Place to);
bool isEmpty(Place p);
bool isTheClosestNid(Place p1, Place p2);

#endif