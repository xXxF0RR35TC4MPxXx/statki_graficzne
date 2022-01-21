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
        static sf::Text createText(string val = "text", string font = "default", int fsize = 30, int xpos = 0, int ypos = 0);

};

#endif
