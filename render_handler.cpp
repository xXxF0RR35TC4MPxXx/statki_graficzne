#include "render_handler.h"
#include "game_screen.h"
#include "render_api.h"

 int RenderHandler::czy_wygrana(Plansza plansza) {
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (plansza.pola_planszy[i][k]->symbol == '1' || plansza.pola_planszy[i][k]->symbol == '2' || plansza.pola_planszy[i][k]->symbol == '3' || plansza.pola_planszy[i][k]->symbol == '4')
			{
				return 0;
			}
		}
	}

	return 1;
}

 Result RenderHandler::handleNickEvent(sf::RenderWindow* Window, sf::Text* t)
{
    sf::Event gevent;
    std::string s;
	while (Window->isOpen()) {
		if (Window->pollEvent(gevent))
		{
			if (gevent.type == sf::Event::MouseButtonPressed) {
				// do nothing;
			}
			if (gevent.type == sf::Event::Closed) {
				Window->close();
			}
			if (gevent.type == sf::Event::TextEntered)
			{
				if (gevent.text.unicode < 127 &&
					gevent.text.unicode >= 48 &&
					gevent.text.unicode != '\n' &&
					gevent.text.unicode != '\r' &&
					gevent.text.unicode != 10 &&
					gevent.text.unicode != '\v' &&
					gevent.text.unicode != 27 &&
					gevent.text.unicode != 32 &&
					gevent.text.unicode != '\b' &&
					t->getString().getSize() < 16)
				{
					s = t->getString();
					s += static_cast<char>(gevent.text.unicode);
					std::cout << "TextEntered s = " << s << "\n";
					Result wynik(s, false);
					return wynik;
				}
				//jezeli masz co usuwac, to usun ostatnio dodany znak
				if (t->getString().getSize() > 0 && gevent.text.unicode == '\b') {
					s = t->getString();  s.pop_back();
					Result wynik(s, false);
					return wynik;
				}
				if ((gevent.text.unicode == '\n' || gevent.text.unicode == '\r') && t->getString().getSize() > 0) {
					std::string tempString = t->getString();
					std::cout << "Enter: tempString = " << tempString << "\n";
					Result wynik(tempString, true);
					return wynik;
				}
			}
		}
	}
    
}

// jak to nie rzuci overflowa to robie fikołka na kamerce
std::tuple<std::string, int, int, int> RenderHandler::handleShipPlacement(int msgtype, int type, int nr) {
	std::string s;
	int max_ilosc = 5 - type;
	int x, y, csize = 0;
	std::string var;
	if (msgtype == 1)
	{
		s = "Ustawiasz statek " + std::to_string(type) + "-masztowy (" + std::to_string(nr) + "/" + std::to_string(max_ilosc) + ")\n";
		x = 115; y = 493; csize = 18;
	}
	else if (msgtype == 2) {
		s = "Wybierz orientacje okretu (strzalkami)\n";
		x = 75; y = 539; csize = 18;
	}
	else if (msgtype == 3) {
		s = "Nie mozna umiescic statku w tym miejscu!\n";
		x = 75; y = 579; csize = 17;
	}
	else if (msgtype == 4) {
		s = "";
		x = 71; y = 539; csize = 17;
	}
	
	return std::make_tuple(s, x, y, csize);
}

