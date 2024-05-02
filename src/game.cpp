#include <projet_fourmi/game.hpp>
#include <projet_fourmi/outils.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/place.hpp>
#include <iostream>
#include <random>
#include <format>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/fourmi_eng.hpp>
#include <projet_fourmi/team_consts.hpp>

using namespace std;

void birthNewFourmi(FourmiEng &f_eng, Grille &g, int colony){
    EnsCoord coords_around_nid = coordsAroundNid(g.getNid(colony));
    vector<Place> places = emptyPlaces(loadPlacesByCoords(g, coords_around_nid));

    if(places.size() == 0) return; //if there's no empty places

    int idx = rand() % places.size();
    Place new_p = places[idx];

    int cast_n = rand() % NUMBER_OF_CASTES;
    Caste new_caste = getCastByNumber(cast_n);

    Fourmi f = Fourmi(new_p.getCoords(), 0, colony, new_caste);

    Fourmi new_f = f_eng.birthFourmi(f);

    new_p.setFourmi(new_f);

    g.changePlace(new_p);
    areFourmiGrilleCoherent(g, new_f);
    g.descreaseAmountOfSugar(colony, AMOUT_OF_SUGAR_FOR_NEW_FOURMI);
}

void battleTwoFourmis(Fourmi &f1, Fourmi &f2, FourmiEng &f_eng, Grille &g){
    if(f1.porteSucre() && f2.porteSucre()) return;
    if(f1.getColony() == f2.getColony()) return;

    if(!canCasteBattle(f2.getCaste())){
        killFourmi(f2, f_eng, g);
        return;
    }

    int rand_num = rand() % 10;
    if(rand_num >= 5){
        killFourmi(f2, f_eng, g);
        return;
    }
    killFourmi(f1, f_eng, g);
    return;
}

void killFourmi(Fourmi &f, FourmiEng &f_eng, Grille &g){
    Place p = g.loadPlace(f.getCoords());
    f_eng.killFourmi(f);
    p.removeFourmi();
    g.changePlace(p);
}


void makeGameStep(FourmiEng &f_eng, Grille &g, int &game_count){
    makeGameStepSugar(game_count, g); // put sugar in random place

    g.decreasePheroSugar(); // decrease phero sugar each game step

    makeGameStepEachFourmi(f_eng, g); // handling each fourmi

    makeGameStepBirth(f_eng, g); // the handle for birth of fourmis

    game_count++;
}

void makeGameStepSugar(int game_count, Grille &g){
    if(game_count % NEW_SUGAR_APP_SPEED == 0){ // add sugar in random place
        putSugarInRandomPlace(g);
    }
}

void makeGameStepEachFourmi(FourmiEng &f_eng, Grille &g){
    for(int i = 0; i < f_eng.getFourmiTabSize(); i++){ 
        Fourmi f = f_eng.loadFourmi(i);
        makeGameStepForFourmi(f, f_eng, g);
    }
}

void makeGameStepBirth(FourmiEng &f_eng, Grille &g){
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){ 
        bool required_amount_of_sugar = g.getAmountOfSugar(i) >= AMOUT_OF_SUGAR_FOR_NEW_FOURMI;
        bool required_number_of_fourmis = numberOfFourmiInTheNid(g, i) >= 2;
        bool below_maximal_number_of_fourmis = f_eng.getNumberOfFourmiInColony(i) < MAX_NUMBER_OF_FOURMI_IN_COLONY;
        
        if( required_amount_of_sugar
        && required_number_of_fourmis
        && below_maximal_number_of_fourmis){
            birthNewFourmi(f_eng, g, i);
        }
    }
}

