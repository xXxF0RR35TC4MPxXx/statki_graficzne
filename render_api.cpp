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
	bool czy_wyjsc = false;
	sf::Texture* tx = new Texture();
	tx->loadFromFile("Texture/podaj_nick.png");
	RectangleShape podaj_nick_background = *SFMLFactory::createRectangle(WINDOW_WIDTH, WINDOW_HEIGHT, *tx);
	Window->clear();
	Window->draw(podaj_nick_background);
	Window->display();
	while (Window->isOpen()) {
		sf::Event gevent;
		Window->clear();
		Window->draw(podaj_nick_background);
		Result result = RenderHandler::handleNickEvent(Window, &t);
		t.setString(result.nickname);
		Window->draw(t); //tutaj error
		Window->display();
		if(result.exit) return t.getString();
	}
}
void render_api::ustawiasz_statek(int typ, int nr, sf::RenderWindow* Window, int typ_wiadomosci, Font* f) {
	string s;
	int x, y, csize;
	std::tie(s, x, y, csize) = RenderHandler::handleShipPlacement(typ_wiadomosci, typ, nr);

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


	game_screen game_screen(Window->getSize().x, Window->getSize().y, Window);

	RenderHandler::handleBoardSetup(game_background, twojaplanszatekst,
		planszaprzeciwnikatekst, game_screen, plansza1, plansza2, Window);
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

	game_screen game_screen(Window->getSize().x, Window->getSize().y, Window);

	RenderHandler::handleBoardGame(game_background, twojaplanszatekst,
		planszaprzeciwnikatekst, komunikat,
		game_screen, plansza1, plansza2, plansza2_1, plansza2_2,
		Window, typ, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
	
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
	t->loadFromFile("Texture/game_background.png");

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

	auto shots_text = *SFMLFactory::createText("Strzalow:", *f, 18, 460, 240);
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