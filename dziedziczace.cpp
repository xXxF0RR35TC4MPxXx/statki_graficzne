#pragma warning( disable : 6386 )
#pragma warning(disable:4996)
#include "dziedziczace.h"
#include <string>
#include <Windows.h>
#include "render_api.h"
#include <iostream>
#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822
gracz::gracz() :rozgrywka()//konstruktor
{
	tryb_gry = 2;
}
void przerw(int x)
{
	for (int i = 0; i < x; i++)
		printf(" ");
}
int gracz::gra(sf::RenderWindow* Window, render_api* renderer)//funkcja do przeprowadzenia tury gry(gracz vs gracz)
{
	int czy_trafione = 0;
	int jezeli_wygrana = 0;
	while (1)
	{
		bool wyjsc_z_okna = false;
		
		sf::Event przekazkomputerevent;
		bool wyszedl_z_okna = false;
		jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			printf("PRZED1: WYGRAL: %s \n", nick1);
			wygrana(Window, nick1);//wyswietlenie statystyk
			return 1;
		}
		
		std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";

		renderer->render_planszy_gra(plansza1_1, plansza1_2, plansza2_1, plansza2_2, Window, 1, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
		//oddane_strzaly_1 += renderer->temp_shot1;
		//trafienia_1 += renderer->temp_hit1;
		std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		while (Window->isOpen() && !wyjsc_z_okna) {
			sf::sleep(sf::milliseconds(1000));
			wyjsc_z_okna = true;
			break;
		}
		
		jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			printf("PO1: WYGRAL: %s \n", nick1);
			if (trafienia_1 != 0 && trafienia_2 != 0)wygrana(Window, nick1);//wyswietlenie statystyk
			return 1;
		}wyjsc_z_okna = false;
		//opóŸnienie, ¿eby wyœwietliæ komunikat o pudle
		
		sf::RectangleShape przekaz_background;
		przekaz_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		sf::Texture przekaz_background_texture;
		przekaz_background_texture.loadFromFile("Texture/game_background.png");
		przekaz_background.setTexture(&przekaz_background_texture);
		sf::Font retrofont;
		retrofont.loadFromFile("retrofont.ttf");

		//tekst "Twoje pole:"
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
		wyszedl_z_okna = false;
		while (Window->isOpen() && !wyszedl_z_okna) {
			while (Window->pollEvent(przekazkomputerevent)) {
				if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {

				}
				//std::cout << "MA PRZEKAZAC KOMPUTER";
				Window->draw(przekaz_background);
				Window->draw(przekaz_text);
				Window->draw(enter_text);
				Window->display();
				if (przekazkomputerevent.type == sf::Event::KeyPressed) {
					if (przekazkomputerevent.key.code == sf::Keyboard::Return)
					{
						//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
						wyszedl_z_okna = true;
						Window->clear();
						break;
					}
				}
			}
		}
		
		wyszedl_z_okna = false;
		jezeli_wygrana = czy_wygrana(plansza1_1);//sprawdzanie czy gracz zatopil juz wszystkie statki
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			//printf("PRZED2: WYGRAL: %s \n", nick2);
			if(trafienia_1 !=0 && trafienia_2 !=0) wygrana(Window, nick2);//wyswietlenie statystyk
			return 1;
		}
		std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";

		renderer->render_planszy_gra(plansza2_1, plansza2_2, plansza1_1, plansza1_2, Window, 2, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
		//oddane_strzaly_1 += renderer->temp_shot1;
		//trafienia_1 += renderer->temp_hit1;
		std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		while (Window->isOpen() && !wyjsc_z_okna) {
			sf::sleep(sf::milliseconds(1000));
			wyjsc_z_okna = true;
			break;
		}
		jezeli_wygrana = czy_wygrana(plansza1_1);//sprawdzanie czy gracz zatopil juz wszytskie statki
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			//printf("PO2: WYGRAL: %s \n", nick2);
			if (trafienia_1 != 0 && trafienia_2 != 0) wygrana(Window, nick2);//wyswietlenie statystyk
			return 1;
		}
		while (Window->isOpen() && !wyszedl_z_okna) {
			while (Window->pollEvent(przekazkomputerevent)) {
				if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {

				}
				//std::cout << "MA PRZEKAZAC KOMPUTER";
				Window->draw(przekaz_background);
				Window->draw(przekaz_text);
				Window->draw(enter_text);
				Window->display();
				if (przekazkomputerevent.type == sf::Event::KeyPressed) {
					if (przekazkomputerevent.key.code == sf::Keyboard::Return)
					{
						wyszedl_z_okna = true;
						//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
						Window->clear();
						break;
					}
				}
			}
		}
		return 0;//koniec tury
	}
}

