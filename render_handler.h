#ifndef RENDER_HANDLER_H
#define RENDER_HANDLER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "SFMLFactory.h"
#include "game_screen.h"

class Result {
public:
	Result(string s, bool e) {
		nickname = s;
		exit = e;
	}
	string nickname;
	bool exit;
};

class RenderHandler {
public:
        static Result handleNickEvent(sf::RenderWindow*, sf::Text*);
        static std::tuple<std::string, int, int, int> handleShipPlacement(int msgtype, int type, int nr);
		static void handleBoardGame(sf::RectangleShape game_background, sf::Text twojaplanszatekst,
			sf::Text planszaprzeciwnikatekst, sf::Text komunikat,
			game_screen game_screen,
			Plansza plansza1, Plansza plansza2,
			Plansza plansza2_1, Plansza plansza2_2,
			sf::RenderWindow* Window, int typ,
			unsigned int& oddane_strzaly_1,
			unsigned int& oddane_strzaly_2,
			unsigned int& trafienia_1,
			unsigned int& trafienia_2);

		static void handleBoardSetup(sf::RectangleShape game_background, sf::Text twojaplanszatekst,
			sf::Text planszaprzeciwnikatekst, game_screen game_screen, Plansza plansza1, Plansza plansza2, sf::RenderWindow* Window);
private:
	static int czy_wygrana(Plansza plansza);

};

#endif