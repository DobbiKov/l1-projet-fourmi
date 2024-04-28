#ifndef PLACE_HPP
#define PLACE_HPP

#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/fourmi.hpp>

using namespace std;

class Place{
private:
    int fourmi_id;
    vector<float> phero_sugar_by_colony;
    float phero_nid;
    vector<float> phero_nid_by_colony;
    Coord coords;

    int sugar;
    int colony_nid;
public: 
    Place(Coord c);
    Coord getCoords() const;
    float getPheroSugar(int colony) const;
    float getPheroNid() const;
    float getPheroNidByColony(int colony) const;
    int getFourmiID() const;
    int getColonyId() const;

    bool containSugar() const;
    bool containNid() const;
    bool estSurUnePiste(int colony) const;

    void setSugar();
    void removeSugar();
    void setNid(int colony_id);
    void setFourmi(Fourmi f);
    void removeFourmi();
    void setPheroNid(float intensity);
    void setPheroNidByColony(int colony, float intensity);
    void setPheroSugar(int colony);
    void decreasePheroSugar();

    bool isEmpty() const;
};

void replaceFourmi(Fourmi& f, Place& from, Place& to);

bool isTheClosestNid(const Place& p1, const Place& p2);
bool isTheFarestNid(const Place& p1, const Place& p2);

bool isTheClosestNidByColony(const Place& p1, const Place& p2, int colony);
bool isTheFarestNidByColony(const Place& p1, const Place& p2, int colony);
Place closestPlaceToTheNid(vector<Place> places);
Place closestPlaceToTheNidByColony(vector<Place> places, int colony);

/// gets as a parameter vector of places and returns only the empty ones
vector<Place> emptyPlaces(vector<Place> places);

bool isTheClosestSugar(const Place& p1, const Place& p2, int colony);
bool isTheFarestSugar(const Place& p1, const Place& p2, int colony);
Place closestPlaceToTheSugar(vector<Place> places, int colony);

#endif