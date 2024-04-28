#include <SFML/Graphics.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/place.hpp>
#include <iostream>
#include <random>
#include <format>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/fourmi_eng.hpp>
#include "time.h"

void makeGameStep(FourmiEng &f_eng, Grille &g, int &game_count);
void makeRandomMoveFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeMoveToTheNidFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeMoveToThePheroSugarFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeFourmiMoveToPlace(Fourmi &f, FourmiEng &f_eng, Grille &g, Place move);

void makeFourmiTakeSugar(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeFourmiPutSugar(Fourmi f, FourmiEng &f_eng, Grille &g);

void birthNewFourmi(FourmiEng &f_eng, Grille &g);

sf::RectangleShape draw_empty_square(int row, int column, const Place &p, float color=12.0){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));
    // rectangle.setFillColor(sf::Color::Black);

    int alpha = (int)(p.getPheroNid()*100);
    rectangle.setFillColor(sf::Color(120, 120, 120, alpha));

    if(p.estSurUnePiste()){
        int phero_sug_alpha = p.getPheroSugar();
        rectangle.setFillColor(sf::Color(0, 0, 255, phero_sug_alpha));
    }
    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

    return rectangle;
}
sf::RectangleShape draw_nid(int row, int column, const Place &p, float color=12.0){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

    return rectangle;
}

sf::CircleShape draw_fourmi(int row, int column, Fourmi f, float color=12.0){
    sf::CircleShape triangle(scale/2, 3);

    triangle.setFillColor(sf::Color::Green);
    if(f.searchingSugar()){
        triangle.setFillColor(sf::Color::Red);
    }
    triangle.setPosition(sf::Vector2f(scale*row, scale*column));

    return triangle;
}

sf::CircleShape draw_sugar(int row, int column, float color=12.0){
    sf::CircleShape circle(scale/2);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(sf::Vector2f(scale*row, scale*column));

    return circle;
}

void birthNewFourmi(FourmiEng &f_eng, Grille &g){
    EnsCoord coords_around_nid = coordsAroundNid(g.getNid());
    vector<Place> places = emptyPlaces(loadPlacesByCoords(g, coords_around_nid));

    if(places.size() == 0) return; //if there's no empty places

    int idx = rand() % places.size();
    Place new_p = places[idx];

    Fourmi f = Fourmi(new_p.getCoords(), 0);

    Fourmi new_f = f_eng.birthFourmi(f);

    new_p.setFourmi(new_f);

    g.changePlace(new_p);
    areFourmiGrilleCoherent(g, new_f);
    g.descreaseAmountOfSugar(AMOUT_OF_SUGAR_FOR_NEW_FOURMI);
}


void makeGameStep(FourmiEng &f_eng, Grille &g, int &game_count){
    if(game_count % NEW_SUGAR_APP_SPEED == 0){
        putSugarInRandomPlace(g);
    }
    g.decreasePheroSugar();
    for(Fourmi f: f_eng.getFourmis()){
        if(f.porteSucre()){
            Place p = g.loadPlace(f.getCoords());
            p.setPheroSugar();
            g.changePlace(p);
        }
        if(f.goingToTheNid()){
            if(isNidNeighbour(g, f.getCoords())){
                makeFourmiPutSugar(f, f_eng, g);
                continue;
            }
            makeMoveToTheNidFourmi(f, f_eng, g);
            continue;
        }
        if(f.searchingSugar()){
            if(isSugarNeighbour(g, f.getCoords())){
                makeFourmiTakeSugar(f, f_eng, g);
                continue;
            }
            if(g.loadPlace(f.getCoords()).estSurUnePiste()){
                makeMoveToThePheroSugarFourmi(f, f_eng, g);
                continue;
            }
            makeRandomMoveFourmi(f, f_eng, g);
            continue;
        }
        // makeRandomMoveFourmi(f, fourmis, g);
    }
    if(g.getAmountOfSugar() >= AMOUT_OF_SUGAR_FOR_NEW_FOURMI){
        birthNewFourmi(f_eng, g);
    }
    game_count++;
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
    Place move = closestPlaceToTheNid(near_places);
    makeFourmiMoveToPlace(f, f_eng, g, move);
}

void makeMoveToThePheroSugarFourmi(Fourmi f, FourmiEng &f_eng, Grille &g){
    vector<Place> near_places = emptyPlaces( loadPlacesByCoords( g, voisines(f.getCoords()) ) );
    Place move = closestPlaceToTheSugar(near_places);
    makeFourmiMoveToPlace(f, f_eng, g, move);  
}

