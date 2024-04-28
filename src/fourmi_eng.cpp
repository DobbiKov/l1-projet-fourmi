#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/fourmi_eng.hpp>
#include <projet_fourmi/coord.hpp>
#include <vector>

using namespace std;

Fourmi FourmiEng::loadFourmi(int num) const{
    if(num >= fourmis.size()) throw invalid_argument("Index is out of range of the list of fourmis!");
    return fourmis[num];
}
Fourmi FourmiEng::loadFourmi(Fourmi f) const{
    if(f.getNum() >= fourmis.size()) throw invalid_argument("The ant isn't in list of fourmis!");
    return fourmis[f.getNum()];
}
void FourmiEng::changeFourmi(Fourmi f){
    if(f.getNum() >= fourmis.size()) throw invalid_argument("The ant isn't in list of fourmis!");
    fourmis[f.getNum()] = f;
}

void FourmiEng::killFourmi(Fourmi &f){
    f.killFourmi();
    number_of_fourmis--;
    changeFourmi(f);
}
Fourmi FourmiEng::birthFourmi(Fourmi f){
    int new_id = fourmis.size();
    Fourmi new_fourmi = Fourmi(f.getCoords(), new_id);
    fourmis.push_back(new_fourmi);
    number_of_fourmis++;
    return new_fourmi;
}