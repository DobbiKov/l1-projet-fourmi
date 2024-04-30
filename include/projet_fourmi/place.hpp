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
    int getNidColonyId() const;

    bool containSugar() const;
    bool containNid() const;
    bool estSurUnePiste(int colony) const;
    bool estSurUneAnyPiste() const;

    int getColonyOfThePiste() const;

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

/// @brief replaces the given fourmi from the one place to the other
/// @param f fourmi
/// @param from place from which we replace fourmi
/// @param to place where we replace fourmi
void replaceFourmi(Fourmi& f, Place& from, Place& to);

/// @brief returns if the place is closer to the nid than the other
/// @param p1 place 1
/// @param p2 place 2
/// @return returns true if place 1 is closer to the nid than the place 2
bool isTheClosestNid(const Place& p1, const Place& p2);
/// @brief returns if the place is farer to the nid than the other
/// @param p1 place 1
/// @param p2 place 2
/// @return returns true if place 1 is farer to the nid than the place 2
bool isTheFarestNid(const Place& p1, const Place& p2);

/// @brief says whether the place is closer to the nid of of the given colony than the other
/// @param p1 place 1
/// @param p2 place 2
/// @param colony colony
/// @return true if place 1 is closer to the nid of the given colony, false in the other case
bool isTheClosestNidByColony(const Place& p1, const Place& p2, int colony);
/// @brief says whether the place is farer to the nid of of the given colony than the other
/// @param p1 place 1
/// @param p2 place 2
/// @param colony colony
/// @return true if place 1 is farer to the nid of the given colony, false in the other case
bool isTheFarestNidByColony(const Place& p1, const Place& p2, int colony);
/// @brief returns the place among the given ones with the biggest amount of pheromons of the nid
/// @param places set of places
/// @return the place with the biggest amount of pheromons of the nid
Place closestPlaceToTheNid(vector<Place> places);
/// @brief returns the place among the given ones with the biggest amount of pheromons of the nid of the given colony
/// @param places set of places
/// @param colony colony
/// @return the place with the biggest amount of pheromons of the nid of the given colony
Place closestPlaceToTheNidByColony(vector<Place> places, int colony);

/// gets as a parameter vector of places and returns only the empty ones
vector<Place> emptyPlaces(vector<Place> places);

/// @brief returns whether a place is closer to the sugar using pheromons of the sugar of the given colony
/// @param p1 place 1
/// @param p2 place 2
/// @param colony colony
/// @return true if place 1 has more pheromons of the sugar of the given colony than the place 2, false in the other case
bool isTheClosestSugar(const Place& p1, const Place& p2, int colony);
/// @brief returns whether a place is farer to the sugar using pheromons of the sugar of the given colony
/// @param p1 place 1
/// @param p2 place 2
/// @param colony colony
/// @return true if place 1 has less pheromons of the sugar of the given colony than the place 2, false in the other case
bool isTheFarestSugar(const Place& p1, const Place& p2, int colony);
/// @brief returns the closer place to the sugar using pheromons of the sugar of the given colony
/// @param places set of places
/// @param colony colony
/// @return place with the biggest amount of pheromons of sugar of the given colony
Place closestPlaceToTheSugar(vector<Place> places, int colony);

/// @brief tells whether fourmi can move to the place
/// @param f fourmi
/// @param p place
/// @return true if he can and false in the other case
bool canFourmiMoveToPlace(const Fourmi &f, const Place &p);

#endif