void RenderHandler::handleBoardSetup(sf::RectangleShape game_background, sf::Text twojaplanszatekst,
	sf::Text planszaprzeciwnikatekst, game_screen game_screen, Plansza plansza1, Plansza plansza2, sf::RenderWindow* Window) {
	//font
	sf::Font* retrofont = new Font();
	retrofont->loadFromFile("retrofont.ttf");

	sf::Text ustawiasz_statek;
	sf::Text komunikat_bledu;
	sf::Text komunikat_kierunku;
	Texture sprite_pustego_pola_texture;
	sprite_pustego_pola_texture.loadFromFile("Texture/empty_tile.png");
	Texture sprite_1_tile;
	sprite_1_tile.loadFromFile("Texture/1_tile.png");
	Texture sprite_2_tile;
	sprite_2_tile.loadFromFile("Texture/2_tile.png");
	Texture sprite_3_tile;
	sprite_3_tile.loadFromFile("Texture/3_tile.png");
	Texture sprite_4_tile;
	sprite_4_tile.loadFromFile("Texture/4_tile.png");
	Texture sprite_hit_tile;
	sprite_hit_tile.loadFromFile("Texture/hit_tile.png");
	Texture sprite_miss_tile;
	sprite_miss_tile.loadFromFile("Texture/missed_tile.png");



	render_api* renderer = render_api::GetInstance();
	int nr = 1;
	int typ = 1;
	int odpowiedz = -1;
	bool podaje_kierunek = false;
	bool czy_error = false;
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja = 1;
	while (Window->isOpen() && typ < 5)
	{
		
		do
		{
			Event gevent;

			Window->clear();
			Window->draw(game_background);
			Window->draw(twojaplanszatekst);
			Window->draw(planszaprzeciwnikatekst);
			game_screen.draw(*Window, plansza1, plansza2, 1, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
				sprite_hit_tile, sprite_miss_tile);
			renderer->ustawiasz_statek(typ, nr, Window, 1, retrofont);
			if (czy_error && !podaje_kierunek) {
				renderer->ustawiasz_statek(typ, nr, Window, 3, retrofont);
			}
			else {
				renderer->ustawiasz_statek(typ, nr, Window, 4, retrofont);
			}

			//read_nickname.draw(*Window);
			Window->display();
			wspolrzedna_x = 0;
			wspolrzedna_y = 0;
			while (Window->pollEvent(gevent))
			{
				if (gevent.type == Event::MouseButtonPressed) {

				}
				if (gevent.type == Event::KeyPressed) {
					if (gevent.key.code == Keyboard::Up && !podaje_kierunek)
					{
						game_screen.MoveUp(plansza1, 1);
						break;
					}
					if (gevent.key.code == Keyboard::Down && !podaje_kierunek) {
						game_screen.MoveDown(plansza1, 1);
						break;
					}
					if (gevent.key.code == Keyboard::Left && !podaje_kierunek) {
						game_screen.MoveLeft(plansza1, 1);
						break;
					}
					if (gevent.key.code == Keyboard::Right && !podaje_kierunek) {
						game_screen.MoveRight(plansza1, 1);
						break;
					}
					if (gevent.key.code == Keyboard::Return)
					{
						if (typ == 1) {
							wspolrzedna_y = floor(game_screen.PoleSelected / 10);
							wspolrzedna_x = game_screen.PoleSelected % 10;
							odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_y + 1, wspolrzedna_x + 1);//sprawdzanie czy w wylosowanej pozycji moze stac statek
							if (odpowiedz == 0)
							{
								czy_error = true;
								//renderer->nie_mo�na_postawi�_statku();

							}
							else {
								czy_error = false;
								komunikat_bledu.setString("");
								Window->clear();
								plansza1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = '1';//wpisanie statku do tablicy w odpowiednie miejsce
								game_screen.PoleSelected = 0;
								nr++;
								renderer->wypisz_plansze(plansza1);
								if (nr == 5) { typ++; nr = 1; break; }
							}
						}
						else if (typ == 2)
						{
							wspolrzedna_x = floor(game_screen.PoleSelected / 10);
							wspolrzedna_y = game_screen.PoleSelected % 10;
							Event kierunekevent;
							while (Window->waitEvent(kierunekevent))
							{

								czy_error = false;

								podaje_kierunek = true; if (!czy_error && podaje_kierunek)
								{
									renderer->ustawiasz_statek(typ, nr, Window, 2, retrofont);
									renderer->ustawiasz_statek(typ, nr, Window, 4, retrofont);
								}Window->display();
								if (kierunekevent.type == Event::KeyPressed)
								{
									if (kierunekevent.key.code == Keyboard::Up)
									{
										orientacja = 1;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '2';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x - 1]->symbol = '2';
											game_screen.PoleSelected = 0;
											nr++;
											if (nr == 4) { typ++; nr = 1; }renderer->wypisz_plansze(plansza1);
										}podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Down)
									{
										orientacja = 4;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '2';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x + 1]->symbol = '2';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 4) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Left)
									{
										orientacja = 3;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '2';
											plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x]->symbol = '2';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 4) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Right)
									{
										orientacja = 2;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 2);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '2';
											plansza1.pola_planszy[wspolrzedna_y + 1][wspolrzedna_x]->symbol = '2';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 4) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
								}
							}

						}
						else if (typ == 3)
						{
							wspolrzedna_x = floor(game_screen.PoleSelected / 10);
							wspolrzedna_y = game_screen.PoleSelected % 10;
							Event kierunekevent;
							while (Window->waitEvent(kierunekevent))
							{
								czy_error = false;


								podaje_kierunek = true;
								if (!czy_error && podaje_kierunek)
								{
									renderer->ustawiasz_statek(typ, nr, Window, 2, retrofont);
									renderer->ustawiasz_statek(typ, nr, Window, 4, retrofont);
								}Window->display();
								if (kierunekevent.type == Event::KeyPressed)
								{
									if (kierunekevent.key.code == Keyboard::Up)
									{
										orientacja = 1;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x - 1]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x - 2]->symbol = '3';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 3) { typ++; nr = 1; }
										}podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Down)
									{
										orientacja = 4;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 3, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x + 1]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x + 2]->symbol = '3';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 3) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Left)
									{
										orientacja = 3;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true;  podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y - 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y - 2][wspolrzedna_x]->symbol = '3';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 3) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Right)
									{
										orientacja = 2;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 2);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 3);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											Window->clear();
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y + 1][wspolrzedna_x]->symbol = '3';
											plansza1.pola_planszy[wspolrzedna_y + 2][wspolrzedna_x]->symbol = '3';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 3) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
								}
							}

						}
						else if (typ == 4)
						{
							wspolrzedna_x = floor(game_screen.PoleSelected / 10);
							wspolrzedna_y = game_screen.PoleSelected % 10;
							Event kierunekevent;
							while (Window->waitEvent(kierunekevent))
							{
								czy_error = false;

								podaje_kierunek = true; if (!czy_error && podaje_kierunek)
								{
									renderer->ustawiasz_statek(typ, nr, Window, 4, retrofont);
									renderer->ustawiasz_statek(typ, nr, Window, 2, retrofont);
								}
								Window->display();
								if (kierunekevent.type == Event::KeyPressed)
								{
									if (kierunekevent.key.code == Keyboard::Up)
									{
										orientacja = 1;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x - 2, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											podaje_kierunek = false; break;
											czy_error = true;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x - 1]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x - 2]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x - 3]->symbol = '4';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 2) { typ++; nr = 1; }
										}podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Down)
									{
										orientacja = 4;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 3, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 4, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x + 1]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x + 2]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x + 3]->symbol = '4';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 2) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Left)
									{
										orientacja = 3;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y - 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y - 2);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y - 2][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y - 3][wspolrzedna_x]->symbol = '4';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 2) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Right)
									{
										orientacja = 2;
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 2);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 3);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 4);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y + 1][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y + 2][wspolrzedna_x]->symbol = '4';
											plansza1.pola_planszy[wspolrzedna_y + 3][wspolrzedna_x]->symbol = '4';
											game_screen.PoleSelected = 0;

											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 2) { typ++; nr = 1; }
										}
										podaje_kierunek = false;
										break;
									}
								}
							}

						}
					}
				}
				if (gevent.type == Event::Closed) {
					Window->close();
				}
				//Window->display();
			}
		} while (odpowiedz != 1);//jezeli nie moze stac statek w tej pozycji uzytkownik podaje nowe wspolrzedne

	}
}

