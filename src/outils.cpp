#include <projet_fourmi/outils.hpp>
#include <vector>
#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/consts.hpp>

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

float val_abs(float num){
    return (num >= 0) ? num : -num;
}

bool float_equal(float a, float b){
    float epsilon = 1.e-10;
    return val_abs(a - b) < epsilon;
}

vector<int> sort_by(vector<int> ints, vector<float> floats){
    if(ints.size() != floats.size()) throw invalid_argument("The sizes of vectors aren't the same!");
    int smallest_int = ints[0];
    int smallest_int_idx = 0;
    int smallest_float = floats[0];

    vector<int> res{{}};
    
    for(int i = 0; i < ints.size(); i++){
        if(ints.size() == 0) break;

        smallest_int = ints[0];
        smallest_int_idx = 0;
        smallest_float = floats[0];

        for(int j = 0; j < ints.size(); j++){
            if(smallest_float > floats[j]){
                smallest_float = floats[j];
                smallest_int = ints[j];
                smallest_int_idx = j;
            }
        }
        res.push_back(smallest_int);
        swap(ints[smallest_int_idx], ints[ints.size()-1]);
        swap(floats[smallest_int_idx], floats[ints.size()-1]);
        ints.pop_back();
        floats.pop_back();

    }
    return res;
}