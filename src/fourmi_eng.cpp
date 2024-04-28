#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/fourmi_eng.hpp>
#include <projet_fourmi/coord.hpp>
#include <vector>

using namespace std;

Fourmi FourmiEng::loadFourmi(int num) const{
    return fourmis[num];
}
Fourmi FourmiEng::loadFourmi(Fourmi f) const{
    return fourmis[f.getNum()];
}
void FourmiEng::changeFourmi(const Fourmi &f){
    fourmis[f.getNum()] = f;
}

void FourmiEng::killFourmi(Fourmi &f){
    f.killFourmi();
    changeFourmi(f);
}
Fourmi FourmiEng::birthFourmi(Fourmi f){
    int new_id = fourmis.size();
    Fourmi new_fourmi = Fourmi(f.getCoords(), new_id);
    fourmis.push_back(new_fourmi);
    return new_fourmi;
}