void gracz::ustawienia(sf::RenderWindow* Window)//gracze ustawiaja nicki oraz statki
{
	sf::RectangleShape przekaz_background;
	przekaz_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture przekaz_background_texture;
	przekaz_background_texture.loadFromFile("Texture/game_background.png");
	przekaz_background.setTexture(&przekaz_background_texture);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	//tekst "Twoje pole:"
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
	sf::Event przekazkomputerevent;
	bool wyszedl_z_okna = false;

	printf("USTAWIENIA GRY Z GRACZEM\n");
	render_api* renderer = new render_api();
	strcpy_s(nick1, renderer->podaj_nick(Window).c_str());
	ustawienie_statkow(plansza1_1, plansza1_2, Window);//funkcja w ktorej gracz ustawia wszystkie swoje statki
	std::cout << "dziedziczace -> gracz::ustawienia -> po ustawieniu statkow\n";
	while (Window->isOpen() && !wyszedl_z_okna) {
		while (Window->pollEvent(przekazkomputerevent)) {
			if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {

			}
			std::cout << "MA PRZEKAZAC KOMPUTER";
			Window->draw(przekaz_background);
			Window->draw(przekaz_text);
			Window->draw(enter_text);
			Window->display();
			if (przekazkomputerevent.type == sf::Event::KeyPressed) {
				if (przekazkomputerevent.key.code == sf::Keyboard::Return)
				{
					wyszedl_z_okna = true;
					Window->clear();
					break;
				}
			}
		}
	}wyszedl_z_okna = false;
	strcpy_s(nick2, renderer->podaj_nick(Window).c_str());
	ustawienie_statkow(plansza2_1, plansza2_2, Window);//funkcja w ktorej gracz ustawia wszystkie swoje statki
	
	while (Window->isOpen() && !wyszedl_z_okna) {
		while (Window->pollEvent(przekazkomputerevent)) {
			if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {

			}
			std::cout << "MA PRZEKAZAC KOMPUTER";
			Window->draw(przekaz_background);
			Window->draw(przekaz_text);
			Window->draw(enter_text);
			Window->display();
			if (przekazkomputerevent.type == sf::Event::KeyPressed) {
				if (przekazkomputerevent.key.code == sf::Keyboard::Return)
				{
					wyszedl_z_okna = true;
					Window->clear();
					break;
				}
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bot::bot() :rozgrywka() //konstruktor
{
	tryb_gry = 1;
}

void bot::ustawienia(sf::RenderWindow* Window)//gracz oraz komputer uswtaiaja nicki oraz statki
{
	printf("USTAWIENIA GRY Z BOTEM\n");
	render_api* renderer = new render_api();
	strcpy_s(nick1, renderer->podaj_nick(Window).c_str());
	int size = strlen(nick1);
	std::string myString(nick1, size);
	std::cout << "Nick gracza 1 w ustawieniach: " + myString + "\n";

	//ZROBIÆ USTAWIENIE STATKÓW!
	ustawienie_statkow(plansza1_1, plansza1_2, Window);//funkcja gdzie gracz ustawia statki
	std::cout << "dziedziczace -> bot::ustawienia -> po ustawieniu statkow\n";
	sf::RectangleShape ustawienie_statkow_bota_background;
	ustawienie_statkow_bota_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture ustawienie_statkow_bota_texture;
	ustawienie_statkow_bota_texture.loadFromFile("Texture/game_background.png");
	ustawienie_statkow_bota_background.setTexture(&ustawienie_statkow_bota_texture);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	//tekst "Twoje pole:"
	sf::Text ustawienie_statkow_bota_text;
	ustawienie_statkow_bota_text.setFillColor(sf::Color::Black);
	ustawienie_statkow_bota_text.setFont(retrofont);
	ustawienie_statkow_bota_text.setCharacterSize(24);
	ustawienie_statkow_bota_text.setPosition(sf::Vector2f(134, 300));
	ustawienie_statkow_bota_text.setString("Komputer ustawia statki");

	sf::Event ruch_komputera_event;
	bool wyjsc_z_okna = false;
	while (Window->isOpen() && !wyjsc_z_okna) {
		while (Window->pollEvent(ruch_komputera_event)) {
			if (ruch_komputera_event.type == sf::Event::MouseButtonPressed) {

			}
			//std::cout << "MA PRZEKAZAC KOMPUTER";
			Window->draw(ustawienie_statkow_bota_background);
			Window->draw(ustawienie_statkow_bota_text);
			Window->display();
			//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
			sf::sleep(sf::milliseconds(1000));
			wyjsc_z_okna = true;
			Window->clear();
			break;
		}
	}
	strcpy_s(nick2, "Komputer");//ustawienie drugiego nicku jako 'Komputer'
	ustawienie_statkow_bot(plansza2_1, plansza2_2);//funkcja gdzie komputer 'ustawia' statki

	std::cout << "dziedziczace -> bot::ustawienia -> po ustawieniu statkow BOTA\n";
	renderer->komputer_ustawia_statki(Window);
	
	std::cout << "Tutaj powinno wyjsc z ustawien\n";
}

template <class T>
int bot::strzal_bot(T plansza1[10][10], T plansza2[10][10])//funkcja gdzie komputer losuje w ktore pole strzelic
{
	
	unsigned int wspolrzedna_x, wspolrzedna_y;
	wspolrzedna_x = (rand() % 10) + 1;//losowanie wspolrzednej X 1-10
	wspolrzedna_y = (rand() % 10) + 1;//losowanie wspolrzednej Y 1-10
	//sprawdzanie gdzie trafily wylosowane wspolrzedne
	std::cout << "Strzal bota: X="+ std::to_string(wspolrzedna_x) + ", Y="+ std::to_string(wspolrzedna_y)+  "\n";
	if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == ' ')//jezeli trafienie w puste pole
	{
		std::cout << "Bot trafil w puste\n";
		//ustawienie oznaczen strzalu na odpowiednich planszach i zwrocenie oznaczenia nietrafienia
		plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '.';
		plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = '.';
		return 0;
	}
	else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == 'x' || plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '.')//jezeli trafienie w pole gdzie juz strzelano
	{
		std::cout << "Bot trafil w x\n";
		return 2;//wrocenie oznaczenia nietrafienia
	}
	else//jezeli trafiono
	{
		std::cout << "Bot trafil w statek\n";
		//ustawienie odpowiedniego oznaczenia(zaleznego od tego w jaki statek trafiono) na odpowiedniej planszy
		if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '1')
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = 'x';
		}
		else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '2')
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = 'x';
		}
		else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '3')
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = 'x';
		}
		else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '4')
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = 'x';
		}
		plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = 'x';//ustawienie oznaczenia ze wrog trafil na planszy przeciwnika
		return 1;//zwrocenie oznaczenia trafienia
	}
}

