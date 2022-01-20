#include <SFML/Graphics.hpp>
#include <string>
#include "SFMLFactory.h"

using std::string;

sf::RectangleShape SFMLFactory::createRectangle(int w, int h) {
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(w, h));
    return shape;
}

sf::RectangleShape SFMLFactory::createRectangle(int w, int h, string pathToTexture) {
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(w, h));
    sf::Texture t;
    t.loadFromFile(pathToTexture);
    shape.setTexture(&t);
    return shape;
}

sf::Text SFMLFactory::createText(string val = "text", string fontPath = "retrofont.ttf", int fsize = 30, int xpos = 0, int ypos = 0) {
    sf::Color color;
    sf::Font font;
    
    font.loadFromFile(fontPath);

    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(fsize);
    t.setPosition(sf::Vector2f(xpos, ypos));
    t.setString(val);
    t.setFillColor(color);
} 