void RenderHandler::handleBoardGame(sf::RectangleShape game_background, sf::Text twojaplanszatekst,
	sf::Text planszaprzeciwnikatekst, sf::Text komunikat,
	game_screen game_screen,
	Plansza plansza1, Plansza plansza2,
	Plansza plansza2_1, Plansza plansza2_2,
	sf::RenderWindow* Window, int typ,
	unsigned int& oddane_strzaly_1,
	unsigned int& oddane_strzaly_2,
	unsigned int& trafienia_1,
	unsigned int& trafienia_2)
{
	render_api* renderer = render_api::GetInstance();
	int nr = 1;
	int odpowiedz = -1;
	int jezeli_wygrana = 0;
	bool podaje_kierunek = false;
	bool czy_error = false;
	bool czy_kontynuowac = true;
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja = 1;
	while (Window->isOpen() && czy_kontynuowac)
	{
		Event gevent;
		Texture sprite_pustego_pola_texture;
		sprite_pustego_pola_texture.loadFromFile("Texture/empty_tile.png");
		Texture sprite_1_tile;
		sprite_1_tile.loadFromFile("Texture/1_tile.png");
		Texture sprite_2_tile;
		sprite_2_tile.loadFromFile("Texture/2_tile.png");
		Texture sprite_3_tile;
		sprite_3_tile.loadFromFile("Texture/3_tile.png");
		Texture sprite_4_tile;
		sprite_4_tile.loadFromFile("Texture/4_tile.png");
		Texture sprite_hit_tile;
		sprite_hit_tile.loadFromFile("Texture/hit_tile.png");
		Texture sprite_miss_tile;
		sprite_miss_tile.loadFromFile("Texture/missed_tile.png");
		Window->clear();
		Window->draw(game_background);
		Window->draw(twojaplanszatekst);
		Window->draw(planszaprzeciwnikatekst);
		Window->draw(komunikat);
		game_screen.draw(*Window, plansza1, plansza2, 2, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
			sprite_hit_tile, sprite_miss_tile);
		Window->display();
		wspolrzedna_x = 0;
		int czy_trafione = 0;
		wspolrzedna_y = 0;
		while (Window->pollEvent(gevent))
		{
			if (gevent.type == Event::MouseButtonPressed) {

			}
			if (gevent.type == Event::KeyPressed) {
				if (gevent.key.code == Keyboard::Up)
				{
					game_screen.MoveUp(plansza2, 2);
					break;
				}
				if (gevent.key.code == Keyboard::Down) {
					game_screen.MoveDown(plansza2, 2);
					break;
				}
				if (gevent.key.code == Keyboard::Left) {
					game_screen.MoveLeft(plansza2, 2);
					break;
				}
				if (gevent.key.code == Keyboard::Right) {
					game_screen.MoveRight(plansza2, 2);
					break;
				}
				if (gevent.key.code == Keyboard::Return)
				{

					wspolrzedna_x = floor(game_screen.PoleSelected / 10);
					wspolrzedna_y = game_screen.PoleSelected % 10;


					if (typ == 1 || typ == 2) {
						if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == ' ')//jezeli uzytkownik strzelil w puste pole
						{
							if (typ == 1) {
								oddane_strzaly_1++;
								renderer->temp_shot1++;

							}
							if (typ == 2) {
								oddane_strzaly_2++;
								renderer->temp_shot2++;
							}
							//ustawianie oznaczenia strzalu w odpowiednich tablicach

							komunikat.setPosition(Vector2f(356, 539));
							komunikat.setString("Pudlo!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
								sprite_hit_tile, sprite_miss_tile);
							Window->display();
							plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '.';
							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = '.';
							czy_trafione = 0;
							czy_kontynuowac = false;
						}
						else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == 'x' || plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '.')//jezeli uzytkownik strzelil w juz strzelane pole
						{

							if (typ == 1) {
								oddane_strzaly_1++;
								renderer->temp_shot1++;


							}
							if (typ == 2) {
								oddane_strzaly_2++;
								renderer->temp_shot2++;
							}
							komunikat.setPosition(Vector2f(226, 539));
							komunikat.setString("Strzelales juz tutaj!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
								sprite_hit_tile, sprite_miss_tile);
							Window->display();
							czy_trafione = 2;
							czy_kontynuowac = false;
						}
						else//jezeli uzytkownik trafil
						{
							if (typ == 1) {
								oddane_strzaly_1++;

								renderer->temp_shot1++;

								trafienia_1++;

								renderer->temp_hit1++;

							}
							if (typ == 2) {
								oddane_strzaly_2++;

								renderer->temp_shot2++;
								trafienia_2++;

								renderer->temp_hit2++;
							}

							komunikat.setString("Trafiles!");
							czy_kontynuowac = true;
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
								sprite_hit_tile, sprite_miss_tile);
							Window->display();
							//umieszczanie odpowiednich oznaczen statkow na tablicach
							if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '1')//jezeli statek jednomasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '2')//jezeli statek dwumasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '3')//jezeli statek trzymasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '4')//jezeli statek czteromasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = 'x';//ustawienie na planszy drugiego gracza oznaczenia, ze przeciwnik trafil
							czy_trafione = 1;
							jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
							if (jezeli_wygrana == 1)//jezeli wygral
							{
								czy_kontynuowac = false;
								//wygrana(nick1);//wyswietlenie statystyk
								break;
							}
						}
						std::cout << "PLANSZA2_1\n";
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++) {
								if (plansza2_1.pola_planszy[j][i]->symbol != ' ')
									std::cout << plansza2_1.pola_planszy[j][i]->symbol;
								else std::cout << '-';
							}std::cout << "\n";
						}
					}
					//typ 3 jest ok - NIE RUSZAC!
					else if (typ == 3) {
						if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == ' ')//jezeli uzytkownik strzelil w puste pole
						{
							//ustawianie oznaczenia strzalu w odpowiednich tablicach

							oddane_strzaly_1++;
							renderer->temp_shot1++;


							komunikat.setPosition(Vector2f(356, 539));
							komunikat.setString("Pudlo!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
								sprite_hit_tile, sprite_miss_tile);
							Window->display();
							plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = '.';
							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = '.';
							czy_trafione = 0;
							czy_kontynuowac = false;
						}
						else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == 'x' || plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '.')//jezeli uzytkownik strzelil w juz strzelane pole
						{

							oddane_strzaly_1++;
							renderer->temp_shot1++;

							komunikat.setPosition(Vector2f(226, 539));
							komunikat.setString("Strzelales juz tutaj!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
								sprite_hit_tile, sprite_miss_tile);
							Window->display();
							czy_trafione = 2;
							czy_kontynuowac = false;
						}
						else//jezeli uzytkownik trafil
						{
							oddane_strzaly_1++;
							renderer->temp_shot1++;

							trafienia_1++;
							renderer->temp_hit1++;

							komunikat.setString("Trafiles!");
							czy_kontynuowac = true;
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2, sprite_pustego_pola_texture, sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
								sprite_hit_tile, sprite_miss_tile);
							Window->display();
							//umieszczanie odpowiednich oznaczen statkow na tablicach
							if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '1')//jezeli statek jednomasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '2')//jezeli statek dwumasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '3')//jezeli statek trzymasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '4')//jezeli statek czteromasztowy
							{
								plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
							}
							plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';//ustawienie na planszy drugiego gracza oznaczenia, ze przeciwnik trafil
							czy_trafione = 1;
							jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
							if (jezeli_wygrana == 1)//jezeli wygral
							{
								czy_kontynuowac = false;
								//wygrana(nick1);//wyswietlenie statystyk
								break;
							}
						}
						std::cout << "PLANSZA1_2\n";
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++) {
								if (plansza2.pola_planszy[i][j]->symbol != ' ')
									std::cout << plansza2.pola_planszy[i][j]->symbol;
								else std::cout << '-';
							}std::cout << "\n";
						}
						std::cout << "PLANSZA2_1\n";
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++) {
								if (plansza2_1.pola_planszy[i][j]->symbol != ' ')
									std::cout << plansza2_1.pola_planszy[i][j]->symbol;
								else std::cout << '-';
							}std::cout << "\n";
						}
					}
				}
			}
			if (gevent.type == Event::Closed) {
				Window->close();
			}
			//Window->display();
		}
	}
}