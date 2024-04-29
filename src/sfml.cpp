#include <SFML/Graphics.hpp>
#include <projet_fourmi/grille.hpp>
#include <projet_fourmi/place.hpp>
#include <iostream>
#include <random>
#include <format>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/fourmi_eng.hpp>
#include <projet_fourmi/team_consts.hpp>
#include "time.h"

void makeGameStep(FourmiEng &f_eng, Grille &g, int &game_count);
void makeRandomMoveFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeMoveToTheNidFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeMoveToThePheroSugarFourmi(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeFourmiMoveToPlace(Fourmi &f, FourmiEng &f_eng, Grille &g, Place move);

void makeFourmiTakeSugar(Fourmi f, FourmiEng &f_eng, Grille &g);
void makeFourmiPutSugar(Fourmi f, FourmiEng &f_eng, Grille &g);

void killFourmi(Fourmi &f, FourmiEng &f_eng, Grille &g);
void battleTwoFourmis(Fourmi &f1, Fourmi &f2, FourmiEng &f_eng, Grille &g);
void birthNewFourmi(FourmiEng &f_eng, Grille &g);

void draw_phero_sugar(sf::RenderWindow &window, int row, int column, const Place &p, float color=12.0){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));

    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        if(p.estSurUnePiste(i)){
            int color_r = TEAMS_COLORS[i][0];
            int color_g = TEAMS_COLORS[i][1];
            int color_b = TEAMS_COLORS[i][2];
            int phero_sug_alpha = (int)(p.getPheroSugar(i)*127);

            rectangle.setFillColor(sf::Color(color_r, color_g, color_b, phero_sug_alpha));
            rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

            window.draw(rectangle);
            break;
        }
    }
}

void draw_nid(sf::RenderWindow &window, int row, int column, const Place &p, float color=12.0){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));

    int color_r = TEAMS_COLORS[p.getColonyId()][0];
    int color_g = TEAMS_COLORS[p.getColonyId()][1];
    int color_b = TEAMS_COLORS[p.getColonyId()][2];

    rectangle.setFillColor(sf::Color(color_r, color_g, color_b, 255));

    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

    window.draw(rectangle);
}

void draw_fourmi(sf::RenderWindow &window, int row, int column, Fourmi f, float color=12.0){
    sf::CircleShape triangle(scale/2, 3);

    int color_r = TEAMS_COLORS[f.getColony()][0];
    int color_g = TEAMS_COLORS[f.getColony()][1];
    int color_b = TEAMS_COLORS[f.getColony()][2];
    // sf::Color color = sf::Color(color_r, color_g, color_b, 255);


    triangle.setFillColor(
        sf::Color(color_r, color_g, color_b, 255)
    );
    triangle.setPosition(sf::Vector2f(scale*row, scale*column));

    triangle.setOutlineThickness(0.5f);
    triangle.setOutlineColor(sf::Color::Black);

    window.draw(triangle);
}

void draw_fourmi_sugar(sf::RenderWindow &window, int row, int column, Fourmi f, float color=12.0){
    sf::CircleShape triangle(scale/4, 3);


    triangle.setFillColor(
        sf::Color::Blue
    );
    triangle.setPosition(sf::Vector2f((scale*row) + (scale/4), (scale*column) + (scale/4)));

    window.draw(triangle);
}

void draw_sugar(sf::RenderWindow &window, int row, int column, float color=12.0){
    sf::CircleShape circle(scale/2);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(sf::Vector2f(scale*row, scale*column));

    window.draw(circle);
}

void drawPheroNid(sf::RenderWindow &window, int row, int column, Place p){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));
    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        int alpha = (int)(p.getPheroNidByColony(i)*127);
        rectangle.setFillColor(sf::Color(TEAMS_COLORS[i][0], TEAMS_COLORS[i][1], TEAMS_COLORS[i][2], alpha));
        window.draw(rectangle);
    }
}

void birthNewFourmi(FourmiEng &f_eng, Grille &g, int colony){
    EnsCoord coords_around_nid = coordsAroundNid(g.getNid(colony));
    vector<Place> places = emptyPlaces(loadPlacesByCoords(g, coords_around_nid));

    if(places.size() == 0) return; //if there's no empty places

    int idx = rand() % places.size();
    Place new_p = places[idx];

    Fourmi f = Fourmi(new_p.getCoords(), 0, colony);

    Fourmi new_f = f_eng.birthFourmi(f);

    new_p.setFourmi(new_f);

    g.changePlace(new_p);
    areFourmiGrilleCoherent(g, new_f);
    g.descreaseAmountOfSugar(colony, AMOUT_OF_SUGAR_FOR_NEW_FOURMI);
}

