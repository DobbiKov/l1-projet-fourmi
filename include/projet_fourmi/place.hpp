#ifndef PLACE_HPP
#define PLACE_HPP

#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>

const int AMOUNT_OF_SUGAR_TO_SET = 60;
const int AMOUT_OF_SUGAR_TO_REMOVE = 10;

const float MAX_PHERO_SUGAR_INTENSITY = 5;
const float AMOUT_OF_PHERO_SUGAR_TO_REMOVE = 1;

using namespace std;

class Place{
private:
    int fourmi_id;
    float phero_sugar;
    float phero_nid;
    Coord coords;

    int sugar;
    bool has_nid;
    bool is_alive;
public: 
    Place(Coord c);
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
    void setFourmi(Fourmi f);
    void removeFourmi();
    void setPheroNid(float intensity);
    void setPheroSugar();
    void decreasePheroSugar();

    bool isEmpty() const;
};

void replaceFourmi(Fourmi& f, Place& from, Place& to);
bool isTheClosestNid(const Place& p1, const Place& p2);
bool isTheFarestNid(const Place& p1, const Place& p2);
Place closestPlaceToTheNid(vector<Place> places);

//gets as a parameter vector of places and returns only the empty ones
vector<Place> emptyPlaces(vector<Place> places);

#endif