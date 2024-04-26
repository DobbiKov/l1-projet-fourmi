#include <SFML/Graphics.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/place.hpp>
#include <iostream>
#include <random>
#include "time.h"

const int WINDOW_SIZE = 1024;
const int grid_size = TAILLEGRILLE;
const float scale = WINDOW_SIZE / (TAILLEGRILLE);
const int GAME_SPEED = 5;

sf::RectangleShape draw_empty_square(int row, int column, float color=12.0){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

    return rectangle;
}
sf::RectangleShape draw_nid(int row, int column, float color=12.0){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

    return rectangle;
}

sf::CircleShape draw_fourmi(int row, int column, float color=12.0){
    sf::CircleShape triangle(scale/2, 3);
    triangle.setFillColor(sf::Color::Green);
    triangle.setPosition(sf::Vector2f(scale*row, scale*column));

    return triangle;
}

sf::CircleShape draw_sugar(int row, int column, float color=12.0){
    sf::CircleShape circle(scale/2);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(sf::Vector2f(scale*row, scale*column));

    return circle;
}

void makeGameStep(vector<Fourmi>& fourmis, Grille &g){
    for(Fourmi f: fourmis){
        EnsCoord vois = voisines(f.getCoords());
        vector<Place> poss_moves = emptyPlaces(loadPlacesByCoords(g, vois));
        int rand_moves_idx = rand() % poss_moves.size();
        Place move = poss_moves[rand_moves_idx];

        Coord old_coords = f.getCoords();
        f.deplace(move.getCoords());
        fourmis[f.getNum()] = f;


        Place old_place = g.loadPlace(old_coords);
        old_place.removeFourmi();
        g.changePlace(old_place);

        Place new_place = g.loadPlace(f.getCoords());
        new_place.setFourmi(f);
        g.changePlace(new_place);

        areFourmiGrilleCoherent(g, f);
    }
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
        Coord(2, 7),
        Coord(4, 12),
        Coord(11, 7),
        Coord(10, 2)
    }};
    EnsCoord sugar_ens = EnsCoord(sugar_coords);

    EnsCoord fourmis_coords = coordsAroundNid(nid_ens);
    vector<Fourmi> fourmis{{}};

    for(int i = 0; i < fourmis_coords.taille(); i++){
        Fourmi f = Fourmi(fourmis_coords.ieme(i), i);
        fourmis.push_back(f);
    }
    Grille grille = initializeGrille(fourmis, sugar_ens, nid_ens);

    
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Simulation");

    window.setFramerateLimit(GAME_SPEED);


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // sf::Time elapsed = clock.restart(); // Get the elapsed time and restart the clock
        // float deltaTime = elapsed.asSeconds(); // Time in seconds since last frame

        window.clear(sf::Color::White);

        for(Place p: grille.getPlaces()){
            Coord c = p.getCoords();
            window.draw(draw_empty_square(c.getLine(), c.getColumn()));
            if(p.isEmpty()) continue;
            if(p.containNid()) window.draw(draw_nid(c.getLine(), c.getColumn()));
            if(p.containSugar()) window.draw(draw_sugar(c.getLine(), c.getColumn()));
            if(p.getFourmiID() != -1 && fourmis[p.getFourmiID()].isAlive()) window.draw(draw_fourmi(c.getLine(), c.getColumn()));
        }

        makeGameStep(fourmis, grille);

        window.display();
    }
    return 0;
}
