#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define Max_main_menu 5


class mainmenu {
protected:
	mainmenu(float, float);
	int MainMenuSelected;
	Font font;
	Text mainMenu[Max_main_menu];
	static mainmenu* mainmenu_;
public:
	mainmenu(mainmenu &diff) = delete;
	void operator=(const mainmenu &) = delete;
	static mainmenu *GetInstance(float, float);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int MainMenuPressed() {
		return MainMenuSelected;
	}
};