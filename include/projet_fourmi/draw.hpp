#ifndef DRAW_HPP
#define DRAW_HPP

#include <SFML/Graphics.hpp>
#include "fourmi.hpp"
#include "place.hpp"

void draw_phero_sugar(sf::RenderWindow &window, int row, int column, const Place &p);
void draw_nid(sf::RenderWindow &window, int row, int column, const Place &p);
void draw_fourmi(sf::RenderWindow &window, int row, int column, Fourmi f);
void draw_fourmi_sugar(sf::RenderWindow &window, int row, int column, Fourmi f);
void draw_sugar(sf::RenderWindow &window, int row, int column);
void drawPheroNid(sf::RenderWindow &window, int row, int column, Place p);

class Button
{
public:
    Button(float x, float y, float width, float height, sf::Color color, std::string text, sf::Font _font);
    void drawTo(sf::RenderWindow &window);
    bool isMouseOver(sf::RenderWindow &window);

private:
    sf::RectangleShape shape;
    sf::Text label;
    sf::Font font;
};

#endif