void makeGameStepForFourmi(Fourmi f, FourmiEng &f_eng, Grille &g){
    if(!f.isAlive()) return;

    if(isFourmiNeighbour(g, f.getCoords()) && canCasteBattle(f.getCaste())){ // if fourmi is near an other fourmi and they can fight
        Place p = getNeigbourFourmiPlace(g, f.getCoords());
        Fourmi f2 = f_eng.loadFourmi(p.getFourmiID());
        if(f.getColony() != f2.getColony() && f.isAlive() && f2.isAlive()){
            battleTwoFourmis(f, f2, f_eng, g);
        }
    }
    if(!f.isAlive()) return;

    if(canCasteBattle( f.getCaste() )){ // if fourmi can fight and he's looking for another fourmi to kill
        Place p = g.loadPlace(f.getCoords());
        if(p.estSurUneAnyPiste()){ // if fourmi is sur une any piste
            vector<int> found_colonies = get_numbers_except(p.getColoniesOfThePiste(), f.getColony());

            if(found_colonies.size() == 0){ // if it's une piste of his own colony, he moves randomly
                makeRandomMoveFourmi(f, f_eng, g);
                return;
            }
            // he moves along the piste of the found phero sugar
            int chosen_colony = found_colonies[rand() % found_colonies.size()];
            makeMoveToThePheroSugarFourmi(f, chosen_colony, f_eng, g);
            return;
        }else{ // if fourmi isn't sur une any piste
            makeRandomMoveFourmi(f, f_eng, g);
            return;
        }
    }

    if(f.getCaste() == Caste::reproductrice && 
    g.getAmountOfSugar(f.getColony()) >= AMOUT_OF_SUGAR_FOR_NEW_FOURMI){ // if fourmi is reproductive
        // if the fourmi has to go to the fourmi cause the amount of sugar is enough to create new one
        Place p = g.loadPlace(f.getCoords());
        if(p.containNid()) return;
        if(isFourmiNearItsNid(f, g)){ // if fourmi near it's nid, he steps in
            Place nid_place = getNeigbourNidPlace(g, f.getCoords());
            if(nid_place.getFourmiID() == -1) makeFourmiMoveToPlace(f, f_eng, g, nid_place);
            else makeMoveToTheNidFourmi(f, f_eng, g);
            return;
        }
        // in other case he moves towards the nid
        makeMoveToTheNidFourmi(f, f_eng, g);
        return;
    }

    if(f.porteSucre()){
        Place p = g.loadPlace(f.getCoords());
        p.setPheroSugar(f.getColony());
        g.changePlace(p);
    }
    if(f.goingToTheNid()){
        if(isFourmiNearItsNid(f, g)){
            makeFourmiPutSugar(f, f_eng, g);
            return;
        }
        makeMoveToTheNidFourmi(f, f_eng, g);
        return;
    }
    if(f.searchingSugar()){
        if(isSugarNeighbour(g, f.getCoords())){
            makeFourmiTakeSugar(f, f_eng, g);
            return;
        }
        if(g.loadPlace(f.getCoords()).estSurUnePiste(f.getColony())){
            makeMoveToThePheroSugarFourmi(f, f.getColony(), f_eng, g);
            return;
        }
        makeRandomMoveFourmi(f, f_eng, g);
        return;
    }
}

void makeFourmiTakeSugar(Fourmi f, FourmiEng &f_eng, Grille &g){
    Place p = getNeigbourSugarPlace(g, f.getCoords());
    p.removeSugar();
    g.changePlace(p);
    f.prendSucre();
    f_eng.changeFourmi(f);
}

void makeFourmiPutSugar(Fourmi f, FourmiEng &f_eng, Grille &g){
    g.poseSugarFromFourmi(f);
    f.poseSucre();
    f_eng.changeFourmi(f); 
}

void makeMoveToTheNidFourmi(Fourmi f, FourmiEng &f_eng, Grille &g){
    vector<Place> near_places = emptyPlaces( loadPlacesByCoords( g, voisines(f.getCoords()) ) );
    if(near_places.size() == 0){
        cout << "The fourmi didn't find a way to go to the sugar!" << endl;
        return;
    }
    Place move = closestPlaceToTheNidByColony(near_places, f.getColony());
    makeFourmiMoveToPlace(f, f_eng, g, move);
}

void makeMoveToThePheroSugarFourmi(Fourmi f, int colony, FourmiEng &f_eng, Grille &g){
    verify_colony(colony);
    vector<Place> near_places = emptyPlaces( loadPlacesByCoords( g, voisines(f.getCoords()) ) );
    if(near_places.size() == 0){
        cout << "The fourmi didn't find a way to go to the sugar!" << endl;
        return;
    }
    Place move = closestPlaceToTheSugar(near_places, colony);
    makeFourmiMoveToPlace(f, f_eng, g, move);  
}

//makes random move for fourmi updating the state of the program
void makeRandomMoveFourmi(Fourmi f, FourmiEng &f_eng, Grille &g){
    try{
        Place move = getNextRandomPlaceToGo(f, g);
        makeFourmiMoveToPlace(f, f_eng, g, move);
    }catch(runtime_error e){
        cout << "The fourmi didn't find a place to move" << endl;
        return;
    }
}

void makeFourmiMoveToPlace(Fourmi &f, FourmiEng &f_eng, Grille &g, Place move){
        //replace fourmi
        Coord old_coords = f.getCoords();
        Place old_place = g.loadPlace(old_coords);
        Place new_place = g.loadPlace(move.getCoords());
        if(!canFourmiMoveToPlace(f, move)) return;

        replaceFourmi(f, old_place, new_place);


        //update places and fourmis
        f_eng.changeFourmi(f);
        g.changePlace(old_place);
        g.changePlace(new_place);

        //check if the state of the program is correct
        areFourmiGrilleCoherent(g, f);
}