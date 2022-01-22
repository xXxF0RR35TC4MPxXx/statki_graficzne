#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include "dziedziczace.h"
#include "SFMLFactory.h"
#include "render_api.h"
#include "game_screen.h"
#include "render_handler.h"

#pragma warning(disable:4996)

#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822

#define TILE_WIDTH 30
#define TILE_HEIGHT 30

const string FONT_DIR = "retrofont.ttf";

using std::to_string;

render_api::render_api(){}

render_api* render_api::singleton = nullptr;

render_api* render_api::GetInstance() {
	if (singleton == nullptr) {
		singleton = new render_api();
	}
	return singleton;
}

void render_api::rysujMenu(sf::RenderWindow* Window, mainmenu MainMenu) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/menu_background.jpg");
	auto background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(background);
	MainMenu.draw(*Window);
	Window->display();
}
void render_api::wybor_typ_gry(sf::RenderWindow* Window, wybor_typu_gry wybor_typu_gry) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/menu_background.jpg");
	auto background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(background);
	wybor_typu_gry.draw(*Window);
	Window->display();
}
std::string render_api::podaj_nick(sf::RenderWindow* Window) {
	sf::Font* f = new Font();
	f->loadFromFile(FONT_DIR);
	sf::Text t = *SFMLFactory::createText("", *f, 50, 75, 250);
	string s;
	sf::Texture* tx = new Texture();
	tx->loadFromFile("Texture/podaj_nick.png");
	RectangleShape podaj_nick_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *tx);
	while (Window->isOpen())
	{
		Window->clear();
		Window->draw(podaj_nick_background);
		Window->draw(t); //tutaj error
		Window->display();

		return RenderHandler::handleNickEvent(Window, &t);
	}	
}
void render_api::ustawiasz_statek(int typ, int nr, sf::RenderWindow* Window, int typ_wiadomosci) {
	string s;
	int x, y, csize;
	std::tie(s, x, y, csize) = RenderHandler::handleShipPlacement(typ_wiadomosci, typ, nr);
	
	sf::Font* f = new Font();
	f->loadFromFile(FONT_DIR);
	auto napis = *SFMLFactory::createText(s, *f, csize, x, y);
	napis.setFillColor(sf::Color::Black);
	Window->draw(napis);
}