void battleTwoFourmis(Fourmi &f1, Fourmi &f2, FourmiEng &f_eng, Grille &g){
    if(f1.porteSucre() && f2.porteSucre()) return;
    if(f1.getColony() == f2.getColony()) return;

    if(!f1.porteSucre() && f2.porteSucre()){
        killFourmi(f2, f_eng, g);
        return;
    }
    if(f1.porteSucre() && !f2.porteSucre()){
        killFourmi(f1, f_eng, g);
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
    if(game_count % NEW_SUGAR_APP_SPEED == 0){
        putSugarInRandomPlace(g);
    }
    g.decreasePheroSugar();
    for(int i = 0; i < f_eng.getFourmiTabSize(); i++){
        Fourmi f = f_eng.loadFourmi(i);
        if(!f.isAlive()) continue;
        if(isFourmiNeighbour(g, f.getCoords())){
            Place p = getNeigbourFourmiPlace(g, f.getCoords());
            Fourmi f2 = f_eng.loadFourmi(p.getFourmiID());
            if(f.getColony() != f2.getColony() && f.isAlive() && f2.isAlive()){
                battleTwoFourmis(f, f2, f_eng, g);
            }
        }
        if(!f.isAlive()) continue;

        if(f.porteSucre()){
            Place p = g.loadPlace(f.getCoords());
            p.setPheroSugar(f.getColony());
            g.changePlace(p);
        }
        if(f.goingToTheNid()){
            if(isFourmiNearItsNid(f, g)){
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
            if(g.loadPlace(f.getCoords()).estSurUnePiste(f.getColony())){
                makeMoveToThePheroSugarFourmi(f, f_eng, g);
                continue;
            }
            makeRandomMoveFourmi(f, f_eng, g);
            continue;
        }
        // makeRandomMoveFourmi(f, fourmis, g);
    }

    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        if(g.getAmountOfSugar(i) >= AMOUT_OF_SUGAR_FOR_NEW_FOURMI 
        && f_eng.getNumberOfFourmiInColony(i) >= 2
        && f_eng.getNumberOfFourmiInColony(i) < MAX_NUMBER_OF_FOURMI_IN_COLONY){
            birthNewFourmi(f_eng, g, i);
        }
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
    Place move = closestPlaceToTheNidByColony(near_places, f.getColony());
    makeFourmiMoveToPlace(f, f_eng, g, move);
}

void makeMoveToThePheroSugarFourmi(Fourmi f, FourmiEng &f_eng, Grille &g){
    vector<Place> near_places = emptyPlaces( loadPlacesByCoords( g, voisines(f.getCoords()) ) );
    Place move = closestPlaceToTheSugar(near_places, f.getColony());
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

    vector<Coord> sugar_coords{{
        // Coord(2, 7),
        // Coord(4, 12),
        // Coord(11, 7),
        // Coord(10, 2)
    }};
    EnsCoord sugar_ens = EnsCoord(sugar_coords);


    int f_id_count = 0;
    vector<Fourmi> fourmis{{}};
    for(int colony = 0; colony < NUMBER_OF_COLONIES; colony++){
        EnsCoord fourmis_coords = coordsAroundNid(NIDS_COORDS[colony]);

        for(int i = 0; i < fourmis_coords.taille(); i++){
            Fourmi f = Fourmi(fourmis_coords.ieme(i), f_id_count, colony);
            fourmis.push_back(f);
            f_id_count++;
        }
    }

    FourmiEng f_eng = FourmiEng(fourmis);
    Grille grille = initializeGrille(f_eng.getFourmis(), sugar_ens, NUMBER_OF_COLONIES);
    int GAME_COUNT = 1;


    int WINDOW_SIZE_FOR_TEXT = 500;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE+WINDOW_SIZE_FOR_TEXT, WINDOW_SIZE), "Simulation");

    window.setFramerateLimit(GAME_SPEED);

    sf::Font font = load_font();

    string text_for_game_count;
    string text_for_number_of_fourmis;

    float win_coords = 50.0f;
    float win_coords_step = 20.0f;
    sf::Text game_count_text = create_text((TAILLEGRILLE+1)*scale, win_coords, font);
    win_coords += win_coords_step;

    sf::Text number_of_fourmis_text = create_text((TAILLEGRILLE+1)*scale, win_coords, font);
    win_coords += win_coords_step;

    vector<sf::Text> amount_of_sugar_texts(NUMBER_OF_COLONIES);
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        amount_of_sugar_texts[i] = create_text((TAILLEGRILLE+1)*scale, win_coords, font);
        win_coords += win_coords_step;
    }

    vector<sf::Text> number_of_fourmis_texts(NUMBER_OF_COLONIES);
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        number_of_fourmis_texts[i] = create_text((TAILLEGRILLE+1)*scale, win_coords, font);
        win_coords += win_coords_step;
    }


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
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

        window.display();
    }
    return 0;
}
