#include <SFML/Graphics.hpp>
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
#include <projet_fourmi/game.hpp>
#include <projet_fourmi/draw.hpp>
#include "time.h"

void debug_text(int num, const Fourmi &f, const Place &p);

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

void debug_text(int num, const Fourmi &f, const Place &p){
    cout << "Debug " << num << " " << f.getNum() << " " << f.getCoords() << " " << p.getCoords() << " " << p.getFourmiID() << endl;
}


int main()
{
    srand (time(NULL));
    FourmiEng f_eng = initializeFourmiEng();
    Grille grille = initializeGrille(f_eng.getFourmis(), EnsCoord(vector<Coord>{{}}), NUMBER_OF_COLONIES);
    int GAME_COUNT = 1;
    int GAME_SPEED = INITIAL_GAME_SPEED;


    int WINDOW_SIZE_FOR_TEXT = 500;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE+WINDOW_SIZE_FOR_TEXT, WINDOW_SIZE), "Simulation");

    window.setFramerateLimit(GAME_SPEED);

    sf::Font font = load_font();

    string text_for_game_count;
    string text_for_number_of_fourmis;

    float win_coords = 50.0f;
    float win_coords_step = 20.0f;


    Button btn_speed_up((TAILLEGRILLE+15)*scale, win_coords, scale*8, scale*2, sf::Color::Blue, "Speed Up", font);
    Button btn_speed_down((TAILLEGRILLE+15)*scale, win_coords+(win_coords_step*3), scale*8, scale*2, sf::Color::Blue, "Speed Down", font);


    sf::Text game_count_text = create_text((TAILLEGRILLE+1)*scale, win_coords, font);

    win_coords += win_coords_step;

    sf::Text number_of_fourmis_text = create_text((TAILLEGRILLE+1)*scale, win_coords, font);

    win_coords += win_coords_step;
    win_coords += win_coords_step;

    vector<sf::Text> amount_of_sugar_texts(NUMBER_OF_COLONIES);
    vector<sf::Text> number_of_fourmis_texts(NUMBER_OF_COLONIES);
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        amount_of_sugar_texts[i] = create_text((TAILLEGRILLE+1)*scale, win_coords, font);
        win_coords += win_coords_step;
        number_of_fourmis_texts[i] = create_text((TAILLEGRILLE+1)*scale, win_coords, font);

        amount_of_sugar_texts[i].setFillColor(sf::Color(TEAMS_COLORS[i][0], TEAMS_COLORS[i][1], TEAMS_COLORS[i][2], 255));
        number_of_fourmis_texts[i].setFillColor(sf::Color(TEAMS_COLORS[i][0], TEAMS_COLORS[i][1], TEAMS_COLORS[i][2], 255));
        
        win_coords += win_coords_step;
        win_coords += win_coords_step;
    }

    // for(int i = 0; i < NUMBER_OF_COLONIES; i++){
    // }


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (btn_speed_up.isMouseOver(window))
                {
                    std::cout << "Speed Up!" << std::endl;
                    GAME_SPEED += GAME_SPEED_CHANGE;
                    window.setFramerateLimit(GAME_SPEED);
                    
                }
                if (btn_speed_down.isMouseOver(window))
                {
                    std::cout << "Speed Down!" << std::endl;
                    GAME_SPEED -= GAME_SPEED_CHANGE;
                    if(GAME_SPEED < 1) GAME_SPEED = 1;
                    window.setFramerateLimit(GAME_SPEED);
                }
            }
        }

        window.clear(sf::Color::White);

        for(Place p: grille.getPlaces()){
            Coord c = p.getCoords();
            drawPheroNid(window, c.getLine(), c.getColumn(), p);
            draw_phero_sugar(window, c.getLine(), c.getColumn(), p);
            if(p.isEmpty()) continue;
            if(p.containNid()) draw_nid(window, c.getLine(), c.getColumn(), p);
            if(p.containSugar()) draw_sugar(window, c.getLine(), c.getColumn());
            if(p.getFourmiID() != -1 && f_eng.loadFourmi(p.getFourmiID()).isAlive()) {
                draw_fourmi(window, c.getLine(), c.getColumn(), f_eng.loadFourmi(p.getFourmiID()) );
                if(f_eng.loadFourmi(p.getFourmiID()).porteSucre()) draw_fourmi_sugar(window, c.getLine(), c.getColumn(), f_eng.loadFourmi(p.getFourmiID()) );
            }
        }

        text_for_game_count = "Game count: " + to_string(GAME_COUNT);
        game_count_text.setString(text_for_game_count);
        window.draw(game_count_text);

        for(int i = 0; i < NUMBER_OF_COLONIES; i++){
            string text_for_amount_of_sugar = "Amount of sugar in colony " + to_string(i) + " " + to_string(grille.getAmountOfSugar(i));
            amount_of_sugar_texts[i].setString(text_for_amount_of_sugar);
            window.draw(amount_of_sugar_texts[i]);

            string text_for_number_of_fourmis_c = "Number of fourmis in colony " + to_string(i) + " " + to_string(f_eng.getNumberOfFourmiInColony(i));
            number_of_fourmis_texts[i].setString(text_for_number_of_fourmis_c);
            window.draw(number_of_fourmis_texts[i]);
        }

        text_for_number_of_fourmis = "Number of fourmis: " + to_string(f_eng.getNumberOfFourmi());
        number_of_fourmis_text.setString(text_for_number_of_fourmis);
        window.draw(number_of_fourmis_text);

        makeGameStep(f_eng, grille, GAME_COUNT);

        btn_speed_down.drawTo(window);
        btn_speed_up.drawTo(window);

        window.display();
    }
    return 0;
}