void render_api::render_planszy_przy_ustawianiu(Plansza plansza1, Plansza plansza2, sf::RenderWindow* Window) {

	//tlo planszy
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	auto game_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);

	//font
	sf::Font* retrofont = new Font();
	retrofont->loadFromFile(FONT_DIR);

	//tekst "Twoje pole:"
	auto twojaplanszatekst = *SFMLFactory::createText("Twoje pole:", *retrofont, 18, 120, 100);
	twojaplanszatekst.setFillColor(sf::Color::Green);

	//tekst "Pole przeciwnika:"
	auto planszaprzeciwnikatekst = *SFMLFactory::createText("Pole przeciwnika:", *retrofont, 18, 456, 100);
	planszaprzeciwnikatekst.setFillColor(sf::Color::Red);

	sf::Text ustawiasz_statek;
	sf::Text komunikat_bledu;
	sf::Text komunikat_kierunku;

	//�adowanie dost�pnych tekstur p�l
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
			renderer->ustawiasz_statek(typ, nr, Window, 1);
			if (czy_error && !podaje_kierunek) {
				renderer->ustawiasz_statek(typ, nr, Window, 3);
			}
			else {
				renderer->ustawiasz_statek(typ, nr, Window, 4);
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
									renderer->ustawiasz_statek(typ, nr, Window, 2);
									renderer->ustawiasz_statek(typ, nr, Window, 4);
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
									renderer->ustawiasz_statek(typ, nr, Window, 2); 
									renderer->ustawiasz_statek(typ, nr, Window, 4);
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
									renderer->ustawiasz_statek(typ, nr, Window, 4);
									renderer->ustawiasz_statek(typ, nr, Window, 2);
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
void render_api::render_planszy_gra(Plansza plansza1, Plansza plansza2, Plansza plansza2_1, Plansza plansza2_2, sf::RenderWindow* Window, int typ, unsigned int& oddane_strzaly_1, unsigned int& oddane_strzaly_2, unsigned int& trafienia_1, unsigned int& trafienia_2) {

	//tlo planszy
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	auto game_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT,*t);

	//tekst "Twoje pole:"
	sf::Font f;
	f.loadFromFile(FONT_DIR);
	auto twojaplanszatekst = *SFMLFactory::createText("Twoje pole:", f, 18, 120, 100);
	twojaplanszatekst.setFillColor(sf::Color::Green);

	//tekst "Pole przeciwnika:"
	auto planszaprzeciwnikatekst = *SFMLFactory::createText("Pole przeciwnika:", f, 18, 456, 100);
	planszaprzeciwnikatekst.setFillColor(sf::Color::Red);

	auto komunikat = *SFMLFactory::createText("", f, 18, 333, 539);
	komunikat.setFillColor(sf::Color::Red);

	//ladowanie dostepnych tekstur pol
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
	//render_api* renderer = this->GetInstance();
	//int nr = 1;
	//int odpowiedz = -1;
	//int jezeli_wygrana = 0;
	//bool podaje_kierunek = false;
	//bool czy_error = false;
	//bool czy_kontynuowac = true;
	//unsigned int wspolrzedna_x, wspolrzedna_y, orientacja = 1;
	//RenderHandler::handleBoardGame(game_background, sprite_pustego_pola_texture,
	//	sprite_1_tile, sprite_2_tile, sprite_3_tile, sprite_4_tile,
	//	sprite_hit_tile, sprite_miss_tile, twojaplanszatekst,
	//	planszaprzeciwnikatekst, komunikat,
	//	game_screen, plansza1, plansza2, plansza2_1, plansza2_2,
	//	Window, typ, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
	//while (Window->isOpen() && czy_kontynuowac)
	//{
	//	Event gevent;

	//	Window->clear();
	//	Window->draw(game_background);
	//	Window->draw(twojaplanszatekst);
	//	Window->draw(planszaprzeciwnikatekst);
	//	Window->draw(komunikat);
	//	game_screen.draw(*Window, plansza1, plansza2, 2);
	//	Window->display();
	//	wspolrzedna_x = 0;
	//	int czy_trafione = 0;
	//	wspolrzedna_y = 0;
	//	while (Window->pollEvent(gevent))
	//	{
	//		if (gevent.type == Event::MouseButtonPressed) {

	//		}
	//		if (gevent.type == Event::KeyPressed) {
	//			if (gevent.key.code == Keyboard::Up)
	//			{
	//				game_screen.MoveUp(plansza2, 2);
	//				break;
	//			}
	//			if (gevent.key.code == Keyboard::Down) {
	//				game_screen.MoveDown(plansza2, 2);
	//				break;
	//			}
	//			if (gevent.key.code == Keyboard::Left) {
	//				game_screen.MoveLeft(plansza2, 2);
	//				break;
	//			}
	//			if (gevent.key.code == Keyboard::Right) {
	//				game_screen.MoveRight(plansza2, 2);
	//				break;
	//			}
	//			if (gevent.key.code == Keyboard::Return)
	//			{

	//				wspolrzedna_x = floor(game_screen.PoleSelected / 10);
	//				wspolrzedna_y = game_screen.PoleSelected % 10;


	//				if (typ == 1 || typ == 2) {
	//					if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == ' ')//jezeli uzytkownik strzelil w puste pole
	//					{
	//						if (typ == 1) {
	//							oddane_strzaly_1++;
	//							temp_shot1++;

	//						}
	//						if (typ == 2) {
	//							oddane_strzaly_2++;
	//							temp_shot2++;
	//						}
	//						//ustawianie oznaczenia strzalu w odpowiednich tablicach

	//						komunikat.setPosition(Vector2f(356, 539));
	//						komunikat.setString("Pudlo!");
	//						Window->clear();
	//						Window->draw(game_background);
	//						Window->draw(twojaplanszatekst);
	//						Window->draw(planszaprzeciwnikatekst);
	//						Window->draw(komunikat);
	//						game_screen.draw(*Window, plansza1, plansza2, 2);
	//						Window->display();
	//						plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = '.';
	//						plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = '.';
	//						czy_trafione = 0;
	//						czy_kontynuowac = false;
	//					}
	//					else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == 'x' || plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '.')//jezeli uzytkownik strzelil w juz strzelane pole
	//					{

	//						if (typ == 1) {
	//							oddane_strzaly_1++;
	//							temp_shot1++;


	//						}
	//						if (typ == 2) {
	//							oddane_strzaly_2++;
	//							temp_shot2++;
	//						}
	//						komunikat.setPosition(Vector2f(226, 539));
	//						komunikat.setString("Strzelales juz tutaj!");
	//						Window->clear();
	//						Window->draw(game_background);
	//						Window->draw(twojaplanszatekst);
	//						Window->draw(planszaprzeciwnikatekst);
	//						Window->draw(komunikat);
	//						game_screen.draw(*Window, plansza1, plansza2, 2);
	//						Window->display();
	//						czy_trafione = 2;
	//						czy_kontynuowac = false;
	//					}
	//					else//jezeli uzytkownik trafil
	//					{
	//						if (typ == 1) {
	//							oddane_strzaly_1++;

	//							temp_shot1++;

	//							trafienia_1++;

	//							temp_hit1++;

	//						}
	//						if (typ == 2) {
	//							oddane_strzaly_2++;

	//							temp_shot2++;
	//							trafienia_2++;

	//							temp_hit2++;
	//						}

	//						komunikat.setString("Trafiles!");
	//						czy_kontynuowac = true;
	//						Window->clear();
	//						Window->draw(game_background);
	//						Window->draw(twojaplanszatekst);
	//						Window->draw(planszaprzeciwnikatekst);
	//						Window->draw(komunikat);
	//						game_screen.draw(*Window, plansza1, plansza2, 2);
	//						Window->display();
	//						//umieszczanie odpowiednich oznaczen statkow na tablicach
	//						if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '1')//jezeli statek jednomasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '2')//jezeli statek dwumasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '3')//jezeli statek trzymasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						else if (plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol == '4')//jezeli statek czteromasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						plansza2_1.pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol = 'x';//ustawienie na planszy drugiego gracza oznaczenia, ze przeciwnik trafil
	//						czy_trafione = 1;
	//						jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
	//						if (jezeli_wygrana == 1)//jezeli wygral
	//						{
	//							czy_kontynuowac = false;
	//							//wygrana(nick1);//wyswietlenie statystyk
	//							break;
	//						}
	//					}
	//					std::cout << "PLANSZA2_1\n";
	//					for (int i = 0; i < 10; i++) {
	//						for (int j = 0; j < 10; j++) {
	//							if (plansza2_1.pola_planszy[j][i]->symbol != ' ')
	//								std::cout << plansza2_1.pola_planszy[j][i]->symbol;
	//							else std::cout << '-';
	//						}std::cout << "\n";
	//					}
	//				}
	//				//typ 3 jest ok - NIE RUSZAC!
	//				else if (typ == 3) {
	//					if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == ' ')//jezeli uzytkownik strzelil w puste pole
	//					{
	//						//ustawianie oznaczenia strzalu w odpowiednich tablicach

	//						oddane_strzaly_1++;
	//						temp_shot1++;


	//						komunikat.setPosition(Vector2f(356, 539));
	//						komunikat.setString("Pudlo!");
	//						Window->clear();
	//						Window->draw(game_background);
	//						Window->draw(twojaplanszatekst);
	//						Window->draw(planszaprzeciwnikatekst);
	//						Window->draw(komunikat);
	//						game_screen.draw(*Window, plansza1, plansza2, 2);
	//						Window->display();
	//						plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = '.';
	//						plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = '.';
	//						czy_trafione = 0;
	//						czy_kontynuowac = false;
	//					}
	//					else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == 'x' || plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '.')//jezeli uzytkownik strzelil w juz strzelane pole
	//					{

	//						oddane_strzaly_1++;
	//						temp_shot1++;

	//						komunikat.setPosition(Vector2f(226, 539));
	//						komunikat.setString("Strzelales juz tutaj!");
	//						Window->clear();
	//						Window->draw(game_background);
	//						Window->draw(twojaplanszatekst);
	//						Window->draw(planszaprzeciwnikatekst);
	//						Window->draw(komunikat);
	//						game_screen.draw(*Window, plansza1, plansza2, 2);
	//						Window->display();
	//						czy_trafione = 2;
	//						czy_kontynuowac = false;
	//					}
	//					else//jezeli uzytkownik trafil
	//					{
	//						oddane_strzaly_1++;
	//						temp_shot1++;

	//						trafienia_1++;
	//						temp_hit1++;

	//						komunikat.setString("Trafiles!");
	//						czy_kontynuowac = true;
	//						Window->clear();
	//						Window->draw(game_background);
	//						Window->draw(twojaplanszatekst);
	//						Window->draw(planszaprzeciwnikatekst);
	//						Window->draw(komunikat);
	//						game_screen.draw(*Window, plansza1, plansza2, 2);
	//						Window->display();
	//						//umieszczanie odpowiednich oznaczen statkow na tablicach
	//						if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '1')//jezeli statek jednomasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '2')//jezeli statek dwumasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '3')//jezeli statek trzymasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						else if (plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol == '4')//jezeli statek czteromasztowy
	//						{
	//							plansza2.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';
	//						}
	//						plansza2_1.pola_planszy[wspolrzedna_x][wspolrzedna_y]->symbol = 'x';//ustawienie na planszy drugiego gracza oznaczenia, ze przeciwnik trafil
	//						czy_trafione = 1;
	//						jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
	//						if (jezeli_wygrana == 1)//jezeli wygral
	//						{
	//							czy_kontynuowac = false;
	//							//wygrana(nick1);//wyswietlenie statystyk
	//							break;
	//						}
	//					}
	//					std::cout << "PLANSZA1_2\n";
	//					for (int i = 0; i < 10; i++) {
	//						for (int j = 0; j < 10; j++) {
	//							if (plansza2.pola_planszy[i][j]->symbol != ' ')
	//								std::cout << plansza2.pola_planszy[i][j]->symbol;
	//							else std::cout << '-';
	//						}std::cout << "\n";
	//					}
	//					std::cout << "PLANSZA2_1\n";
	//					for (int i = 0; i < 10; i++) {
	//						for (int j = 0; j < 10; j++) {
	//							if (plansza2_1.pola_planszy[i][j]->symbol != ' ')
	//								std::cout << plansza2_1.pola_planszy[i][j]->symbol;
	//							else std::cout << '-';
	//						}std::cout << "\n";
	//					}
	//				}
	//			}
	//		}
	//		if (gevent.type == Event::Closed) {
	//			Window->close();
	//		}
	//		//Window->display();
	//	}
	//}
}
void render_api::przekaz_komputer(sf::RenderWindow* Window) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	sf::RectangleShape przekaz_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);

	sf::Font f;
	f.loadFromFile(FONT_DIR);

	sf::Text przekaz_text = *SFMLFactory::createText("Przekaz komputer drugiemu graczowi", f, 18, 100, 100);
	przekaz_text.setFillColor(sf::Color::Black);

	sf::Text enter_text = *SFMLFactory::createText("Wcisnij ENTER, aby kontynuowac", f, 22, 86, 500);
	enter_text.setFillColor(sf::Color::Black);

	Window->draw(przekaz_background);
	Window->draw(przekaz_text);
	Window->draw(enter_text);
	Window->display();
}
void render_api::komputer_ustawia_statki(sf::RenderWindow* Window) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture / game_background.png");

	sf::Font* f = new sf::Font();
	f->loadFromFile(FONT_DIR);
	auto ustawienie_statkow_bota_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	auto ustawienie_statkow_bota_text = *SFMLFactory::createText("Komputer ustawia statki", *f, 24, 134, 300);
	ustawienie_statkow_bota_text.setFillColor(sf::Color::Black);
	
	Window->draw(ustawienie_statkow_bota_background);
	Window->draw(ustawienie_statkow_bota_text);
	Window->display();
	sf::sleep(sf::milliseconds(1000)); 
	clear_screen(Window);
}
void render_api::ruch_wykonuje_komputer(sf::RenderWindow* Window) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	auto ruch_komputera_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);

	sf::Font* f = new Font();
	f->loadFromFile(FONT_DIR);
	auto ruch_komputera_text = *SFMLFactory::createText("Ruch wykonuje komputer", *f, 24, 154, 300);
	ruch_komputera_text.setFillColor(sf::Color::Black);

	Window->draw(ruch_komputera_background);
	Window->draw(ruch_komputera_text);
	Window->display();
	//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
	sf::sleep(sf::milliseconds(1000));
	Window->clear();
}
int render_api::czy_wygrana(Plansza plansza)//funkcja sprawdza czy w przeslanej tablicy znajduja sie jeszcze symbole oznaczajace niezatopiony statek i zwraca odpowiednia informacje
{
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
void render_api::drukuj_statystyki(sf::RenderWindow* Window, char* nick, char* nick1, char* nick2, int oddane_strzaly_1, int oddane_strzaly_2, int trafienia_1, int trafienia_2) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	auto background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);

	sf::Font* f= new sf::Font();
	f->loadFromFile(FONT_DIR);
	//tekst "Twoje pole:"
	auto game_over_text = *SFMLFactory::createText("KONIEC GRY", *f, 38, 230, 100);
	game_over_text.setFillColor(sf::Color::Black);

	auto wygral = *SFMLFactory::createText("Wygral: " + std::string(nick), *f, 38, 145, 160);
	wygral.setFillColor(sf::Color::Black);

	auto player1_name = *SFMLFactory::createText(nick1, *f, 38, 76, 300);
	player1_name.setFillColor(sf::Color::Black);

	auto player2_name = *SFMLFactory::createText(nick2, *f, 38, 76, 400);
	player2_name.setFillColor(sf::Color::Black);

	auto oddane_strzaly_player1_text = *SFMLFactory::createText(to_string(oddane_strzaly_1), *f, 38, 500, 300);
	oddane_strzaly_player1_text.setFillColor(sf::Color::Black);

	auto oddane_strzaly_player2_text = *SFMLFactory::createText(to_string(oddane_strzaly_2), *f, 38, 500, 400);
	oddane_strzaly_player2_text.setFillColor(sf::Color::Black);

	auto trafienia_player1_text = *SFMLFactory::createText(to_string(trafienia_1), *f, 38, 680, 300);
	trafienia_player1_text.setFillColor(sf::Color::Black);

	auto trafienia_player2_text = *SFMLFactory::createText(to_string(trafienia_2), *f, 38, 680, 400);
	trafienia_player2_text.setFillColor(sf::Color::Black);

	auto shots_text = *SFMLFactory::createText("Strzalów:", *f, 18, 460, 240);
	shots_text.setFillColor(sf::Color::Black);

	auto hit_text = *SFMLFactory::createText("Trafien:", *f, 18, 630, 240);
	hit_text.setFillColor(sf::Color::Black);

	auto enter_text = *SFMLFactory::createText("Wcisnij ENTER, aby kontynuowac", *f, 22, 86, 500);
	enter_text.setFillColor(sf::Color::Black);

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
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	auto pusty_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(pusty_background);
	zapis_yes_no.draw(*Window);
	Window->display();
}

