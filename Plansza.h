#pragma once
#include "Pojedy�cze_pole.h"
class Plansza
{
public:
	Plansza() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				pola_planszy[i][j] = new pojedy�cze_pole(i, j, ' ');
			}
		}
	}

	pojedy�cze_pole* pola_planszy[10][10];
};