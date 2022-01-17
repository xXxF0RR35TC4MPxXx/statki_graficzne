#include "wybor_typu_gry.h"
#include "zapis_save_yes_no.h"
#include "odczyt_save.h"
#include "mainmenu.h"
#pragma once
class render_api {
public:
	render_api(); //konstruktor domy�lny



	//MENU, ustawienia gry i w�a�ciwa rozgrywka

	virtual void main_menu(sf::RenderWindow* Window, mainmenu mainMenu);		//narysowanie menu g��wnego na ekran
	virtual void wybor_typ_gry(sf::RenderWindow*, wybor_typu_gry);				//wypisanie opcji wyboru typu gry
	virtual std::string podaj_nick(sf::RenderWindow* Window);					//wypisanie ekranu wczytania nicku od gracza i pobranie tego nicku
	virtual void ustawiasz_statek(int, int, sf::RenderWindow*, int, sf::Text);	//wypisanie informacji o typie i numerze stawianego statku
	virtual int czy_moze_tu_stac(unsigned int wspolrzedna_x, unsigned int wspolrzedna_y, char plansza[10][10]);//funkcja sprawdza czy na podanych koordynatach moze stac statek
	virtual void render_planszy_przy_ustawianiu(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow*); //funkcja rysuj�ca plansze podczas ustawiania statk�w i wczytuje pozycje od gracza
	//funkcja rysuj�ca plansze graczy podczas oddawania strza��w i zliczanie statystyk
	virtual void render_planszy_gra(char plansza1[10][10], char plansza2[10][10], char plansza2_1[10][10], char plansza2_2[10][10], sf::RenderWindow*, int typ, unsigned int& oddane_strzaly_1, unsigned int& oddane_strzaly_2, unsigned int& trafienia_1, unsigned int& trafienia_2);
	virtual void przeka�_komputer(sf::RenderWindow*);							//wy�wietlanie ekranu z pro�b� o przekazanie komputera drugiemu graczowi
	virtual void komputer_ustawia_statki(sf::RenderWindow* Window);				//wy�wietlanie ekranu z info o ustawianiu statk�w przez komputer
	virtual void ruch_wykonuje_komputer(sf::RenderWindow*);						//wy�wietlanie ekranu z info o wykonywaniu ruchu przez komputer
	virtual int czy_wygrana(char plansza[10][10]);								//funkcja sprawdza czy ktos juz nie zatopil wszystkich statkow
	virtual void drukuj_statystyki(sf::RenderWindow* Window, char*, char*, char*, int, int, int, int); //wypisywanie ekranu ze statystykami




	//pytanie o zapis i info o pomy�lnym zapisie

	virtual void czy_zapisac_gre(sf::RenderWindow*, zapis_save_yes_no);			//wy�wietlanie ekranu z pytaniem o ch�� zapisu i pobranie odpowiedzi od gracza
	virtual void zapisano_pomy�lnie(sf::RenderWindow*);							//ekran z info o poprawnym zapisaniu pliku



	//ekrany odczytu pliku zapisu, info o uszkodzeniu pliku, b��dzie lub kto zaczyna

	virtual void wczytaj_save_background_method(sf::RenderWindow*, sf::Text);	//wy�wietlenie t�a podczas wczytywania pliku zapisu
	virtual void plik_uszkodzony(sf::RenderWindow*);							//wy�wietlenie ekranu z info o uszkodzonym pliku zapisu
	virtual void b��d_odczytu_save(sf::RenderWindow* Window, sf::Text text);	//ekran b��du odczytu pliku z zapisem
	virtual void zaczyna(sf::RenderWindow*, char*);								//ekran z info o tym kto zaczyna wznowion� gr�
	
	
	//pozosta�e ekrany, rysowanie samego t�a, wypisywanie planszy w konsoli (debug) i czyszczenie ekranu
	
	virtual void instrukcja(sf::RenderWindow*);									//wy�wietlenie ekranu z instrukcj�
	virtual void tw�rcy(sf::RenderWindow*);										//wy�wietlenie ekranu z list� tw�rc�w
	virtual void draw_empty_background(sf::RenderWindow* Window);				//wy�wietlenie pustego t�a (bez napis�w)
	virtual void wypisz_plansze(char plansza[10][10]);							//wypisywanie wskazanej planszy do konsoli (do debugowania)
	virtual void clear_screen(sf::RenderWindow*);								//czyszczenie ekranu
	
	//zmienne potrzebne do zliczania statystyk
	unsigned int temp_hit1 = 0, temp_hit2 = 0, temp_shot1 = 0, temp_shot2 = 0;

};
