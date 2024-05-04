#include <SFML/Graphics.hpp>
#include <projet_fourmi/fourmi.hpp>
#include <projet_fourmi/place.hpp>
#include <projet_fourmi/draw.hpp>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/team_consts.hpp>

void draw_phero_sugar(sf::RenderWindow &window, int row, int column, const Place &p){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));

    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        if(p.estSurUnePiste(i)){
            int color_r = TEAMS_COLORS[i][0];
            int color_g = TEAMS_COLORS[i][1];
            int color_b = TEAMS_COLORS[i][2];
            int phero_sug_alpha = (int)(p.getPheroSugar(i));

            rectangle.setFillColor(sf::Color(color_r, color_g, color_b, phero_sug_alpha));
            rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

            window.draw(rectangle);
            // break;
        }
    }
}

void draw_nid(sf::RenderWindow &window, int row, int column, const Place &p){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));

    int color_r = TEAMS_COLORS[p.getNidColonyId()][0];
    int color_g = TEAMS_COLORS[p.getNidColonyId()][1];
    int color_b = TEAMS_COLORS[p.getNidColonyId()][2];

    rectangle.setFillColor(sf::Color(color_r, color_g, color_b, 255));

    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));

    rectangle.setOutlineThickness(0.5f);
    sf::Color grey(3, 3, 3, 55);
    rectangle.setOutlineColor(grey);

    window.draw(rectangle);
}

void draw_fourmi(sf::RenderWindow &window, int row, int column, Fourmi f){
    sf::CircleShape triangle(scale/2, 3);

    int color_r = TEAMS_COLORS[f.getColony()][0];
    int color_g = TEAMS_COLORS[f.getColony()][1];
    int color_b = TEAMS_COLORS[f.getColony()][2];

    triangle.setFillColor(
        sf::Color(color_r, color_g, color_b, 255)
    );
    triangle.setPosition(sf::Vector2f(scale*row, scale*column));

    triangle.setOutlineThickness(0.5f);
    triangle.setOutlineColor(sf::Color::Black);

    switch (f.getCaste())
    {
    case Caste::guerrier:
        triangle.setRadius(scale/4);
        triangle.setPosition(sf::Vector2f(scale*row+(scale/4), scale*column+(scale/4)));
        triangle.setOutlineThickness(1.0f);
        break;
    case Caste::reproductrice:
        triangle.setRadius(scale/2);
        triangle.setOutlineThickness(2.0f);
        triangle.setPointCount(6);
        break;
    
    default:
        break;
    }

    window.draw(triangle);
}

void draw_fourmi_sugar(sf::RenderWindow &window, int row, int column, Fourmi f){
    sf::CircleShape triangle(scale/4, 3);

    triangle.setFillColor(
        sf::Color::Blue
    );
    triangle.setPosition(sf::Vector2f((scale*row) + (scale/4), (scale*column) + (scale/4)));

    window.draw(triangle);
}

void draw_sugar(sf::RenderWindow &window, int row, int column){
    sf::CircleShape circle(scale/2);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(sf::Vector2f(scale*row, scale*column));

    window.draw(circle);
}

void drawPheroNid(sf::RenderWindow &window, int row, int column, Place p, bool show_phero_nid){
    sf::RectangleShape rectangle(sf::Vector2f(scale, scale));
    rectangle.setPosition(sf::Vector2f(scale*row, scale*column));
    if(!show_phero_nid){
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setOutlineThickness(0.5f);
        sf::Color grey(255, 255, 255, 15);
        rectangle.setOutlineColor(grey);
        window.draw(rectangle);
        return;
    }
    
    for(int i = 0; i < NUMBER_OF_COLONIES; i++){
        int alpha = (int)(p.getPheroNidByColony(i)*127);
        rectangle.setFillColor(sf::Color(TEAMS_COLORS[i][0], TEAMS_COLORS[i][1], TEAMS_COLORS[i][2], alpha));
        window.draw(rectangle);
    }
}


Button::Button(float x, float y, float width, float height, sf::Color color, std::string text, sf::Font _font)
{
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);

    font = _font;
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);
    label.setPosition(x + 10, y + 10); 
}

void Button::drawTo(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(label);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;
    float btnPosX = shape.getPosition().x;
    float btnPosY = shape.getPosition().y;
    float btnxPosWidth = shape.getPosition().x + shape.getSize().x;
    float btnyPosHeight = shape.getPosition().y + shape.getSize().y;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY)
    {
        return true;
    }
    return false;
}
