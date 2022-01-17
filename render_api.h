#include "wybor_typu_gry.h"
#include "zapis_save_yes_no.h"
#include "odczyt_save.h"
#include "mainmenu.h"
#pragma once
class render_api {
public:
	render_api(); //konstruktor domyœlny
	virtual void main_menu(sf::RenderWindow* Window, mainmenu mainMenu);		//narysowanie menu g³ównego na ekran
	virtual void wybor_typ_gry(sf::RenderWindow*, wybor_typu_gry);				//wypisanie opcji wyboru typu gry
	virtual std::string podaj_nick(sf::RenderWindow* Window);					//wypisanie ekranu wczytania nicku od gracza i pobranie tego nicku

	virtual void ustawiasz_statek(int, int, sf::RenderWindow*, int, sf::Text);	//wypisanie informacji o typie i numerze stawianego statku
	virtual int czy_moze_tu_stac(unsigned int wspolrzedna_x, unsigned int wspolrzedna_y, char plansza[10][10]);//funkcja sprawdza czy na podanych koordynatach moze stac statek
	virtual void render_planszy_przy_ustawianiu(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow*); //funkcja rysuj¹ca plansze podczas ustawiania statków i wczytuje pozycje od gracza
	
	virtual void render_planszy_gra(char plansza1[10][10], char plansza2[10][10], char plansza2_1[10][10], char plansza2_2[10][10], sf::RenderWindow*, int typ, unsigned int& oddane_strzaly_1, unsigned int& oddane_strzaly_2, unsigned int& trafienia_1, unsigned int& trafienia_2);


	virtual void wczytaj_save_background_method(sf::RenderWindow*, sf::Text);
	virtual void plik_uszkodzony(sf::RenderWindow*);

	virtual void instrukcja(sf::RenderWindow*);
	virtual void twórcy(sf::RenderWindow*);
	virtual void draw_empty_background(sf::RenderWindow* Window);
	
	virtual void czy_zapisac_gre(sf::RenderWindow*, zapis_save_yes_no);
	
	
	virtual void przeka¿_komputer(sf::RenderWindow*);
	
	virtual void komputer_ustawia_statki(sf::RenderWindow* Window);
	virtual void ruch_wykonuje_komputer(sf::RenderWindow*);
	virtual void clear_screen(sf::RenderWindow*);
	virtual void wypisz_plansze(char plansza[10][10]);
	virtual int czy_wygrana(char plansza[10][10]);//funkcja sprawdza czy ktos juz nie zatopil wszystkich statkow

	virtual void drukuj_statystyki(sf::RenderWindow* Window, char*, char*, char*, int, int, int, int);
	virtual void nie_uda³o_siê(sf::RenderWindow* Window, sf::Text text);
	virtual void zapisano_pomyœlnie(sf::RenderWindow*);
	
	virtual void zaczyna(sf::RenderWindow*, char*);
	unsigned int temp_hit1=0, temp_hit2=0, temp_shot1=0, temp_shot2=0;
};
