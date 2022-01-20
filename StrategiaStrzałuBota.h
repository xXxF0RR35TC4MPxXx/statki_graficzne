#include "Plansza.h"
#include <iostream>
#include <string>
#include <list>
#pragma once


class OstatnioTrafionePole {
public:
	OstatnioTrafionePole(int y, int x, int wt) {
		this->x = x;
		this->y = y;
		this->wynik_trafienia = wt;
	}
	int x = 0;
	int y = 0;
	int wynik_trafienia = 0;
};

class Pole {
public:
	Pole(int y, int x) {
		this->y = y;
		this->x = x;
	};
	int x = 0;
	int y = 0;

};

class IStrategiaStrza³uBota
{
public:
	virtual ~IStrategiaStrza³uBota() {}
	virtual OstatnioTrafionePole* strza³_bota(Plansza plansza1, Plansza plansza2, int, int)=0;
};

class StrategiaBota_Strza³Losowy :public IStrategiaStrza³uBota
{
public:
	~StrategiaBota_Strza³Losowy() {};
	OstatnioTrafionePole* strza³_bota(Plansza plansza1, Plansza plansza2, int x, int y) {
		cout << "U¿yta strategia: Strza³Losowy\n";
		unsigned int wspolrzedna_x = (rand() % 10) + 1;//losowanie wspolrzednej X 1-10
		unsigned int wspolrzedna_y = (rand() % 10) + 1;//losowanie wspolrzednej Y 1-10

		while (plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol== '.' || plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol == 'x')
		{
			wspolrzedna_x = (rand() % 10) + 1;//losowanie wspolrzednej X 1-10
			wspolrzedna_y = (rand() % 10) + 1;//losowanie wspolrzednej Y 1-10
		}
		//sprawdzanie gdzie trafily wylosowane wspolrzedne
		std::cout << "Strzal bota: X=" + std::to_string(wspolrzedna_y-1) + ", Y=" + std::to_string(wspolrzedna_x-1) + "\n";
		if (plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol == ' ')//jezeli trafienie w puste pole
		{
			std::cout << "Bot trafil w puste\n";
			//ustawienie oznaczen strzalu na odpowiednich planszach i zwrocenie oznaczenia nietrafienia
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = '.';
			plansza2.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = '.';
			OstatnioTrafionePole* ost_traf_pole = new OstatnioTrafionePole(wspolrzedna_y - 1, wspolrzedna_x - 1, 0);
			return ost_traf_pole;

		}
		//jezeli trafienie w pole gdzie juz strzelano
		else if (plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol == 'x' || plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol == '.')
		{
			std::cout << "Bot trafil w x\n";
			//wrocenie oznaczenia nietrafienia
			OstatnioTrafionePole* ost_traf_pole = new OstatnioTrafionePole(wspolrzedna_y - 1, wspolrzedna_x - 1, 2);
			return ost_traf_pole;
		}
		else//jezeli trafiono
		{
			std::cout << "Bot trafil w statek\n";

			//wstawienie odpowiedniego oznaczenia na planszy przeciwnika widzianej przez gracza
			plansza2.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = 'x';
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = 'x';//ustawienie oznaczenia ze wrog trafil na planszy przeciwnika
			OstatnioTrafionePole* ost_traf_pole = new OstatnioTrafionePole(wspolrzedna_y - 1, wspolrzedna_x - 1, 1);
			return ost_traf_pole;
		}
	};
};

