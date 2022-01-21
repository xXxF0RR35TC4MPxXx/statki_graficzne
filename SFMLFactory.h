#ifndef SFMLFACTORY_H
#define SFMLFACTORY_H

#include <SFML/Graphics.hpp>
#include <string>


using std::string;

class SFMLFactory {
    private: 
        SFMLFactory();

    public:
        static sf::RectangleShape createRectangle(int w, int h);
        static sf::RectangleShape createRectangle(int w, int h, string pathToTexture);
        static sf::Text createText(string val, string font, int fsize, int xpos, int ypos);

};

#endif
