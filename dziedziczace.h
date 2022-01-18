
#include "bazowa.h"
#include "KontekstStrategiiBota.h"
class gra_z_graczem : public rozgrywka
{
public:
	gra_z_graczem();//konstruktor
protected:
	int gra(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs gracz)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs gracz)
};

class gra_z_botem : public rozgrywka
{
public:
	gra_z_botem();//konstruktor
protected:
	int gra(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs komputer)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs komputer)
	OstatnioTrafionePole* strzal_bot(char plansza1[10][10], char plansza2[10][10], int, int);//funkcja w ktorej komputer losuje wspolrzedna gdzie strzelic
	void ustawienie_statkow_bot(char plansza1[10][10], char plansza2[10][10]);//funkcja w ktorej komputer losuje gdzie postawic statki
	KontekstStrategiiBota* kontekst_strategii_bota;
	int ostatnio_trafiony_x = -1;
	int ostatnio_trafiony_y = -1;
};