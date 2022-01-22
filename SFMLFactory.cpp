#include <SFML/Graphics.hpp>
#include <string>
#include "SFMLFactory.h"

using std::string;

sf::RectangleShape *SFMLFactory::createRectangle(int w, int h) {
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(w, h));
    return &shape;
}

sf::RectangleShape *SFMLFactory::createRectangle(int w, int h, sf::Texture texture) {
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(w, h));
    shape.setTexture(&texture);
    return &shape;
}

sf::Text *SFMLFactory::createText(string val, sf::Font font, int fsize, int xpos, int ypos) {
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(fsize);
    t.setPosition(sf::Vector2f(xpos, ypos));
    t.setString(val);

    return &t;
} 