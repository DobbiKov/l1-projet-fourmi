#ifndef FOURMI_HPP
#define FOURMI_HPP

#include <projet_fourmi/coord.hpp>

enum class Caste { ouvrier, guerrier, reproductrice };

class Fourmi{
private:
    Coord coords;
    int num;
    bool porte_sucre;
    bool is_alive;
    int colony;
    Caste caste;
public: 
    Fourmi(Coord c, int id, int colony, Caste caste);
    Coord getCoords() const;
    int getNum() const;
    int getColony() const;
    Caste getCaste() const;
    bool isAlive() const;
    bool porteSucre() const;
    void prendSucre();
    void poseSucre();
    void deplace(Coord c);
    bool searchingSugar() const;
    bool goingToTheNid() const;
    void killFourmi();
};

vector<Fourmi> createListFourmis(EnsCoord ens, int colony, Caste caste);

bool operator==(const Fourmi& f1, const Fourmi& f2);
bool operator!=(const Fourmi& f1, const Fourmi& f2);

/// @brief function throws error if the colony is incorrect and does nothing in the other case
/// @param colony 
void verify_colony(int colony);

/// @brief says whether given casts athorised to take sugar
/// @param caste 
/// @return true if the cast is authorised to take sugar and false in the other case
bool canCasteTakeSugar(Caste caste);

bool canCasteBattle(Caste caste);

bool canCasteStayAtTheNid(Caste caste);

/// @brief gives cast (enum class) by number
/// @param num 
/// @return caste
Caste getCastByNumber(int num);

#endif