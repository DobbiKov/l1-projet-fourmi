#ifndef FOURMI_ENG_HPP
#define FOURMI_ENG_HPP

#include <vector>
#include <projet_fourmi/fourmi.hpp>

/// @brief Engine for the fourmis
class FourmiEng{
private: 
    std::vector<Fourmi> fourmis;
    int number_of_fourmis;
public:
    FourmiEng(std::vector<Fourmi> _fourmis): fourmis{_fourmis}, number_of_fourmis{0}{ number_of_fourmis = fourmis.size(); }
    std::vector<Fourmi> getFourmis() const { return fourmis; }

    Fourmi loadFourmi(int num) const;
    Fourmi loadFourmi(Fourmi f) const;
    void changeFourmi(const Fourmi &f);

    int number_of_fourmis() const { return number_of_fourmis; }

    void killFourmi(Fourmi &f);
    Fourmi birthFourmi(Fourmi f);
};

#endif