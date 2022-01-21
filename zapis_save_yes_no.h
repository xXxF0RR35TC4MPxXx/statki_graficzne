#ifndef ZAPIS_SAVE_YES_NO_H
#define ZAPIS_SAVE_YES_NO_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#define Max_wybor_zapis 2
class zapis_save_yes_no {
public:
	zapis_save_yes_no();
	zapis_save_yes_no(float width, float height);
	void draw(RenderWindow& window);
	void MoveLeft();
	void MoveRight();
	int zapis_save_yes_no_pressed() {
		return zapis_save_yes_no_selected;
	}
	~zapis_save_yes_no();

private:
	int zapis_save_yes_no_selected;
	Font font;
	Text opis;
	Text numer_wyboru[Max_wybor_zapis];
};
#endif