class StrategiaBota_Atak_Blisko_Trafienia :public IStrategiaStrza³uBota
{
public:
	~StrategiaBota_Atak_Blisko_Trafienia() {};
	OstatnioTrafionePole* strza³_bota(Plansza plansza1, Plansza plansza2, int x, int y) {
		cout << "U¿yta strategia: AtakBliskoTrafienia\n";

		std::vector<Pole> potencjalne_miejsca_nastêpnego_trafienia;
		std::vector<Pole> mo¿liwe_miejsca_nastêpnego_trafienia;

		//mo¿liwe kierunki ruchu po trafieniu
		Pole* lewo = new Pole(y, x-1);
		Pole* prawo = new Pole(y, x+1);
		Pole* dó³ = new Pole(y+1, x);
		Pole* góra = new Pole(y-1, x);


		//dodanie ich na listê potencjalnych kierunków ruchu
		potencjalne_miejsca_nastêpnego_trafienia.push_back(*lewo);
		potencjalne_miejsca_nastêpnego_trafienia.push_back(*prawo);
		potencjalne_miejsca_nastêpnego_trafienia.push_back(*dó³);
		potencjalne_miejsca_nastêpnego_trafienia.push_back(*góra);


		//przejrzenie tej listy w celu sprawdzenia, czy nie wychodzimy poza planszê i czy nie s¹ to pola ju¿ trafione
		
		//je¿eli w prawo mamy trafienie, to nie chcemy szukaæ w górê i w dó³, tylko szukamy na lewo
		if (x!=9 && plansza1.pola_planszy[prawo->y][prawo->x]->symbol == 'x') {
			mo¿liwe_miejsca_nastêpnego_trafienia.push_back(*lewo);
		}
		else if (x!=0 && plansza1.pola_planszy[lewo->y][lewo->x]->symbol == 'x') {
			mo¿liwe_miejsca_nastêpnego_trafienia.push_back(*prawo);
		}
		else if (y!= 0 && plansza1.pola_planszy[góra->y][góra->x]->symbol == 'x') {
			mo¿liwe_miejsca_nastêpnego_trafienia.push_back(*dó³);
		}
		else if (y!=9 && plansza1.pola_planszy[dó³->y][dó³->x]->symbol == 'x') {
			mo¿liwe_miejsca_nastêpnego_trafienia.push_back(*góra);
		}
		else {
			for (Pole pole : potencjalne_miejsca_nastêpnego_trafienia) {
				if (pole.x >= 0 && pole.x <= 9 && pole.y >= 0 && pole.y <= 9 && (plansza1.pola_planszy[pole.y][pole.x]->symbol != 'x' && plansza1.pola_planszy[pole.y][pole.x]->symbol != '.'))
				{
					mo¿liwe_miejsca_nastêpnego_trafienia.push_back(pole);
				}
			}
		}
		
		int selectedIndex,temp_x,temp_y;
		//ustawienie losowego kierunku ruchu z mo¿liwych (spe³niaj¹cych warunki)
		if(mo¿liwe_miejsca_nastêpnego_trafienia.size()!=0){
			selectedIndex = rand() % mo¿liwe_miejsca_nastêpnego_trafienia.size();
			temp_x = mo¿liwe_miejsca_nastêpnego_trafienia[selectedIndex].x;
			temp_y = mo¿liwe_miejsca_nastêpnego_trafienia[selectedIndex].y;
		}
		else return new OstatnioTrafionePole(0,0,-1);




		std::cout << "Strzal bota: X=" + std::to_string(temp_y) + ", Y=" + std::to_string(temp_x) + "\n";
		if (plansza1.pola_planszy[temp_y][temp_x]->symbol == ' ')//jezeli trafienie w puste pole
		{
			std::cout << "Bot trafil w puste\n";
			//ustawienie oznaczen strzalu na odpowiednich planszach i zwrocenie oznaczenia nietrafienia
			plansza1.pola_planszy[temp_y][temp_x]->symbol = '.';
			plansza2.pola_planszy[temp_y][temp_x]->symbol = '.';
			mo¿liwe_miejsca_nastêpnego_trafienia.erase(std::next(mo¿liwe_miejsca_nastêpnego_trafienia.begin(),selectedIndex));
			OstatnioTrafionePole* ost_traf_pole = new OstatnioTrafionePole(temp_y, temp_x, 0);
			return ost_traf_pole;

		}
		//jezeli trafienie w pole gdzie juz strzelano
		else if (plansza1.pola_planszy[temp_y][temp_x]->symbol == 'x' || plansza1.pola_planszy[temp_y][temp_x]->symbol == '.')
		{
			std::cout << "Bot trafil w x\n";
			//wrocenie oznaczenia nietrafienia
			mo¿liwe_miejsca_nastêpnego_trafienia.erase(std::next(mo¿liwe_miejsca_nastêpnego_trafienia.begin(), selectedIndex));
			OstatnioTrafionePole* ost_traf_pole = new OstatnioTrafionePole(temp_y, temp_x, 2);
			return ost_traf_pole;
		}
		else//jezeli trafiono
		{
			std::cout << "Bot trafil w statek\n";

			//wstawienie odpowiedniego oznaczenia na planszy przeciwnika widzianej przez gracza
			plansza2.pola_planszy[temp_y][temp_x]->symbol = 'x';
			plansza1.pola_planszy[temp_y][temp_x]->symbol = 'x';//ustawienie oznaczenia ze wrog trafil na planszy przeciwnika
			mo¿liwe_miejsca_nastêpnego_trafienia.erase(std::next(mo¿liwe_miejsca_nastêpnego_trafienia.begin(), selectedIndex));
			OstatnioTrafionePole* ost_traf_pole = new OstatnioTrafionePole(temp_y, temp_x, 1);
			return ost_traf_pole;
		}
	};
};