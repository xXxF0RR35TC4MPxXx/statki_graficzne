#ifndef BAZOWA_H
#define BAZOWA_H
#include <SFML/Graphics.hpp>
#include "render_api.h"
#include "Plansza.h"
#include <string>

using std::string;

class rozgrywka
{
protected:
	//zmienne potrzebne do gry
	unsigned int tryb_gry;
	char nick1[21];
	char nick2[21];
	Plansza plansza1_1;
	Plansza plansza1_2;
	Plansza plansza2_1;
	Plansza plansza2_2;

	unsigned int oddane_strzaly_1;
	unsigned int oddane_strzaly_2;
	unsigned int trafienia_1;
	unsigned int trafienia_2 ;
public:
	rozgrywka();//konstruktor
	virtual void ustawienia(sf::RenderWindow* Window, render_api* renderer)=0;//funkcja polimorficzna do ustawienia rzeczy przed rozpoczeciem strzelania (nick i statki)
	virtual int przebieg_jednej_tury(sf::RenderWindow* Window, render_api* renderer) = 0;//funkcja polimorficzna ktora "przeprowadza" gre
	void zapisywanie(sf::RenderWindow* Window, render_api* renderer);//funkcja do zapisania postepu gry do pliku
	int wczytywanie(FILE* plik, sf::RenderWindow* Window, render_api* renderer);//funkcja do odczytania postepu gry z pliku
	bool operacja_zapisu_danych_do_pliku(string nazwa_pliku_od_usera);
protected:
	int czy_wygrana(Plansza plansza);//funkcja sprawdza czy ktos juz nie zatopil wszystkich statkow
	void wygrana(sf::RenderWindow* ,char nick[], render_api* renderer);//funkcja wyswietla statystyki jezeli ktos wygral i konczy gre(wraca do menu)
};
#endif