int bot::gra(sf::RenderWindow* Window, render_api* renderer)//funkcja do przeprowadzenia tury gry(gracz vs komputer)
{
	int czy_trafione = 0;
	int jezeli_wygrana = 0;
	while (1)
	{

			sf::Event ruch_komputera_event;
			jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral

			if (jezeli_wygrana == 1)//jezeli wygral
			{
				//printf("WYGRAL: %s \n", nick1);
				if (trafienia_1 != 0 || trafienia_2 != 0)wygrana(Window, nick1);//wyswietlenie statystyk
				return 1;
			}
			std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";

			renderer->render_planszy_gra(plansza1_1, plansza1_2, plansza2_1, plansza2_2, Window, 3, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
			//oddane_strzaly_1 += renderer->temp_shot1;
			//trafienia_1 += renderer->temp_hit1;
			std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
			bool wyjsc_z_okna = false;
			jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
			if (jezeli_wygrana == 1)//jezeli wygral
			{
				//printf("WYGRAL: %s \n", nick1);
				if (trafienia_1 != 0 || trafienia_2 != 0) wygrana(Window, nick1);//wyswietlenie statystyk
				return 1;
			}
			//opóŸnienie, ¿eby wyœwietliæ komunikat o pudle
			while (Window->isOpen() && !wyjsc_z_okna) {
				sf::sleep(sf::milliseconds(1000));
				wyjsc_z_okna = true;
				break;
			}

			sf::RectangleShape ruch_komputera_background;
			ruch_komputera_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
			sf::Texture ruch_komputera_texture;
			ruch_komputera_texture.loadFromFile("Texture/game_background.png");
			ruch_komputera_background.setTexture(&ruch_komputera_texture);
			sf::Font retrofont;
			retrofont.loadFromFile("retrofont.ttf");

			//tekst "Twoje pole:"
			sf::Text ruch_komputera_text;
			ruch_komputera_text.setFillColor(sf::Color::Black);
			ruch_komputera_text.setFont(retrofont);
			ruch_komputera_text.setCharacterSize(24);
			ruch_komputera_text.setPosition(sf::Vector2f(154, 300));
			ruch_komputera_text.setString("Ruch wykonuje komputer");
			
			wyjsc_z_okna = false;
			while (Window->isOpen() && !wyjsc_z_okna) {
				while (Window->pollEvent(ruch_komputera_event)) {
					if (ruch_komputera_event.type == sf::Event::MouseButtonPressed) {

					}
					//std::cout << "MA PRZEKAZAC KOMPUTER";
					Window->draw(ruch_komputera_background);
					Window->draw(ruch_komputera_text);
					Window->display();
					//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
					sf::sleep(sf::milliseconds(1000));
					wyjsc_z_okna = true;
					Window->clear();
					break;
				}
			}


		do
		{
			czy_trafione = strzal_bot(plansza1_1, plansza2_2);//wywolanie funkcji w ktorej komputer losuje gdzie strzelic i sprawdzenie gdzie trafil
			printf("Czy bot trafil: %d\n", czy_trafione);
			oddane_strzaly_2++;//doliczenie do statystyk oddane strzaly
			//sprawdzanie czy trafil
			if (czy_trafione == 1)
			{
				trafienia_2++;//doliczenie do statystyk trafione strzaly
			}
			jezeli_wygrana = czy_wygrana(plansza1_1);//sprawdzenie czy komputer wygral
			if (jezeli_wygrana == 1)//jezeli wygral
			{
				//printf("WYGRAL: %s \n", nick2);
				if (trafienia_1 != 0 && trafienia_2 != 0) wygrana(Window, nick2);//wyswietlenie statystyk
				return 1;
			}
		} while (czy_trafione == 1 || czy_trafione == 2);//strzela do poki trafia lub trafil w to w co juz strzelal(bot nie marnuje strzalow na stzrelanie w cos co juz strzelal)
		return 0;//koniec tury
	}
}

template<class T>
void bot::ustawienie_statkow_bot(T plansza1[10][10], T plansza2[10][10])//funkcja w ktorej komputer losuje gdzie postawic statki
{
	render_api* renderer = new render_api();
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja;
	int odpowiedz = 0;
	for (int i = 0; i < 4; i++)//ustawianie statkow jednomasztowych
	{
		do
		{
			//komputer losuje 2 liczby z przedzialu 1-10
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);//sprawdzanie czy w wylosowanej pozycji moze stac statek
		} while (odpowiedz != 1);//losuje do poki nie wylosuje dobrej pozycji
		plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '1';//wpisanie statku do tablicy w odpowiednie miejsce
	}
	for (int i = 0; i < 3; i++)//ustawianie statkow dwumasztowych
	{
		while (1)
		{
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 1, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;

			}
			else if (orientacja == 3)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y - 2][wspolrzedna_x - 1] = '2';
		}
		else if (orientacja == 2)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '2';
		}
		else if (orientacja == 3)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 2] = '2';
		}
		else if (orientacja == 4)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '2';
		}
	}
	for (int i = 0; i < 2; i++)//ustawianie statkow trzymasztowych
	{
		while (1)
		{
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 2, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;

			}
			else if (orientacja == 3)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 2, plansza1);
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 2][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 3][wspolrzedna_x - 1] = '3';
		}
		else if (orientacja == 2)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x + 1] = '3';
		}
		else if (orientacja == 3)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 2] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 3] = '3';
		}
		else if (orientacja == 4)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y + 1][wspolrzedna_x - 1] = '3';
		}
	}
	for (int i = 0; i < 1; i++)//ustawianie statkow czteromasztowego
	{
		while (1)
		{
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 2, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 3, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x + 3, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 3)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x - 3, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 2, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 3, plansza1);
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 2][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 3][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 4][wspolrzedna_x - 1] = '4';
		}
		else if (orientacja == 2)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x + 1] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x + 2] = '4';
		}
		else if (orientacja == 3)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 2] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 3] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 4] = '4';
		}
		else if (orientacja == 4)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y + 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y + 2][wspolrzedna_x - 1] = '4';
		}
	}
	std::cout << "WYGENEROWANA PLANSZA BOTA\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if(plansza1[i][j]!=' ')
				std::cout << plansza1[i][j];
			else std::cout << '-';
		}std::cout << "\n";
	}
	std::cout << "\n";
	renderer->clear_screen();
}