//makes random move for fourmi updating the state of the program
void makeRandomMoveFourmi(Fourmi f, FourmiEng &f_eng, Grille &g){
    Place move = getNextRandomPlaceToGo(f, g);
    makeFourmiMoveToPlace(f, f_eng, g, move);
}

void makeFourmiMoveToPlace(Fourmi &f, FourmiEng &f_eng, Grille &g, Place move){
        //replace fourmi
        Coord old_coords = f.getCoords();
        Place old_place = g.loadPlace(old_coords);
        Place new_place = g.loadPlace(move.getCoords());
        if(!new_place.isEmpty()) return;

        replaceFourmi(f, old_place, new_place);


        //update places and fourmis
        f_eng.changeFourmi(f);
        g.changePlace(old_place);
        g.changePlace(new_place);

        //check if the state of the program is correct
        areFourmiGrilleCoherent(g, f);
}

sf::Font load_font(){
    sf::Font f; 

    if (!f.loadFromFile("./fonts/Roboto-Regular.ttf"))
    {
        std::cerr << ".Error while loading font" << std::endl;
        throw runtime_error("Error while loading font");
    }
    return f;
}

sf::Text create_text(float line, float column, const sf::Font &f){
    sf::Text text;
    text.setFont(f);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);
    text.setPosition(line, column);
    text.setStyle(sf::Text::Bold);
    return text;
}

int main()
{
    srand (time(NULL));
    // initial grid
    vector<Coord> nid_coords{{
        Coord(4, 7),
        Coord(4, 8),
        Coord(5, 7),
        Coord(5, 8)
    }};
    EnsCoord nid_ens = EnsCoord(nid_coords);

    vector<Coord> sugar_coords{{
        // Coord(2, 7),
        // Coord(4, 12),
        // Coord(11, 7),
        // Coord(10, 2)
    }};
    EnsCoord sugar_ens = EnsCoord(sugar_coords);

    EnsCoord fourmis_coords = coordsAroundNid(nid_ens);
    vector<Fourmi> fourmis{{}};

    for(int i = 0; i < fourmis_coords.taille(); i++){
        Fourmi f = Fourmi(fourmis_coords.ieme(i), i);
        fourmis.push_back(f);
    }
    FourmiEng f_eng = FourmiEng(fourmis);
    Grille grille = initializeGrille(f_eng.getFourmis(), sugar_ens, nid_ens);
    int GAME_COUNT = 1;


    int WINDOW_SIZE_FOR_TEXT = 500;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE+WINDOW_SIZE_FOR_TEXT, WINDOW_SIZE), "Simulation");

    window.setFramerateLimit(GAME_SPEED);

    sf::Font font = load_font();

    string text_for_game_count;
    string text_for_amount_of_sugar;
    string text_for_number_of_fourmis;

    sf::Text game_count_text = create_text((TAILLEGRILLE+1)*scale, 50.0f, font);
    sf::Text amoun_of_sugar_text = create_text((TAILLEGRILLE+1)*scale, 70.0f, font);
    sf::Text number_of_fourmis_text = create_text((TAILLEGRILLE+1)*scale, 90.0f, font);


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for(Place p: grille.getPlaces()){
            Coord c = p.getCoords();
            window.draw(draw_empty_square(c.getLine(), c.getColumn(), p));
            if(p.isEmpty()) continue;
            if(p.containNid()) window.draw(draw_nid(c.getLine(), c.getColumn(), p));
            if(p.containSugar()) window.draw(draw_sugar(c.getLine(), c.getColumn()));
            if(p.getFourmiID() != -1 && f_eng.loadFourmi(p.getFourmiID()).isAlive()) window.draw(draw_fourmi(c.getLine(), c.getColumn(), f_eng.loadFourmi(p.getFourmiID()) ));
        }

        text_for_game_count = "Game count: " + to_string(GAME_COUNT);
        game_count_text.setString(text_for_game_count);
        window.draw(game_count_text);

        text_for_amount_of_sugar = "Amount of sugar: " + to_string(grille.getAmountOfSugar());
        amoun_of_sugar_text.setString(text_for_amount_of_sugar);
        window.draw(amoun_of_sugar_text);

        text_for_number_of_fourmis = "Number of fourmis: " + to_string(f_eng.getNumberOfFourmi());
        number_of_fourmis_text.setString(text_for_number_of_fourmis);
        window.draw(number_of_fourmis_text);

        makeGameStep(f_eng, grille, GAME_COUNT);

        window.display();
    }
    return 0;
}
