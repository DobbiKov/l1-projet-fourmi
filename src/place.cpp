#include <vector>
#include <projet_fourmi/outils.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/team_consts.hpp>

using namespace std;

Place::Place(Coord c):fourmi_id{-1}, phero_sugar_by_colony{vector<float>(NUMBER_OF_COLONIES)}, phero_nid{0}, phero_nid_by_colony{vector<float>(NUMBER_OF_COLONIES)}, coords{c}, sugar{0}, colony_nid{-1} {
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        phero_nid_by_colony[i] = 0.0f;
        phero_sugar_by_colony[i] = 0.0f;
    }
}

Coord Place::getCoords() const{
    return coords;
}

float Place::getPheroSugar(int colony) const{
    return phero_sugar_by_colony[colony];
}

float Place::getPheroNid() const{
    return phero_nid;
}
float Place::getPheroNidByColony(int colony) const{
    return phero_nid_by_colony[colony];
}
int Place::getFourmiID() const{
    return fourmi_id;
}

int Place::getColonyId() const{
    return colony_nid;
}

bool Place::containSugar() const{
    return sugar > 0;
}
bool Place::containNid() const{
    return colony_nid != -1;
}
bool Place::estSurUnePiste(int colony) const{
    return phero_sugar_by_colony[colony] > 0;
}

void Place::setSugar(){
    if(!isEmpty())
        throw runtime_error("The place isn't empty!");
    sugar = AMOUNT_OF_SUGAR_TO_SET;
}

void Place::removeSugar(){
    if(!containSugar())
        throw runtime_error("The place doesn't contain sugar!");
    sugar -= AMOUT_OF_SUGAR_TO_REMOVE;
    if(sugar < 0)
        sugar = 0;
}

void Place::setNid(int colony_id){
    if(!isEmpty())
        throw runtime_error("The place isn't empty!");
    colony_nid = colony_id;
}

void Place::setFourmi(Fourmi f){
    if(!isEmpty())
        throw runtime_error("The place isn't empty!");
    if(f.getCoords() != getCoords())
        throw invalid_argument("The ant isn't placed at these coordinates!");
    fourmi_id = f.getNum();
}

void Place::removeFourmi(){
    if(getFourmiID() == -1)
        throw runtime_error("The place doesn't contain any ant!");
    fourmi_id = -1;
}

void Place::setPheroNid(float intensity){
    phero_nid = intensity;
}

void Place::setPheroNidByColony(int colony, float intensity){
    phero_nid_by_colony[colony] = intensity;
}

void Place::setPheroSugar(int colony){
    phero_sugar_by_colony[colony] = MAX_PHERO_SUGAR_INTENSITY;
}

void Place::decreasePheroSugar(){
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        if(phero_sugar_by_colony[i] == 0) continue;
        phero_sugar_by_colony[i] -= AMOUT_OF_PHERO_SUGAR_TO_REMOVE;
        if(phero_sugar_by_colony[i] < 0)
            phero_sugar_by_colony[i] = 0;
    }
}

bool Place::isEmpty() const{
    return !containSugar() && !containNid() && getFourmiID() == -1;
}

void replaceFourmi(Fourmi& f, Place& from, Place& to){
    if(!to.isEmpty())
        throw invalid_argument("The place where you want to replace the ant to isn't empty!");
    if(from.getFourmiID() != f.getNum())
        throw invalid_argument("The place doesn't contain this ant!");
    if(from.getCoords() == to.getCoords())
        throw invalid_argument("The same places were provided!");


    f.deplace(to.getCoords());
    to.setFourmi(f);
    from.removeFourmi();
}

bool isTheClosestNid(const Place& p1, const Place& p2){
    return p1.getPheroNid() >= p2.getPheroNid();
}
bool isTheFarestNid(const Place& p1, const Place& p2){
    return p1.getPheroNid() <= p2.getPheroNid();
}
bool isTheClosestNidByColony(const Place& p1, const Place& p2, int colony){
    return p1.getPheroNidByColony(colony) >= p2.getPheroNidByColony(colony);
}
bool isTheFarestNidByColony(const Place& p1, const Place& p2, int colony){
    return p1.getPheroNidByColony(colony) <= p2.getPheroNidByColony(colony);
}

bool isTheClosestSugar(const Place& p1, const Place& p2, int colony){
    return p1.getPheroSugar(colony) >= p2.getPheroSugar(colony);
}
bool isTheFarestSugar(const Place& p1, const Place& p2, int colony){
    return p1.getPheroSugar(colony) <= p2.getPheroSugar(colony);
}

Place closestPlaceToTheNid(vector<Place> places){
    int count = places.size()-1;
    while(places.size() > 1){
        if(count == 0) count = places.size()-1;
        //if the place isn't empty, the fourmi can't go there, we remove this place
        if(!places[count].isEmpty()){
            swap(places[count], places[places.size()-1]);
            places.pop_back();
            count--;
            continue;
        }
        if(isTheFarestNid(places[count], places[count-1])){
            swap(places[count], places[places.size()-1]);
            places.pop_back();
        }else{
            swap(places[count-1], places[places.size()-1]);
            places.pop_back();
        }
        count--;
    }
    return places[0];
}

Place closestPlaceToTheNidByColony(vector<Place> places, int colony){
    int count = places.size()-1;
    while(places.size() > 1){
        if(count == 0) count = places.size()-1;
        //if the place isn't empty, the fourmi can't go there, we remove this place
        if(!places[count].isEmpty()){
            swap(places[count], places[places.size()-1]);
            places.pop_back();
            count--;
            continue;
        }
        if(isTheFarestNidByColony(places[count], places[count-1], colony)){
            swap(places[count], places[places.size()-1]);
            places.pop_back();
        }else{
            swap(places[count-1], places[places.size()-1]);
            places.pop_back();
        }
        count--;
    }
    return places[0];
}

Place closestPlaceToTheSugar(vector<Place> places, int colony){
    int count = places.size()-1;
    while(places.size() > 1){
        if(count == 0) count = places.size()-1;
        //if the place isn't empty, the fourmi can't go there, we remove this place
        if(!places[count].isEmpty()){
            swap(places[count], places[places.size()-1]);
            places.pop_back();
            count--;
            continue;
        }

        if(isTheFarestSugar(places[count], places[count-1], colony) && isTheClosestNidByColony(places[count], places[count-1], colony)){
            swap(places[count], places[places.size()-1]);
            places.pop_back();
        }else{
            swap(places[count-1], places[places.size()-1]);
            places.pop_back();
        }
        count--;
    }
    return places[0];
}

vector<Place> emptyPlaces(vector<Place> places){
    vector<Place> res{{}};
    for(Place p: places){
        if(!p.isEmpty()) continue;

        res.push_back(p);
    }
    return res;
}