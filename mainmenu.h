#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#define Max_main_menu 5


class mainmenu {
public:
	mainmenu(float width, float height);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int MainMenuPressed() {
		return MainMenuSelected;
	}
	~mainmenu();
private:
	int MainMenuSelected;
	Font font;
	Text mainMenu[Max_main_menu];
};
#endif