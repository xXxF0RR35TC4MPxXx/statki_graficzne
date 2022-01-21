#include "zapis_save_yes_no.h"

zapis_save_yes_no::zapis_save_yes_no(float width, float height)
{
	if (!font.loadFromFile("retrofont.ttf")) {
	}

	opis.setFont(font);
	opis.setFillColor(Color::Black);
	opis.setString(L"Czy chcesz zapisac gre i wyjsc?");
	opis.setCharacterSize(20);
	opis.setPosition(Vector2f(100, 100));

	
	numer_wyboru[0].setFont(font);
	numer_wyboru[0].setFillColor(Color::Black);
	numer_wyboru[0].setString("Tak");
	numer_wyboru[0].setCharacterSize(35);
	numer_wyboru[0].setPosition(Vector2f(144, 300));

	
	numer_wyboru[1].setFont(font);
	numer_wyboru[1].setFillColor(Color::Black);
	numer_wyboru[1].setString(L"Nie");
	numer_wyboru[1].setCharacterSize(35);
	numer_wyboru[1].setPosition(Vector2f(559, 300));

	zapis_save_yes_no_selected = 0;
	numer_wyboru[zapis_save_yes_no_selected].setFillColor(Color::White);
}

zapis_save_yes_no::~zapis_save_yes_no() {

}


void zapis_save_yes_no::draw(RenderWindow& window) {
	for (int i = 0; i < Max_wybor_zapis; i++)
	{
		window.draw(numer_wyboru[i]);
		window.draw(opis);
	}
}

void zapis_save_yes_no::MoveLeft() {
		numer_wyboru[zapis_save_yes_no_selected].setFillColor(Color::Black);

		zapis_save_yes_no_selected--;
		if (zapis_save_yes_no_selected == -1) {
			zapis_save_yes_no_selected = 1;
		}
		numer_wyboru[zapis_save_yes_no_selected].setFillColor(Color::White);
}

void zapis_save_yes_no::MoveRight() {
	numer_wyboru[zapis_save_yes_no_selected].setFillColor(Color::Black);

	zapis_save_yes_no_selected++;
	if (zapis_save_yes_no_selected == 2) {
		zapis_save_yes_no_selected = 0;
	}
	numer_wyboru[zapis_save_yes_no_selected].setFillColor(Color::White);
}