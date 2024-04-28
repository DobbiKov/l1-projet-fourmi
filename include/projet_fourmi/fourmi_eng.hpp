#ifndef FOURMI_ENG_HPP
#define FOURMI_ENG_HPP

#include <vector>
#include <projet_fourmi/fourmi.hpp>

/// @brief Engine for the fourmis
class FourmiEng{
private: 
    std::vector<Fourmi> fourmis;

    int number_of_fourmis;
    vector<int> numbers_of_fourmi_by_colony;
public:
    FourmiEng(std::vector<Fourmi> _fourmis);
    std::vector<Fourmi> getFourmis() const { return fourmis; }

    Fourmi loadFourmi(int num) const;
    Fourmi loadFourmi(Fourmi f) const;
    void changeFourmi(Fourmi f);

    int getNumberOfFourmi() const { return number_of_fourmis; }
    int getNumberOfFourmiInColony(int colony) const { return numbers_of_fourmi_by_colony[colony]; }

    void killFourmi(Fourmi &f);
    Fourmi birthFourmi(Fourmi f);
};

#endif