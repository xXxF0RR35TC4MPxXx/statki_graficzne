#include "wybor_typu_gry.h"
#include "zapis_save_yes_no.h"
#include "odczyt_save.h"
#include "mainmenu.h"
#pragma once
class render_api {
public:
	render_api(); //konstruktor domyœlny



	//MENU, ustawienia gry i w³aœciwa rozgrywka

	virtual void main_menu(sf::RenderWindow* Window, mainmenu mainMenu);		//narysowanie menu g³ównego na ekran
	virtual void wybor_typ_gry(sf::RenderWindow*, wybor_typu_gry);				//wypisanie opcji wyboru typu gry
	virtual std::string podaj_nick(sf::RenderWindow* Window);					//wypisanie ekranu wczytania nicku od gracza i pobranie tego nicku
	virtual void ustawiasz_statek(int, int, sf::RenderWindow*, int, sf::Text);	//wypisanie informacji o typie i numerze stawianego statku
	virtual int czy_moze_tu_stac(unsigned int wspolrzedna_x, unsigned int wspolrzedna_y, char plansza[10][10]);//funkcja sprawdza czy na podanych koordynatach moze stac statek
	virtual void render_planszy_przy_ustawianiu(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow*); //funkcja rysuj¹ca plansze podczas ustawiania statków i wczytuje pozycje od gracza
	//funkcja rysuj¹ca plansze graczy podczas oddawania strza³ów i zliczanie statystyk
	virtual void render_planszy_gra(char plansza1[10][10], char plansza2[10][10], char plansza2_1[10][10], char plansza2_2[10][10], sf::RenderWindow*, int typ, unsigned int& oddane_strzaly_1, unsigned int& oddane_strzaly_2, unsigned int& trafienia_1, unsigned int& trafienia_2);
	virtual void przeka¿_komputer(sf::RenderWindow*);							//wyœwietlanie ekranu z proœb¹ o przekazanie komputera drugiemu graczowi
	virtual void komputer_ustawia_statki(sf::RenderWindow* Window);				//wyœwietlanie ekranu z info o ustawianiu statków przez komputer
	virtual void ruch_wykonuje_komputer(sf::RenderWindow*);						//wyœwietlanie ekranu z info o wykonywaniu ruchu przez komputer
	virtual int czy_wygrana(char plansza[10][10]);								//funkcja sprawdza czy ktos juz nie zatopil wszystkich statkow
	virtual void drukuj_statystyki(sf::RenderWindow* Window, char*, char*, char*, int, int, int, int); //wypisywanie ekranu ze statystykami




	//pytanie o zapis i info o pomyœlnym zapisie

	virtual void czy_zapisac_gre(sf::RenderWindow*, zapis_save_yes_no);			//wyœwietlanie ekranu z pytaniem o chêæ zapisu i pobranie odpowiedzi od gracza
	virtual void zapisano_pomyœlnie(sf::RenderWindow*);							//ekran z info o poprawnym zapisaniu pliku



	//ekrany odczytu pliku zapisu, info o uszkodzeniu pliku, b³êdzie lub kto zaczyna

	virtual void wczytaj_save_background_method(sf::RenderWindow*, sf::Text);	//wyœwietlenie t³a podczas wczytywania pliku zapisu
	virtual void plik_uszkodzony(sf::RenderWindow*);							//wyœwietlenie ekranu z info o uszkodzonym pliku zapisu
	virtual void b³¹d_odczytu_save(sf::RenderWindow* Window, sf::Text text);	//ekran b³êdu odczytu pliku z zapisem
	virtual void zaczyna(sf::RenderWindow*, char*);								//ekran z info o tym kto zaczyna wznowion¹ grê
	
	
	//pozosta³e ekrany, rysowanie samego t³a, wypisywanie planszy w konsoli (debug) i czyszczenie ekranu
	
	virtual void instrukcja(sf::RenderWindow*);									//wyœwietlenie ekranu z instrukcj¹
	virtual void twórcy(sf::RenderWindow*);										//wyœwietlenie ekranu z list¹ twórców
	virtual void draw_empty_background(sf::RenderWindow* Window);				//wyœwietlenie pustego t³a (bez napisów)
	virtual void wypisz_plansze(char plansza[10][10]);							//wypisywanie wskazanej planszy do konsoli (do debugowania)
	virtual void clear_screen(sf::RenderWindow*);								//czyszczenie ekranu
	
	//zmienne potrzebne do zliczania statystyk
	unsigned int temp_hit1 = 0, temp_hit2 = 0, temp_shot1 = 0, temp_shot2 = 0;

};
