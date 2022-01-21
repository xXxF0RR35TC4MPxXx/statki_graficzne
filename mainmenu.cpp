#include "MainMenu.h"

mainmenu::mainmenu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Nie ma takiego fontu!";
	}

	//Nowa gra
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Black);
	mainMenu[0].setString("Nowa gra");
	mainMenu[0].setCharacterSize(35);
	mainMenu[0].setPosition(Vector2f(width / 25, height / (Max_main_menu + 1) * 1));

	//Wczytaj gr�
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::Black);
	mainMenu[1].setString(L"Wczytaj gre");
	mainMenu[1].setCharacterSize(35);
	mainMenu[1].setPosition(Vector2f(width / 25, height / (Max_main_menu + 1) * 2));

	//Instrukcja
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::Black);
	mainMenu[2].setString("Instrukcja");
	mainMenu[2].setCharacterSize(35);
	mainMenu[2].setPosition(Vector2f(width / 25, height / (Max_main_menu + 1) * 3));

	//Zako�cz gr�
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::Black);
	mainMenu[3].setString(L"Tworcy");
	mainMenu[3].setCharacterSize(35);
	mainMenu[3].setPosition(Vector2f(width / 25, height / (Max_main_menu + 1) * 4));

	//Zako�cz gr�
	mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(Color::Black);
	mainMenu[4].setString(L"Zakoncz gre");
	mainMenu[4].setCharacterSize(35);
	mainMenu[4].setPosition(Vector2f(width / 25, height / (Max_main_menu + 1) * 5));

	MainMenuSelected = 0;
	mainMenu[MainMenuSelected].setFillColor(Color::White);
}

void mainmenu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; i++)
	{
		window.draw(mainMenu[i]);
	}
}

void mainmenu::MoveUp() {
	
		mainMenu[MainMenuSelected].setFillColor(Color::Black);

		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 4;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::White);
	
}

void mainmenu::MoveDown() {
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(Color::Black);

		MainMenuSelected++;
		if (MainMenuSelected == 5) {
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::White);
	}
}

mainmenu* mainmenu::GetInstance(float w, float h) {
	if(mainmenu_ == nullptr) {
		mainmenu_ = new mainmenu(w, h);
	}
	return mainmenu_;
}