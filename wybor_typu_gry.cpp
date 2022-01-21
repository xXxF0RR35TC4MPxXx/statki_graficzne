#include "wybor_typu_gry.h"

using std::cout;

wybor_typu_gry::wybor_typu_gry(float width, float height)
{
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie ma takiego fontu!";
	}

	//Nowa gra
	numer_typu_gry[0].setFont(font);
	numer_typu_gry[0].setFillColor(Color::Black);
	numer_typu_gry[0].setString("P v BOT");
	numer_typu_gry[0].setCharacterSize(40);
	numer_typu_gry[0].setPosition(Vector2f(width / 25, height / (Max_wybor + 1) * 1));

	//Wczytaj gr�
	numer_typu_gry[1].setFont(font);
	numer_typu_gry[1].setFillColor(Color::Black);
	numer_typu_gry[1].setString(L"P v P");
	numer_typu_gry[1].setCharacterSize(40);
	numer_typu_gry[1].setPosition(Vector2f(width / 25, height / (Max_wybor + 1) * 2));

	//Instrukcja
	numer_typu_gry[2].setFont(font);
	numer_typu_gry[2].setFillColor(Color::Black);
	numer_typu_gry[2].setString(L"Wroc do menu");
	numer_typu_gry[2].setCharacterSize(30);
	numer_typu_gry[2].setPosition(Vector2f(width / 25, height / (Max_wybor + 1) * 3));


	WyborTypuGrySelected = 0;
	numer_typu_gry[WyborTypuGrySelected].setFillColor(Color::White);
}

wybor_typu_gry::~wybor_typu_gry() {

}


void wybor_typu_gry::draw(RenderWindow& window) {
	for (int i = 0; i < Max_wybor; i++)
	{
		window.draw(numer_typu_gry[i]);
	}
}

void wybor_typu_gry::MoveUp() {
		numer_typu_gry[WyborTypuGrySelected].setFillColor(Color::Black);

		WyborTypuGrySelected--;
		if (WyborTypuGrySelected == -1) {
			WyborTypuGrySelected = 2;
		}
		numer_typu_gry[WyborTypuGrySelected].setFillColor(Color::White);
	
}

void wybor_typu_gry::MoveDown() {
	if (WyborTypuGrySelected + 1 <= Max_wybor) {
		numer_typu_gry[WyborTypuGrySelected].setFillColor(Color::Black);

		WyborTypuGrySelected++;
		if (WyborTypuGrySelected == 3) {
			WyborTypuGrySelected = 0;
		}
		numer_typu_gry[WyborTypuGrySelected].setFillColor(Color::White);
	}
}