#pragma once
#include "Pojedyńcze_pole.h"
class Plansza
{
public:
	Plansza() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				pola_planszy[i][j] = new pojedyńcze_pole(i, j, ' ');
			}
		}
	}

	pojedyńcze_pole* pola_planszy[10][10];
};