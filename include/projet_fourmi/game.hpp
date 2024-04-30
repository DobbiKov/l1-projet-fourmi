#ifndef GAME_HPP
#define GAME_HPP

#include "fourmi_eng.hpp"
#include "grille.hpp"

/// @brief Main function of all the game that handles each step of the simulation
/// @param f_eng engine of fourmis
/// @param g grille
/// @param game_count step of the game
void makeGameStep(FourmiEng &f_eng, Grille &g, int &game_count);

/// @brief Makes fourmi move in the random direction
/// @param f fourmi
/// @param f_eng fourmi engine
/// @param g grille
void makeRandomMoveFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);

/// @brief Makes fourmi move move to the place with the biggest phero of the nid
/// @param f fourmi
/// @param f_eng fourmi engine
/// @param g grille
void makeMoveToTheNidFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);

/// @brief Make fourmi move to the place that is closest to the sugar
/// @param f fourmi
/// @param colony colony
/// @param f_eng fourmi engine
/// @param g grille
void makeMoveToThePheroSugarFourmi(Fourmi f, int colony, FourmiEng &f_eng, Grille &g);

/// @brief The fundamental function for the move of fourmi
/// @param f fourmi
/// @param f_eng fourmi engine
/// @param g grille
/// @param move place where to put fourmi
void makeFourmiMoveToPlace(Fourmi &f, FourmiEng &f_eng, Grille &g, Place move);

/// @brief Makes fourmi take sugar
/// @param f fourmi
/// @param f_eng fourmi engine
/// @param g grille
void makeFourmiTakeSugar(Fourmi f, FourmiEng &f_eng, Grille &g);

/// @brief Makes fourmi put sugar
/// @param f fourmi
/// @param f_eng fourmi engine
/// @param g grille
void makeFourmiPutSugar(Fourmi f, FourmiEng &f_eng, Grille &g);

/// @brief Kills fourmi
/// @param f fourmi
/// @param f_eng fourmi engine
/// @param g grille
void killFourmi(Fourmi &f, FourmiEng &f_eng, Grille &g);

/// @brief Handles the battle between two fourmis
/// @param f1 fourmi 1
/// @param f2 fourmi 2
/// @param f_eng fourmi engine
/// @param g grille
void battleTwoFourmis(Fourmi &f1, Fourmi &f2, FourmiEng &f_eng, Grille &g);

/// @brief  Handles the birth of the new fourmi
/// @param f_eng fourmi engine
/// @param g grille
/// @param colony colony in which to birth fourmi
void birthNewFourmi(FourmiEng &f_eng, Grille &g, int colony);

#endif