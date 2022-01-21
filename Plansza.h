#pragma once
#include "Pojedyncze_pole.h"
class Plansza
{
public:
	Plansza() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				pola_planszy[i][j] = new pojedyncze_pole(i, j, ' ');
			}
		}
	}

	int czy_moze_tu_stac(unsigned int wspolrzedna_x, unsigned int wspolrzedna_y) {
		//czy nie wychodzi za tablice																			//wychodzi za plansze
		if (wspolrzedna_x > 10 || wspolrzedna_x < 1 || wspolrzedna_y > 10 || wspolrzedna_y < 1)					//zwraca 0 jezeli nie moze stac na tej pozycji lub 1 jezeli moze
		{
			return 0;
		}
		if (pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol != ' ')
		{
			return 0;
		}
		if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy czegos nie dotyka po lewej)
		{
			if (pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 2]->symbol != ' ')
			{
				return 0;
			}
		}
		else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy czegos nie dotyka po prawej)
		{
			if (pola_planszy[wspolrzedna_y - 1][wspolrzedna_x]->symbol != ' ')
			{
				return 0;
			}
		}
		else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy nie dotyka czegos z obu stron)
		{
			if (pola_planszy[wspolrzedna_y - 1][wspolrzedna_x]->symbol != ' ' || pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 2]->symbol != ' ')
			{
				return 0;
			}
		}
		if (wspolrzedna_y == 10)//jezeli dotyka dolna sciane(sprawdzamy tylko czy czegos nie dotyka u gory)
		{
			if (pola_planszy[wspolrzedna_y - 2][wspolrzedna_x - 1]->symbol != ' ')
			{
				return 0;
			}
		}
		else if (wspolrzedna_y == 1)//jezeli dotyka dolna sciane(sprawdzamy tylko czy czegos nie dotyka u dolu)
		{
			if (pola_planszy[wspolrzedna_y][wspolrzedna_x - 1]->symbol != ' ')
			{
				return 0;
			}
		}
		else//jezeli nie dotyka dotyka zadnej sciany(gornej lub dolnej)(sprawdzamy czy nie dotyka czegos u gory i dolu)
		{
			if (pola_planszy[wspolrzedna_y - 2][wspolrzedna_x - 1]->symbol != ' ' || pola_planszy[wspolrzedna_y][wspolrzedna_x - 1]->symbol != ' ')
			{
				return 0;
			}
		}
		if (wspolrzedna_y > 1)//jezeli nie dotyka gornej sciany
		{
			if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy lewy gorny rog jest wolny)
			{
				if (pola_planszy[wspolrzedna_y - 2][wspolrzedna_x - 2]->symbol != ' ')
				{
					return 0;
				}
			}
			else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy prawy gorny rog jest wolny)
			{
				if (pola_planszy[wspolrzedna_y - 2][wspolrzedna_x]->symbol != ' ')
				{
					return 0;
				}
			}
			else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy gorne rogi sa wolne)
			{
				if (pola_planszy[wspolrzedna_y - 2][wspolrzedna_x - 2]->symbol != ' ' || pola_planszy[wspolrzedna_y - 2][wspolrzedna_x]->symbol != ' ')
				{
					return 0;
				}
			}
		}
		if (wspolrzedna_y < 10)//jezeli nie dotyka dolnej sciany
		{
			if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy lewy dolny rog jest wolny)
			{
				if (pola_planszy[wspolrzedna_y][wspolrzedna_x - 2]->symbol != ' ')
				{
					return 0;
				}
			}
			else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy prawy dolny rog jest wolny)
			{
				if (pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol != ' ')
				{
					return 0;
				}
			}
			else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy dolne rogi sa wolne)
			{
				if (pola_planszy[wspolrzedna_y][wspolrzedna_x - 2]->symbol != ' ' || pola_planszy[wspolrzedna_y][wspolrzedna_x]->symbol != ' ')
				{
					return 0;
				}
			}
		}
		return 1;
	}

	pojedyncze_pole* pola_planszy[10][10];
};