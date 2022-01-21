#ifndef DZIEDZICZACE_H
#define DZIEDZICZACE_H
#include "bazowa.h"
#include "StrategiaStrzaluBota.h"
#include "render_api.h"
class gra_z_graczem : public rozgrywka
{
public:
	gra_z_graczem();//konstruktor
protected:
	int przebieg_jednej_tury(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs gracz)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs gracz)
	void przekaz_komputer(RenderWindow*, render_api*);
};

class gra_z_botem : public rozgrywka
{
public:
	gra_z_botem();//konstruktor
	int ostatnio_trafiony_x = -1;
	int ostatnio_trafiony_y = -1;
	IStrategiaStrzaluBota* obecna_strategia;

	void KontekstStrategiiBota(IStrategiaStrzaluBota* const s) { obecna_strategia = s; };


	void zmien_strategie(IStrategiaStrzaluBota* nowa_strategia) {
		std::cout << "Zmiana strategii!";
		//delete this->obecna_strategia;
		this->obecna_strategia = nowa_strategia;
	}

	
protected:
	int przebieg_jednej_tury(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs komputer)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs komputer)
	OstatnioTrafionePole* strzal_bot(Plansza plansza1, Plansza plansza2, int, int);//funkcja w ktorej komputer wybiera wspolrzedna gdzie strzelic
	void ustawienie_statkow_bot(Plansza plansza1, Plansza plansza2);//funkcja w ktorej komputer losuje gdzie postawic statki

	void ustawienie_statkow_jednomasztowych(render_api*, Plansza plansza1);
	void ustawienie_statkow_dwumasztowych(render_api*, Plansza plansza1);
	void ustawienie_statkow_trojmasztowych(render_api*, Plansza plansza1);
	void ustawienie_statkow_czteromasztowych(render_api*, Plansza plansza1);
};
#endif