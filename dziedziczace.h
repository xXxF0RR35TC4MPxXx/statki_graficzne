
#include "bazowa.h"
#include "KontekstStrategiiBota.h"
class gra_z_graczem : public rozgrywka
{
public:
	gra_z_graczem();//konstruktor
protected:
	int przebieg_jednej_tury(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs gracz)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs gracz)
	void przeka�_komputer(RenderWindow*, render_api*);
};

class gra_z_botem : public rozgrywka
{
public:
	gra_z_botem();//konstruktor
protected:
	int przebieg_jednej_tury(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs komputer)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs komputer)
	OstatnioTrafionePole* strzal_bot(char plansza1[10][10], char plansza2[10][10], int, int);//funkcja w ktorej komputer wybiera wspolrzedna gdzie strzelic
	void ustawienie_statkow_bot(char plansza1[10][10], char plansza2[10][10]);//funkcja w ktorej komputer losuje gdzie postawic statki

	void ustawienie_statk�w_jednomasztowych(render_api*, char plansza1[10][10]);
	void ustawienie_statk�w_dwumasztowych(render_api*, char plansza1[10][10]);
	void ustawienie_statk�w_tr�jmasztowych(render_api*, char plansza1[10][10]);
	void ustawienie_statk�w_czteromasztowych(render_api*, char plansza1[10][10]);
	
	KontekstStrategiiBota* kontekst_strategii_bota;
	int ostatnio_trafiony_x = -1;
	int ostatnio_trafiony_y = -1;
};