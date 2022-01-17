#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "dziedziczace.h"

#include "render_api.h"


#include "game_screen.h"
#pragma warning(disable:4996)
#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822
#define TILE_WIDTH 30
#define TILE_HEIGHT 30
using namespace std;


render_api::render_api() {

}




void render_api::main_menu(sf::RenderWindow* Window, mainmenu MainMenu) {
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture MainTexture;
	MainTexture.loadFromFile("Texture/menu_background.jpg");
	background.setTexture(&MainTexture);
	Window->clear();
	Window->draw(background);
	MainMenu.draw(*Window);
	Window->display();
}
void render_api::wybor_typ_gry(sf::RenderWindow* Window, wybor_typu_gry wybór_typu_gry) {
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture MainTexture;
	MainTexture.loadFromFile("Texture/menu_background.jpg");
	background.setTexture(&MainTexture);
	Window->clear();
	Window->draw(background);
	wybór_typu_gry.draw(*Window);
	Window->display();
}
std::string render_api::podaj_nick(sf::RenderWindow* Window) {
	sf::Text t;
	t.setFillColor(sf::Color::Black);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");
	t.setFont(retrofont);
	t.setCharacterSize(50);
	t.setPosition(Vector2f(75, 250));
	string s;
	RectangleShape podaj_nick_background;
	podaj_nick_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture podaj_nick_Texture;
	podaj_nick_Texture.loadFromFile("Texture/podaj_nick.png");
	podaj_nick_background.setTexture(&podaj_nick_Texture);
	while (Window->isOpen())
	{

		Event gevent;
		Window->clear();
		Window->draw(podaj_nick_background);
		Window->draw(t);
		Window->display();
		if (Window->pollEvent(gevent))
		{
			if (gevent.type == Event::MouseButtonPressed) {

			}
			if (gevent.type == Event::Closed) {
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
					t.getString().getSize() < 16)
				{
					s += static_cast<char>(gevent.text.unicode);
					t.setString(s); //dodaj do stringa

				}
				//je¿eli masz co usuwaæ, to usuñ ostatnio dodany znak
				if (t.getString().getSize() > 0 && gevent.text.unicode == '\b') {
					s.pop_back();
					t.setString(s);
				}
				if ((gevent.text.unicode == '\n' || gevent.text.unicode == '\r') && t.getString().getSize() > 0) {
					string tempString = t.getString();
					int rodzaj = 0;
					const char* nick = tempString.c_str();
					return tempString;
				}
			}
		}
	}
}
void render_api::ustawiasz_statek(int typ, int nr, sf::RenderWindow* Window, int typ_wiadomosci, sf::Text napis) {
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	napis.setFillColor(sf::Color::Black);
	napis.setFont(retrofont);

	int max_ilosc = 5 - typ;
	std::string var;
	if (typ_wiadomosci == 1)
	{
		var = "Ustawiasz statek " + std::to_string(typ) + "-masztowy (" + std::to_string(nr) + "/" + std::to_string(max_ilosc) + ")\n";
		napis.setPosition(Vector2f(115, 493));

		napis.setCharacterSize(18);
	}
	else if (typ_wiadomosci == 2) {
		var = "Wybierz orientacje okretu (strzalkami)\n";
		napis.setPosition(Vector2f(75, 539));

		napis.setCharacterSize(18);
	}
	else if (typ_wiadomosci == 3) {
		var = "Nie mozna umiescic statku w tym miejscu!\n";
		napis.setPosition(Vector2f(71, 579));

		napis.setCharacterSize(17);
	}
	else if (typ_wiadomosci == 4) {
		var = "";
		napis.setPosition(Vector2f(71, 539));

		napis.setCharacterSize(17);
	}
	napis.setString(var);
	Window->draw(napis);

}
int render_api::czy_moze_tu_stac(unsigned int wspolrzedna_x, unsigned int wspolrzedna_y, char plansza[10][10])//funkcja sprawdza czy postawiony statek w tej pozycji nie
{																											//bedzie kolidowal z juz postawionymi statkami lub czy nie
	//czy nie wychodzi za tablice																			//wychodzi za plansze
	if (wspolrzedna_x > 10 || wspolrzedna_x < 1 || wspolrzedna_y > 10 || wspolrzedna_y < 1)					//zwraca 0 jezeli nie moze stac na tej pozycji lub 1 jezeli moze
	{
		return 0;
	}
	if (plansza[wspolrzedna_y - 1][wspolrzedna_x - 1] != ' ')
	{
		return 0;
	}
	if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy czegos nie dotyka po lewej)
	{
		if (plansza[wspolrzedna_y - 1][wspolrzedna_x - 2] != ' ')
		{
			return 0;
		}
	}
	else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy czegos nie dotyka po prawej)
	{
		if (plansza[wspolrzedna_y - 1][wspolrzedna_x] != ' ')
		{
			return 0;
		}
	}
	else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy nie dotyka czegos z obu stron)
	{
		if (plansza[wspolrzedna_y - 1][wspolrzedna_x] != ' ' || plansza[wspolrzedna_y - 1][wspolrzedna_x - 2] != ' ')
		{
			return 0;
		}
	}
	if (wspolrzedna_y == 10)//jezeli dotyka dolna sciane(sprawdzamy tylko czy czegos nie dotyka u gory)
	{
		if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 1] != ' ')
		{
			return 0;
		}
	}
	else if (wspolrzedna_y == 1)//jezeli dotyka dolna sciane(sprawdzamy tylko czy czegos nie dotyka u dolu)
	{
		if (plansza[wspolrzedna_y][wspolrzedna_x - 1] != ' ')
		{
			return 0;
		}
	}
	else//jezeli nie dotyka dotyka zadnej sciany(gornej lub dolnej)(sprawdzamy czy nie dotyka czegos u gory i dolu)
	{
		if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 1] != ' ' || plansza[wspolrzedna_y][wspolrzedna_x - 1] != ' ')
		{
			return 0;
		}
	}
	if (wspolrzedna_y > 1)//jezeli nie dotyka gornej sciany
	{
		if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy lewy gorny rog jest wolny)
		{
			if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 2] != ' ')
			{
				return 0;
			}
		}
		else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy prawy gorny rog jest wolny)
		{
			if (plansza[wspolrzedna_y - 2][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
		else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy gorne rogi sa wolne)
		{
			if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 2] != ' ' || plansza[wspolrzedna_y - 2][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
	}
	if (wspolrzedna_y < 10)//jezeli nie dotyka dolnej sciany
	{
		if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy lewy dolny rog jest wolny)
		{
			if (plansza[wspolrzedna_y][wspolrzedna_x - 2] != ' ')
			{
				return 0;
			}
		}
		else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy prawy dolny rog jest wolny)
		{
			if (plansza[wspolrzedna_y][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
		else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy dolne rogi sa wolne)
		{
			if (plansza[wspolrzedna_y][wspolrzedna_x - 2] != ' ' || plansza[wspolrzedna_y][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}
void render_api::render_planszy_przy_ustawianiu(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow* Window) {

	//t³o planszy
	RectangleShape game_background;
	game_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture game_texture;
	game_texture.loadFromFile("Texture/game_background.png");
	game_background.setTexture(&game_texture);

	//font
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	//tekst "Twoje pole:"
	sf::Text twojaplanszatekst;
	twojaplanszatekst.setFillColor(sf::Color::Green);
	twojaplanszatekst.setFont(retrofont);
	twojaplanszatekst.setCharacterSize(18);
	twojaplanszatekst.setPosition(Vector2f(120, 100));
	twojaplanszatekst.setString("Twoje pole:");

	//tekst "Pole przeciwnika:"
	sf::Text planszaprzeciwnikatekst;
	planszaprzeciwnikatekst.setFillColor(sf::Color::Red);
	planszaprzeciwnikatekst.setFont(retrofont);
	planszaprzeciwnikatekst.setCharacterSize(18);
	planszaprzeciwnikatekst.setPosition(Vector2f(456, 100));
	planszaprzeciwnikatekst.setString("Pole przeciwnika:");

	sf::Text ustawiasz_statek;
	sf::Text komunikat_bledu;
	sf::Text komunikat_kierunku;

	//³adowanie dostêpnych tekstur pól
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
	game_screen game_screen(Window->getSize().x, Window->getSize().y, Window);
	render_api* renderer = new render_api();
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
			game_screen.draw(*Window, plansza1, plansza2, 1);
			renderer->ustawiasz_statek(typ, nr, Window, 1, ustawiasz_statek);
			if (czy_error && !podaje_kierunek) {
				renderer->ustawiasz_statek(typ, nr, Window, 3, komunikat_bledu);
			}
			else {
				komunikat_bledu.setString("");
				Window->draw(komunikat_bledu);
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
							odpowiedz = czy_moze_tu_stac(wspolrzedna_y + 1, wspolrzedna_x + 1, plansza1);//sprawdzanie czy w wylosowanej pozycji moze stac statek
							if (odpowiedz == 0)
							{
								czy_error = true;
								//renderer->nie_mo¿na_postawiæ_statku();

							}
							else {
								czy_error = false;
								komunikat_bledu.setString("");
								Window->clear();
								plansza1[wspolrzedna_x][wspolrzedna_y] = '1';//wpisanie statku do tablicy w odpowiednie miejsce
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
									renderer->ustawiasz_statek(typ, nr, Window, 2, komunikat_kierunku);
									komunikat_bledu.setString("");
								}Window->display();
								if (kierunekevent.type == Event::KeyPressed)
								{
									if (kierunekevent.key.code == Keyboard::Up)
									{
										orientacja = 1;
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '2';
											plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '2';
											game_screen.PoleSelected = 0;
											nr++;
											if (nr == 4) { typ++; nr = 1; }renderer->wypisz_plansze(plansza1);
										}podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Down)
									{
										orientacja = 4;
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '2';
											plansza1[wspolrzedna_y][wspolrzedna_x + 1] = '2';
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
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '2';
											plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '2';
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
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 2, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '2';
											plansza1[wspolrzedna_y + 1][wspolrzedna_x] = '2';
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
									renderer->ustawiasz_statek(typ, nr, Window, 2, komunikat_kierunku); komunikat_bledu.setString("");
								}Window->display();
								if (kierunekevent.type == Event::KeyPressed)
								{
									if (kierunekevent.key.code == Keyboard::Up)
									{
										orientacja = 1;
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false;
											komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '3';
											plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '3';
											plansza1[wspolrzedna_y][wspolrzedna_x - 2] = '3';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 3) { typ++; nr = 1; }
										}podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Down)
									{
										orientacja = 4;
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 3, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '3';
											plansza1[wspolrzedna_y][wspolrzedna_x + 1] = '3';
											plansza1[wspolrzedna_y][wspolrzedna_x + 2] = '3';
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
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true;  podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y - 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '3';
											plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '3';
											plansza1[wspolrzedna_y - 2][wspolrzedna_x] = '3';
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
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 2, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 3, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											Window->clear();
											plansza1[wspolrzedna_y][wspolrzedna_x] = '3';
											plansza1[wspolrzedna_y + 1][wspolrzedna_x] = '3';
											plansza1[wspolrzedna_y + 2][wspolrzedna_x] = '3';
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
									komunikat_bledu.setString("");
									renderer->ustawiasz_statek(typ, nr, Window, 2, komunikat_kierunku);
								}
								Window->display();
								if (kierunekevent.type == Event::KeyPressed)
								{
									if (kierunekevent.key.code == Keyboard::Up)
									{
										orientacja = 1;
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 2, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											podaje_kierunek = false; break;
											czy_error = true;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1[wspolrzedna_y][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '4';
											plansza1[wspolrzedna_y][wspolrzedna_x - 2] = '4';
											plansza1[wspolrzedna_y][wspolrzedna_x - 3] = '4';
											game_screen.PoleSelected = 0;
											nr++; renderer->wypisz_plansze(plansza1);
											if (nr == 2) { typ++; nr = 1; }
										}podaje_kierunek = false;
										break;
									}
									if (kierunekevent.key.code == Keyboard::Down)
									{
										orientacja = 4;
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 3, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 4, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1[wspolrzedna_y][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y][wspolrzedna_x + 1] = '4';
											plansza1[wspolrzedna_y][wspolrzedna_x + 2] = '4';
											plansza1[wspolrzedna_y][wspolrzedna_x + 3] = '4';
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
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y - 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y - 2, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1[wspolrzedna_y][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y - 2][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y - 3][wspolrzedna_x] = '4';
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
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 1, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 2, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 3, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y + 4, plansza1);
										if (odpowiedz == 0)
										{
											czy_error = true; podaje_kierunek = false; break;
										}
										else {
											czy_error = false; komunikat_bledu.setString("");
											plansza1[wspolrzedna_y][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y + 1][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y + 2][wspolrzedna_x] = '4';
											plansza1[wspolrzedna_y + 3][wspolrzedna_x] = '4';
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
void render_api::render_planszy_gra(char plansza1[10][10], char plansza2[10][10], char plansza2_1[10][10], char plansza2_2[10][10], sf::RenderWindow* Window, int typ, unsigned int& oddane_strzaly_1, unsigned int& oddane_strzaly_2, unsigned int& trafienia_1, unsigned int& trafienia_2) {

	//t³o planszy
	RectangleShape game_background;
	game_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture game_texture;
	game_texture.loadFromFile("Texture/game_background.png");
	game_background.setTexture(&game_texture);

	//font
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	//tekst "Twoje pole:"
	sf::Text twojaplanszatekst;
	twojaplanszatekst.setFillColor(sf::Color::Green);
	twojaplanszatekst.setFont(retrofont);
	twojaplanszatekst.setCharacterSize(18);
	twojaplanszatekst.setPosition(Vector2f(120, 100));
	twojaplanszatekst.setString("Twoje pole:");

	//tekst "Pole przeciwnika:"
	sf::Text planszaprzeciwnikatekst;
	planszaprzeciwnikatekst.setFillColor(sf::Color::Red);
	planszaprzeciwnikatekst.setFont(retrofont);
	planszaprzeciwnikatekst.setCharacterSize(18);
	planszaprzeciwnikatekst.setPosition(Vector2f(456, 100));
	planszaprzeciwnikatekst.setString("Pole przeciwnika:");

	sf::Text komunikat;
	komunikat.setFillColor(sf::Color::Red);
	komunikat.setFont(retrofont);
	komunikat.setCharacterSize(18);
	komunikat.setPosition(Vector2f(333, 539));

	//³adowanie dostêpnych tekstur pól
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
	game_screen game_screen(Window->getSize().x, Window->getSize().y, Window);
	render_api* renderer = new render_api();
	int nr = 1;
	int odpowiedz = -1;
	int jezeli_wygrana = 0;
	bool podaje_kierunek = false;
	bool czy_error = false;
	bool czy_kontynuowaæ = true;
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja = 1;
	while (Window->isOpen() && czy_kontynuowaæ)
	{
		Event gevent;

		Window->clear();
		Window->draw(game_background);
		Window->draw(twojaplanszatekst);
		Window->draw(planszaprzeciwnikatekst);
		Window->draw(komunikat);
		game_screen.draw(*Window, plansza1, plansza2, 2);
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
						if (plansza2_1[wspolrzedna_y][wspolrzedna_x] == ' ')//jezeli uzytkownik strzelil w puste pole
						{
							if (typ == 1) {
								oddane_strzaly_1++;
								temp_shot1++;

							}
							if (typ == 2) {
								oddane_strzaly_2++;
								temp_shot2++;
							}
							//ustawianie oznaczenia strzalu w odpowiednich tablicach

							komunikat.setPosition(Vector2f(356, 539));
							komunikat.setString("Pudlo!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2);
							Window->display();
							plansza2_1[wspolrzedna_y][wspolrzedna_x] = '.';
							plansza2[wspolrzedna_x][wspolrzedna_y] = '.';
							czy_trafione = 0;
							czy_kontynuowaæ = false;
						}
						else if (plansza2_1[wspolrzedna_y][wspolrzedna_x] == 'x' || plansza2_1[wspolrzedna_y][wspolrzedna_x] == '.')//jezeli uzytkownik strzelil w juz strzelane pole
						{

							if (typ == 1) {
								oddane_strzaly_1++;
								temp_shot1++;


							}
							if (typ == 2) {
								oddane_strzaly_2++;
								temp_shot2++;
							}
							komunikat.setPosition(Vector2f(226, 539));
							komunikat.setString("Strzelales juz tutaj!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2);
							Window->display();
							czy_trafione = 2;
							czy_kontynuowaæ = false;
						}
						else//jezeli uzytkownik trafil
						{
							if (typ == 1) {
								oddane_strzaly_1++;

								temp_shot1++;

								trafienia_1++;

								temp_hit1++;

							}
							if (typ == 2) {
								oddane_strzaly_2++;

								temp_shot2++;
								trafienia_2++;

								temp_hit2++;
							}

							komunikat.setString("Trafiles!");
							czy_kontynuowaæ = true;
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2);
							Window->display();
							//umieszczanie odpowiednich oznaczen statkow na tablicach
							if (plansza2_1[wspolrzedna_y][wspolrzedna_x] == '1')//jezeli statek jednomasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							else if (plansza2_1[wspolrzedna_y][wspolrzedna_x] == '2')//jezeli statek dwumasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							else if (plansza2_1[wspolrzedna_y][wspolrzedna_x] == '3')//jezeli statek trzymasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							else if (plansza2_1[wspolrzedna_y][wspolrzedna_x] == '4')//jezeli statek czteromasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							plansza2_1[wspolrzedna_y][wspolrzedna_x] = 'x';//ustawienie na planszy drugiego gracza oznaczenia, ze przeciwnik trafil
							czy_trafione = 1;
							jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
							if (jezeli_wygrana == 1)//jezeli wygral
							{
								czy_kontynuowaæ = false;
								//wygrana(nick1);//wyswietlenie statystyk
								break;
							}
						}
						std::cout << "PLANSZA2_1\n";
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++) {
								if (plansza2_1[j][i] != ' ')
									std::cout << plansza2_1[j][i];
								else std::cout << '-';
							}std::cout << "\n";
						}
					}
					//typ 3 jest ok - NIE RUSZAC!
					else if (typ == 3) {
						if (plansza2_1[wspolrzedna_x][wspolrzedna_y] == ' ')//jezeli uzytkownik strzelil w puste pole
						{
							//ustawianie oznaczenia strzalu w odpowiednich tablicach

							oddane_strzaly_1++;
							temp_shot1++;


							komunikat.setPosition(Vector2f(356, 539));
							komunikat.setString("Pudlo!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2);
							Window->display();
							plansza2_1[wspolrzedna_x][wspolrzedna_y] = '.';
							plansza2[wspolrzedna_x][wspolrzedna_y] = '.';
							czy_trafione = 0;
							czy_kontynuowaæ = false;
						}
						else if (plansza2_1[wspolrzedna_x][wspolrzedna_y] == 'x' || plansza2_1[wspolrzedna_x][wspolrzedna_y] == '.')//jezeli uzytkownik strzelil w juz strzelane pole
						{

							oddane_strzaly_1++;
							temp_shot1++;

							komunikat.setPosition(Vector2f(226, 539));
							komunikat.setString("Strzelales juz tutaj!");
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2);
							Window->display();
							czy_trafione = 2;
							czy_kontynuowaæ = false;
						}
						else//jezeli uzytkownik trafil
						{
							oddane_strzaly_1++;
							temp_shot1++;

							trafienia_1++;
							temp_hit1++;

							komunikat.setString("Trafiles!");
							czy_kontynuowaæ = true;
							Window->clear();
							Window->draw(game_background);
							Window->draw(twojaplanszatekst);
							Window->draw(planszaprzeciwnikatekst);
							Window->draw(komunikat);
							game_screen.draw(*Window, plansza1, plansza2, 2);
							Window->display();
							//umieszczanie odpowiednich oznaczen statkow na tablicach
							if (plansza2_1[wspolrzedna_x][wspolrzedna_y] == '1')//jezeli statek jednomasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							else if (plansza2_1[wspolrzedna_x][wspolrzedna_y] == '2')//jezeli statek dwumasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							else if (plansza2_1[wspolrzedna_x][wspolrzedna_y] == '3')//jezeli statek trzymasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							else if (plansza2_1[wspolrzedna_x][wspolrzedna_y] == '4')//jezeli statek czteromasztowy
							{
								plansza2[wspolrzedna_x][wspolrzedna_y] = 'x';
							}
							plansza2_1[wspolrzedna_x][wspolrzedna_y] = 'x';//ustawienie na planszy drugiego gracza oznaczenia, ze przeciwnik trafil
							czy_trafione = 1;
							jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
							if (jezeli_wygrana == 1)//jezeli wygral
							{
								czy_kontynuowaæ = false;
								//wygrana(nick1);//wyswietlenie statystyk
								break;
							}
						}
						std::cout << "PLANSZA1_2\n";
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++) {
								if (plansza2[i][j] != ' ')
									std::cout << plansza2[i][j];
								else std::cout << '-';
							}std::cout << "\n";
						}
						std::cout << "PLANSZA2_1\n";
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++) {
								if (plansza2_1[i][j] != ' ')
									std::cout << plansza2_1[i][j];
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
void render_api::przeka¿_komputer(sf::RenderWindow* Window) {
	sf::RectangleShape przekaz_background;
	przekaz_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture przekaz_background_texture;
	przekaz_background_texture.loadFromFile("Texture/game_background.png");
	przekaz_background.setTexture(&przekaz_background_texture);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	sf::Text przekaz_text;
	przekaz_text.setFillColor(sf::Color::Black);
	przekaz_text.setFont(retrofont);
	przekaz_text.setCharacterSize(18);
	przekaz_text.setPosition(sf::Vector2f(100, 100));
	przekaz_text.setString("Przekaz komputer drugiemu graczowi");
	sf::Text enter_text;
	enter_text.setFillColor(sf::Color::Black);
	enter_text.setFont(retrofont);
	enter_text.setCharacterSize(22);
	enter_text.setPosition(sf::Vector2f(86, 500));
	enter_text.setString("Wcisnij ENTER, aby kontynuowac");

	Window->draw(przekaz_background);
	Window->draw(przekaz_text);
	Window->draw(enter_text);
	Window->display();
}
void render_api::komputer_ustawia_statki(sf::RenderWindow* Window) {
	sf::RectangleShape ustawienie_statkow_bota_background;
	ustawienie_statkow_bota_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture ustawienie_statkow_bota_texture;
	ustawienie_statkow_bota_texture.loadFromFile("Texture/game_background.png");
	ustawienie_statkow_bota_background.setTexture(&ustawienie_statkow_bota_texture);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	sf::Text ustawienie_statkow_bota_text;
	ustawienie_statkow_bota_text.setFillColor(sf::Color::Black);
	ustawienie_statkow_bota_text.setFont(retrofont);
	ustawienie_statkow_bota_text.setCharacterSize(24);
	ustawienie_statkow_bota_text.setPosition(sf::Vector2f(134, 300));
	ustawienie_statkow_bota_text.setString("Komputer ustawia statki");

	
	Window->draw(ustawienie_statkow_bota_background);
	Window->draw(ustawienie_statkow_bota_text);
	Window->display();
	sf::sleep(sf::milliseconds(1000)); 
	clear_screen(Window);
}
void render_api::ruch_wykonuje_komputer(sf::RenderWindow* Window) {

	sf::RectangleShape ruch_komputera_background;
	ruch_komputera_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture ruch_komputera_texture;
	ruch_komputera_texture.loadFromFile("Texture/game_background.png");
	ruch_komputera_background.setTexture(&ruch_komputera_texture);

	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	sf::Text ruch_komputera_text;
	ruch_komputera_text.setFillColor(sf::Color::Black);
	ruch_komputera_text.setFont(retrofont);
	ruch_komputera_text.setCharacterSize(24);
	ruch_komputera_text.setPosition(sf::Vector2f(154, 300));
	ruch_komputera_text.setString("Ruch wykonuje komputer");




	Window->draw(ruch_komputera_background);
	Window->draw(ruch_komputera_text);
	Window->display();
	//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
	sf::sleep(sf::milliseconds(1000));
	Window->clear();
}
int render_api::czy_wygrana(char plansza[10][10])//funkcja sprawdza czy w przeslanej tablicy znajduja sie jeszcze symbole oznaczajace niezatopiony statek i zwraca odpowiednia informacje
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (plansza[i][k] == '1' || plansza[i][k] == '2' || plansza[i][k] == '3' || plansza[i][k] == '4')
			{
				return 0;
			}
		}
	}

	return 1;
}
void render_api::drukuj_statystyki(sf::RenderWindow* Window, char* nick, char* nick1, char* nick2, int oddane_strzaly_1, int oddane_strzaly_2, int trafienia_1, int trafienia_2) {
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture background_texture;
	background_texture.loadFromFile("Texture/game_background.png");
	background.setTexture(&background_texture);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	//tekst "Twoje pole:"
	sf::Text game_over_text;
	game_over_text.setFillColor(sf::Color::Black);
	game_over_text.setFont(retrofont);
	game_over_text.setCharacterSize(38);
	game_over_text.setPosition(sf::Vector2f(230, 100));
	game_over_text.setString("KONIEC GRY");

	sf::Text wygral;
	wygral.setFillColor(sf::Color::Black);
	wygral.setFont(retrofont);
	wygral.setCharacterSize(38);
	wygral.setPosition(sf::Vector2f(145, 160));
	wygral.setString("Wygral: " + std::string(nick));

	sf::Text player1_name;
	player1_name.setFillColor(sf::Color::Black);
	player1_name.setFont(retrofont);
	player1_name.setCharacterSize(38);
	player1_name.setPosition(sf::Vector2f(76, 300));
	player1_name.setString(nick1);

	sf::Text player2_name;
	player2_name.setFillColor(sf::Color::Black);
	player2_name.setFont(retrofont);
	player2_name.setCharacterSize(38);
	player2_name.setPosition(sf::Vector2f(76, 400));
	player2_name.setString(nick2);

	sf::Text oddane_strzaly_player1_text;
	oddane_strzaly_player1_text.setFillColor(sf::Color::Black);
	oddane_strzaly_player1_text.setFont(retrofont);
	oddane_strzaly_player1_text.setCharacterSize(38);
	oddane_strzaly_player1_text.setPosition(sf::Vector2f(500, 300));
	oddane_strzaly_player1_text.setString(to_string(oddane_strzaly_1));

	sf::Text oddane_strzaly_player2_text;
	oddane_strzaly_player2_text.setFillColor(sf::Color::Black);
	oddane_strzaly_player2_text.setFont(retrofont);
	oddane_strzaly_player2_text.setCharacterSize(38);
	oddane_strzaly_player2_text.setPosition(sf::Vector2f(500, 400));
	oddane_strzaly_player2_text.setString(to_string(oddane_strzaly_2));

	sf::Text trafienia_player1_text;
	trafienia_player1_text.setFillColor(sf::Color::Black);
	trafienia_player1_text.setFont(retrofont);
	trafienia_player1_text.setCharacterSize(38);
	trafienia_player1_text.setPosition(sf::Vector2f(680, 300));
	trafienia_player1_text.setString(to_string(trafienia_1));

	sf::Text trafienia_player2_text;
	trafienia_player2_text.setFillColor(sf::Color::Black);
	trafienia_player2_text.setFont(retrofont);
	trafienia_player2_text.setCharacterSize(38);
	trafienia_player2_text.setPosition(sf::Vector2f(680, 400));
	trafienia_player2_text.setString(to_string(trafienia_2));

	sf::Text shots_text;
	shots_text.setFillColor(sf::Color::Black);
	shots_text.setFont(retrofont);
	shots_text.setCharacterSize(18);
	shots_text.setPosition(sf::Vector2f(460, 240));
	shots_text.setString("Strzalów:");

	sf::Text hit_text;
	hit_text.setFillColor(sf::Color::Black);
	hit_text.setFont(retrofont);
	hit_text.setCharacterSize(18);
	hit_text.setPosition(sf::Vector2f(630, 240));
	hit_text.setString("Trafieñ:");

	sf::Text enter_text;
	enter_text.setFillColor(sf::Color::Black);
	enter_text.setFont(retrofont);
	enter_text.setCharacterSize(22);
	enter_text.setPosition(sf::Vector2f(86, 500));
	enter_text.setString("Wcisnij ENTER, aby kontynuowac");

	Window->draw(background);
	Window->draw(game_over_text);
	Window->draw(wygral);
	Window->draw(player1_name);
	Window->draw(player2_name);
	Window->draw(oddane_strzaly_player1_text);
	Window->draw(oddane_strzaly_player2_text);
	Window->draw(trafienia_player1_text);
	Window->draw(trafienia_player2_text);
	Window->draw(hit_text);
	Window->draw(shots_text);
	Window->draw(enter_text);

	Window->display();
}




void render_api::czy_zapisac_gre(sf::RenderWindow* Window, zapis_save_yes_no zapis_yes_no) {
	RectangleShape pusty_background;
	pusty_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture pusty_texture;
	pusty_texture.loadFromFile("Texture/game_background.png");
	pusty_background.setTexture(&pusty_texture);

	Window->clear();
	Window->draw(pusty_background);
	zapis_yes_no.draw(*Window);
	Window->display();
}
void render_api::zapisano_pomyœlnie(sf::RenderWindow* Window) {
	sf::RectangleShape zapis_udany_background;
	zapis_udany_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture zapis_udany_texture;
	zapis_udany_texture.loadFromFile("Texture/zapis_udany.png");
	zapis_udany_background.setTexture(&zapis_udany_texture);

	Window->clear();
	Window->draw(zapis_udany_background);
	Window->display();
}




void render_api::wczytaj_save_background_method(sf::RenderWindow* Window, sf::Text text) {
	sf::RectangleShape Wczytaj_save_background;
	Wczytaj_save_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture wczytaj_save_Texture;
	wczytaj_save_Texture.loadFromFile("Texture/podaj_nazwê_pliku.png");
	Wczytaj_save_background.setTexture(&wczytaj_save_Texture);


	Window->clear();
	Window->draw(Wczytaj_save_background);
	Window->draw(text);
	Window->display();
}
void render_api::plik_uszkodzony(sf::RenderWindow* Window) {
	RectangleShape plik_uszkodzony_background;
	plik_uszkodzony_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture plik_uszkodzony_Texture;
	plik_uszkodzony_Texture.loadFromFile("Texture/plik_uszkodzony.png");
	plik_uszkodzony_background.setTexture(&plik_uszkodzony_Texture);

	Window->draw(plik_uszkodzony_background);
	Window->display();
}
void render_api::b³¹d_odczytu_save(sf::RenderWindow* Window, sf::Text text) {

	RectangleShape b³¹d_odczytu_background;
	b³¹d_odczytu_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture b³¹d_odczytu_Texture;
	b³¹d_odczytu_Texture.loadFromFile("Texture/b³¹d_odczytu.png");
	b³¹d_odczytu_background.setTexture(&b³¹d_odczytu_Texture);

	Window->draw(b³¹d_odczytu_background);
	Window->draw(text);
	Window->display();
}
void render_api::zaczyna(sf::RenderWindow* Window, char* nick1)
{
	int count = 3;
	sf::Text text_odliczania;
	sf::Text text_odliczania2;
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	text_odliczania.setFillColor(sf::Color::Black);
	text_odliczania.setFont(retrofont);
	text_odliczania.setCharacterSize(30);
	text_odliczania.setPosition(sf::Vector2f(136, 157));
	text_odliczania.setString("");

	text_odliczania2.setFillColor(sf::Color::Black);
	text_odliczania2.setFont(retrofont);
	text_odliczania2.setCharacterSize(24);
	text_odliczania2.setPosition(sf::Vector2f(294, 400));
	text_odliczania2.setString("");
	sf::RectangleShape wczytaj_save_background;
	wczytaj_save_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture wczytaj_save_texture;
	wczytaj_save_texture.loadFromFile("Texture/game_background.png");
	wczytaj_save_background.setTexture(&wczytaj_save_texture);

	while (Window->isOpen() && count > 0)
	{
		Window->clear();
		text_odliczania.setString("Rozpoczyna: " + string(nick1));
		text_odliczania2.setString("Start za " + to_string(count));
		Window->draw(wczytaj_save_background);
		Window->draw(text_odliczania);
		Window->draw(text_odliczania2);
		Window->display();
		count--;
		sf::sleep(sf::milliseconds(1000));
	}
}




void render_api::instrukcja(sf::RenderWindow* Window) {
	//photo to instructions
	RectangleShape Instrukcja_background;
	Instrukcja_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture InstructionTexture;
	InstructionTexture.loadFromFile("Texture/Instruction_photo.png");
	Instrukcja_background.setTexture(&InstructionTexture);


	Window->clear();
	Window->draw(Instrukcja_background);
	Window->display();
}
void render_api::twórcy(sf::RenderWindow* Window) {

	RectangleShape Twórcy_background;
	Twórcy_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture AboutTexture;
	AboutTexture.loadFromFile("Texture/About_photo.png");
	Twórcy_background.setTexture(&AboutTexture);


	Window->clear();
	Window->draw(Twórcy_background);
	Window->display();
}
void render_api::draw_empty_background(sf::RenderWindow* Window)
{
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture MainTexture;
	MainTexture.loadFromFile("Texture/menu_background.jpg");
	background.setTexture(&MainTexture);
	Window->clear();
	Window->draw(background);
	Window->display();
}
void render_api::wypisz_plansze(char plansza[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (plansza[j][i] == ' ') cout << '-';
			else cout << plansza[j][i];
		}cout << "\n";
	}
	cout << "\n";
}
void render_api::clear_screen(sf::RenderWindow* Window) {
	Window->clear();
}