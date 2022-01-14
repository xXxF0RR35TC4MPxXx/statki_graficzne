#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define max_pol 100
class game_screen {
public:
	game_screen();
	game_screen(float width, float height, RenderWindow* Window);
	void draw(RenderWindow& window, char plansza1[10][10], char plansza2[10][10], int typ);
	void MoveUp(char plansza[10][10], int typ);
	void MoveDown(char plansza[10][10], int typ);
	void MoveLeft(char plansza[10][10], int typ);
	void MoveRight(char plansza[10][10], int typ);
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