void render_api::zapisano_pomyslnie(sf::RenderWindow* Window) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/zapis_udany.png");
	auto zapis_udany_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(zapis_udany_background);
	Window->display();
}

void render_api::wczytaj_save_background_method(sf::RenderWindow* Window, sf::Text text) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/podaj_nazwe_pliku.png");
	auto Wczytaj_save_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(Wczytaj_save_background);
	Window->draw(text);
	Window->display();
}
void render_api::plik_uszkodzony(sf::RenderWindow* Window) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/plik_uszkodzony.png");
	auto plik_uszkodzony_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->draw(plik_uszkodzony_background);
	Window->display();
}
void render_api::blad_odczytu_save(sf::RenderWindow* Window, sf::Text text) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/blad_odczytu.png");
	
	auto blad_odczytu_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->draw(blad_odczytu_background);
	Window->draw(text);
	Window->display();
}
void render_api::zaczyna(sf::RenderWindow* Window, char* nick1)
{
	sf::Font* f= new sf::Font();
	f->loadFromFile(FONT_DIR);
	int count = 3;
	sf::Text text_odliczania = *SFMLFactory::createText("", *f, 30, 136, 157);
	sf::Text text_odliczania2 = *SFMLFactory::createText("", *f, 24, 294, 400);
	text_odliczania.setFillColor(sf::Color::Black);
	text_odliczania2.setFillColor(sf::Color::Black);


	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	sf::RectangleShape wczytaj_save_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
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
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/Instruction_photo.png");
	auto Instrukcja_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(Instrukcja_background);
	Window->display();
}
void render_api::tworcy(sf::RenderWindow* Window) {
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/About_photo.png");
	auto Tworcy_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(Tworcy_background);
	Window->display();
}
void render_api::draw_empty_background(sf::RenderWindow* Window)
{
	sf::Texture* t = new sf::Texture();
	t->loadFromFile("Texture/game_background.png");
	auto background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *t);
	Window->clear();
	Window->draw(background);
	Window->display();
}
void render_api::wypisz_plansze(Plansza plansza) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (plansza.pola_planszy[j][i]->symbol == ' ') std::cout << '-';
			else std::cout << plansza.pola_planszy[j][i]->symbol;
		} std::cout << "\n";
	}
	std::cout << "\n";
}
void render_api::clear_screen(sf::RenderWindow* Window) {
	Window->clear();
}