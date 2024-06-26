#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/fourmi_eng.hpp>
#include <projet_fourmi/coord.hpp>
#include <projet_fourmi/team_consts.hpp>
#include <projet_fourmi/grille.hpp>

#include <vector>

using namespace std;

FourmiEng::FourmiEng(std::vector<Fourmi> _fourmis): fourmis{_fourmis}, number_of_fourmis{0}, numbers_of_fourmi_by_colony{vector<int>(NUMBER_OF_COLONIES)}{ 
    number_of_fourmis = fourmis.size(); 
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        numbers_of_fourmi_by_colony[i] = 0;
    }
    for(Fourmi f: _fourmis){
        numbers_of_fourmi_by_colony[f.getColony()]++;
    }
}

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
    numbers_of_fourmi_by_colony[f.getColony()]--;
    changeFourmi(f);
}
Fourmi FourmiEng::birthFourmi(Fourmi f){
    int new_id = fourmis.size();
    Fourmi new_fourmi = Fourmi(f.getCoords(), new_id, f.getColony(), f.getCaste());
    fourmis.push_back(new_fourmi);
    number_of_fourmis++;
    numbers_of_fourmi_by_colony[f.getColony()]++;
    return new_fourmi;
}

FourmiEng initializeFourmiEng(){
    int f_id_count = 0;
    vector<Fourmi> fourmis{{}};
    for(int colony = 0; colony < NUMBER_OF_COLONIES; colony++){
        EnsCoord fourmis_coords = coordsAroundNid(NIDS_COORDS[colony]);

        int cast_devider = fourmis_coords.taille() / 3;
        int cast = 0;
        for(int i = 0; i < fourmis_coords.taille(); i++){
            if(i > 0 && i % cast_devider == 0) cast++;
            Fourmi f = Fourmi(fourmis_coords.ieme(i), f_id_count, colony, getCastByNumber(cast));
            fourmis.push_back(f);
            f_id_count++;
        }
    }

    FourmiEng f_eng = FourmiEng(fourmis);
    return f_eng;
}