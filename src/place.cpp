#include <vector>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/fourmi.hpp>

using namespace std;

Place::Place(Coord c):fourmi_id{-1}, phero_sugar{0}, phero_nid{0}, coords{c}, sugar{0}, has_nid{false} {}

Coord Place::getCoords() const{
    return coords;
}

float Place::getPheroSugar() const{
    return phero_sugar;
}

float Place::getPheroNid() const{
    return phero_nid;
}
int Place::getFourmiID() const{
    return fourmi_id;
}

bool Place::containSugar() const{
    return sugar > 0;
}
bool Place::containNid() const{
    return has_nid;
}
bool Place::estSurUnePiste() const{
    return phero_sugar > 0;
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

void Place::setNid(){
    if(!isEmpty())
        throw runtime_error("The place isn't empty!");
    has_nid = true;
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

void Place::setPheroSugar(){
    phero_sugar = MAX_PHERO_SUGAR_INTENSITY;
}

void Place::decreasePheroSugar(){
    if(phero_sugar == 0) return;
    phero_sugar -= AMOUT_OF_PHERO_SUGAR_TO_REMOVE;
    if(phero_sugar < 0)
        phero_sugar = 0;
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