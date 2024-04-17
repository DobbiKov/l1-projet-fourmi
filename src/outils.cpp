#include <projet_fourmi/outils.hpp>
#include <vector>
#include <projet_fourmi/coord.hpp>

using namespace std;

bool operator==(vector<Coord> v1, vector<Coord> v2){
    if(v1.size() != v2.size()) return false;
    for(int i = 0; i < v1.size(); i++){
        if(v1[i] != v2[i])
            return false;
    }
    return true;
}

bool operator!=(vector<Coord> v1, vector<Coord> v2){
    if(v1.size() != v2.size()) return true;
    for(int i = 0; i < v1.size(); i++){
        if(v1[i] != v2[i])
            return true;
    }
    return false;
}