#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Plansza.h"
using namespace std;
using namespace sf;

#define max_pol 100
class game_screen {
public:
	game_screen();
	game_screen(float width, float height, RenderWindow* Window);
	void draw(RenderWindow& window, Plansza plansza1, Plansza plansza2, int typ);
	void MoveUp(Plansza plansza, int typ);
	void MoveDown(Plansza plansza, int typ);
	void MoveLeft(Plansza plansza, int typ);
	void MoveRight(Plansza plansza, int typ);
	int game_screen_Pressed() {
		return PoleSelected;
	}
	~game_screen();
	int PoleSelected;

private:
	
	Font font;
	RectangleShape pojedyncze_pole[max_pol];
	RenderWindow* Window;

};