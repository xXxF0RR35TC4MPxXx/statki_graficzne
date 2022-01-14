
#include "bazowa.h"
class gracz : public rozgrywka
{
public:
	gracz();//konstruktor
protected:
	int gra(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs gracz)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs gracz)
};

class bot : public rozgrywka
{
public:
	bot();//konstruktor
protected:
	int gra(sf::RenderWindow*, render_api* renderer);//funkcja ktora "przeprowadza" gre(wersja dla gracz vs komputer)
	void ustawienia(sf::RenderWindow*);//funkcja sluzaca do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)(wersja dla gracz vs komputer)
	template <class T>
	int strzal_bot(T plansza1[10][10], T plansza2[10][10]);//funkcja w ktorej komputer losuje wspolrzedna gdzie strzelic
	template <class T>
	void ustawienie_statkow_bot(T plansza1[10][10], T plansza2[10][10]);//funkcja w ktorej komputer losuje gdzie postawic statki
};