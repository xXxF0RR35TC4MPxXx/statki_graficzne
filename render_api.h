#ifndef RENDER_API_H
#define RENDER_API_H
#include "wybor_typu_gry.h"
#include "zapis_save_yes_no.h"
#include "mainmenu.h"
#include "render_handler.h"
#include "Plansza.h"
#pragma once
class render_api {
protected:
	render_api();
	static render_api* singleton;

public:

	render_api(render_api& other) = delete;
	void operator=(const render_api&) = delete;
	static render_api* GetInstance();
	//MENU, ustawienia gry i w�a�ciwa rozgrywka

	void rysujMenu(sf::RenderWindow* Window, mainmenu mainMenu);		//narysowanie menu g��wnego na ekran
	void wybor_typ_gry(sf::RenderWindow*, wybor_typu_gry);				//wypisanie opcji wyboru typu gry
	std::string podaj_nick(sf::RenderWindow* Window);					//wypisanie ekranu wczytania nicku od gracza i pobranie tego nicku
	void ustawiasz_statek(int, int, sf::RenderWindow*, int);	//wypisanie informacji o typie i numerze stawianego statku
	void render_planszy_przy_ustawianiu(Plansza plansza1, Plansza plansza2, sf::RenderWindow*); //funkcja rysuj�ca plansze podczas ustawiania statk�w i wczytuje pozycje od gracza
	//funkcja rysuj�ca plansze graczy podczas oddawania strza��w i zliczanie statystyk
    void render_planszy_gra(Plansza plansza1, Plansza plansza2, Plansza plansza2_1, Plansza plansza2_2, sf::RenderWindow*, int typ, unsigned int& oddane_strzaly_1, unsigned int& oddane_strzaly_2, unsigned int& trafienia_1, unsigned int& trafienia_2);
    void przekaz_komputer(sf::RenderWindow*);							//wy�wietlanie ekranu z pro�b� o przekazanie komputera drugiemu graczowi
    void komputer_ustawia_statki(sf::RenderWindow* Window);				//wy�wietlanie ekranu z info o ustawianiu statk�w przez komputer
    void ruch_wykonuje_komputer(sf::RenderWindow*);						//wy�wietlanie ekranu z info o wykonywaniu ruchu przez komputer
    int czy_wygrana(Plansza plansza);								//funkcja sprawdza czy ktos juz nie zatopil wszystkich statkow
    void drukuj_statystyki(sf::RenderWindow* Window, char*, char*, char*, int, int, int, int); //wypisywanie ekranu ze statystykami




	//pytanie o zapis i info o pomy�lnym zapisie

     void czy_zapisac_gre(sf::RenderWindow*, zapis_save_yes_no);			//wy�wietlanie ekranu z pytaniem o ch�� zapisu i pobranie odpowiedzi od gracza
     void zapisano_pomyslnie(sf::RenderWindow*);							//ekran z info o poprawnym zapisaniu pliku



	//ekrany odczytu pliku zapisu, info o uszkodzeniu pliku, b��dzie lub kto zaczyna

	void wczytaj_save_background_method(sf::RenderWindow*, sf::Text);	//wy�wietlenie t�a podczas wczytywania pliku zapisu
	void plik_uszkodzony(sf::RenderWindow*);							//wy�wietlenie ekranu z info o uszkodzonym pliku zapisu
	void blad_odczytu_save(sf::RenderWindow* Window, sf::Text text);	//ekran b��du odczytu pliku z zapisem
	void zaczyna(sf::RenderWindow*, char*);								//ekran z info o tym kto zaczyna wznowion� gr�
	
	
	//pozosta�e ekrany, rysowanie samego t�a, wypisywanie planszy w konsoli (debug) i czyszczenie ekranu
	
	void instrukcja(sf::RenderWindow*);									//wy�wietlenie ekranu z instrukcj�
	void tworcy(sf::RenderWindow*);										//wy�wietlenie ekranu z list� tw�rc�w
	void draw_empty_background(sf::RenderWindow* Window);				//wy�wietlenie pustego t�a (bez napis�w)
	void wypisz_plansze(Plansza plansza);							//wypisywanie wskazanej planszy do konsoli (do debugowania)
	void clear_screen(sf::RenderWindow*);								//czyszczenie ekranu
	
	//zmienne potrzebne do zliczania statystyk
	unsigned int temp_hit1 = 0, temp_hit2 = 0, temp_shot1 = 0, temp_shot2 = 0;
};
#endif