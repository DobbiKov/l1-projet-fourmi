#include <SFML/Graphics.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/place.hpp>
#include <iostream>
#include <random>
#include <format>
#include "time.h"

const int WINDOW_SIZE = 1024;
const int grid_size = TAILLEGRILLE;
const float scale = WINDOW_SIZE / (TAILLEGRILLE);
const int GAME_SPEED = 5;
const int NEW_SUGAR_APP_SPEED = 50;

void makeGameStep(vector<Fourmi>& fourmis, Grille &g);
void makeRandomMoveFourmi(Fourmi f, vector<Fourmi>& fourmis, Grille &g);
void makeMoveToTheNidFourmi(Fourmi f, vector<Fourmi>& fourmis, Grille &g);
void makeMoveToThePheroSugarFourmi(Fourmi f, vector<Fourmi>& fourmis, Grille &g);
void makeFourmiMoveToPlace(Fourmi &f, vector<Fourmi>& fourmis, Grille &g, Place move);

void makeFourmiTakeSugar(Fourmi f, vector<Fourmi>& fourmis, Grille &g);
void makeFourmiPutSugar(Fourmi f, vector<Fourmi>& fourmis, Grille &g);

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


void makeGameStep(vector<Fourmi>& fourmis, Grille &g, int &game_count){
    if(game_count % NEW_SUGAR_APP_SPEED == 0){
        putSugarInRandomPlace(g);
    }
    g.decreasePheroSugar();
    for(Fourmi f: fourmis){
        if(f.porteSucre()){
            Place p = g.loadPlace(f.getCoords());
            p.setPheroSugar();
            g.changePlace(p);
        }
        if(f.goingToTheNid()){
            if(isNidNeighbour(g, f.getCoords())){
                makeFourmiPutSugar(f, fourmis, g);
                continue;
            }
            makeMoveToTheNidFourmi(f, fourmis, g);
            continue;
        }
        if(f.searchingSugar()){
            if(isSugarNeighbour(g, f.getCoords())){
                makeFourmiTakeSugar(f, fourmis, g);
                continue;
            }
            if(g.loadPlace(f.getCoords()).estSurUnePiste()){
                makeMoveToThePheroSugarFourmi(f, fourmis, g);
                continue;
            }
            makeRandomMoveFourmi(f, fourmis, g);
            continue;
        }
        // makeRandomMoveFourmi(f, fourmis, g);
    }
    game_count++;
}

void makeFourmiTakeSugar(Fourmi f, vector<Fourmi>& fourmis, Grille &g){
    Place p = getNeigbourSugarPlace(g, f.getCoords());
    p.removeSugar();
    g.changePlace(p);
    f.prendSucre();
    fourmis[f.getNum()] = f;
}

void makeFourmiPutSugar(Fourmi f, vector<Fourmi>& fourmis, Grille &g){
    g.poseSugarFromFourmi(f);
    f.poseSucre();
    fourmis[f.getNum()] = f; 
}

void makeMoveToTheNidFourmi(Fourmi f, vector<Fourmi>& fourmis, Grille &g){
    vector<Place> near_places = emptyPlaces( loadPlacesByCoords( g, voisines(f.getCoords()) ) );
    Place move = closestPlaceToTheNid(near_places);
    makeFourmiMoveToPlace(f, fourmis, g, move);
}

void makeMoveToThePheroSugarFourmi(Fourmi f, vector<Fourmi>& fourmis, Grille &g){
    vector<Place> near_places = emptyPlaces( loadPlacesByCoords( g, voisines(f.getCoords()) ) );
    Place move = closestPlaceToTheSugar(near_places);
    makeFourmiMoveToPlace(f, fourmis, g, move);  
}

//makes random move for fourmi updating the state of the program
void makeRandomMoveFourmi(Fourmi f, vector<Fourmi>& fourmis, Grille &g){
    Place move = getNextRandomPlaceToGo(f, g);
    makeFourmiMoveToPlace(f, fourmis, g, move);
}

void makeFourmiMoveToPlace(Fourmi &f, vector<Fourmi>& fourmis, Grille &g, Place move){
        //replace fourmi
        Coord old_coords = f.getCoords();
        Place old_place = g.loadPlace(old_coords);
        Place new_place = g.loadPlace(move.getCoords());
        if(!new_place.isEmpty()) return;

        replaceFourmi(f, old_place, new_place);


        //update places and fourmis
        fourmis[f.getNum()] = f;
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
    Grille grille = initializeGrille(fourmis, sugar_ens, nid_ens);
    int GAME_COUNT = 1;


    int WINDOW_SIZE_FOR_TEXT = 500;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE+WINDOW_SIZE_FOR_TEXT, WINDOW_SIZE), "Simulation");

    window.setFramerateLimit(GAME_SPEED);

    sf::Font f = load_font();

    string text_for_game_count;
    string text_for_amount_of_sugar;

    sf::Text game_count_text = create_text((TAILLEGRILLE+1)*scale, 50.0f, f);
    sf::Text amoun_of_sugar_text = create_text((TAILLEGRILLE+1)*scale, 70.0f, f);


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
            if(p.getFourmiID() != -1 && fourmis[p.getFourmiID()].isAlive()) window.draw(draw_fourmi(c.getLine(), c.getColumn(), fourmis[p.getFourmiID()]));
        }

        text_for_game_count = "Game count: " + to_string(GAME_COUNT);
        game_count_text.setString(text_for_game_count);
        window.draw(game_count_text);

        text_for_amount_of_sugar = "Amount of sugar: " + to_string(grille.getAmountOfSugar());
        amoun_of_sugar_text.setString(text_for_amount_of_sugar);
        window.draw(amoun_of_sugar_text);

        makeGameStep(fourmis, grille, GAME_COUNT);

        window.display();
    }
    return 0;
}
