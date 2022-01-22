#pragma warning( disable : 6386 )
#pragma warning(disable:4996)
#include "dziedziczace.h"

#include <string>
#include <Windows.h>
#include "render_api.h"
#include <iostream>

#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822

gra_z_graczem::gra_z_graczem() :rozgrywka()//konstruktor
{
	tryb_gry = 2;
}

void gra_z_graczem::przekaz_komputer(RenderWindow* Window, render_api* renderer) {
	bool wyszedl_z_okna = false;

	sf::Event przekazkomputerevent;
	while (Window->isOpen() && !wyszedl_z_okna) {
		while (Window->pollEvent(przekazkomputerevent)) {
			if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {

			}
			renderer->przekaz_komputer(Window);
			if (przekazkomputerevent.type == sf::Event::KeyPressed) {
				if (przekazkomputerevent.key.code == sf::Keyboard::Return)
				{
					wyszedl_z_okna = true;
					Window->clear();
					break;
				}
			}
		}
	}
}

int gra_z_graczem::przebieg_jednej_tury(sf::RenderWindow* Window, render_api* renderer)//funkcja do przeprowadzenia tury gry(gracz vs gracz)
{
	int czy_trafione = 0;
	int jezeli_wygrana = 0;
	while (1)
	{
		if (czy_wygrana(plansza2_1) == 1)//jezeli gracz1 wygral
		{
			if (trafienia_1 != 0 && trafienia_2 != 0) wygrana(Window, nick1);//wyswietlenie ekranu ze statystykami
			return 1;
		}
		
		
		std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		//oddawanie strza�u przez pierwszego gracza
		renderer->render_planszy_gra(plansza1_1, plansza1_2, plansza2_1, plansza2_2, Window, 1, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
		std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		sf::sleep(sf::milliseconds(1000));
		
		if (czy_wygrana(plansza2_1) == 1)//jezeli gracz1 wygral
		{
			if (trafienia_1 != 0 && trafienia_2 != 0)wygrana(Window, nick1);//wyswietlenie statystyk
			return 1;
		}
		
		//oczekiwanie na przekazanie komputera drugiemu graczowi
		przekaz_komputer(Window, renderer);
		
		if (czy_wygrana(plansza1_1) == 1)//jezeli gracz2 wygral
		{
			if(trafienia_1 !=0 && trafienia_2 !=0) wygrana(Window, nick2);//wyswietlenie statystyk
			return 1;
		}

		
		std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		//oddawanie strza�u przez drugiego gracza
		renderer->render_planszy_gra(plansza2_1, plansza2_2, plansza1_1, plansza1_2, Window, 2, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
		std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		sf::sleep(sf::milliseconds(1000));

		if (czy_wygrana(plansza1_1) == 1)//jezeli gracz2 wygral
		{
			if (trafienia_1 != 0 && trafienia_2 != 0) wygrana(Window, nick2);//wyswietlenie statystyk
			return 1;
		}

		//oczekiwanie na przekazanie komputera pierwszemu graczowi
		przekaz_komputer(Window, renderer);
		return 0;//koniec tury
	}
}

void gra_z_graczem::ustawienia(sf::RenderWindow* Window)//gracze ustawiaja nicki oraz statki
{
	render_api* renderer = render_api::GetInstance();

	strcpy_s(nick1, renderer->podaj_nick(Window).c_str()); //wpisanie nicku przez gracza1
	renderer->render_planszy_przy_ustawianiu(plansza1_1, plansza1_2, Window);//funkcja w ktorej gracz1 ustawia wszystkie swoje statki
	
	//rysowanie okna m�wi�cego graczowi1, aby przekaza� komputer drugiej osobie.
	przekaz_komputer(Window, renderer);

	strcpy_s(nick2, renderer->podaj_nick(Window).c_str());  //wpisanie nicku przez gracza2
	renderer->render_planszy_przy_ustawianiu(plansza2_1, plansza2_2, Window);//funkcja w ktorej gracz1 ustawia wszystkie swoje statki
	
	//rysowanie okna m�wi�cego graczowi2, aby przekaza� komputer pierwszej osobie.
	przekaz_komputer(Window, renderer);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


gra_z_botem::gra_z_botem() :rozgrywka() //konstruktor
{
	KontekstStrategiiBota(new StrategiaBota_StrzalLosowy);
	tryb_gry = 1;
}

void gra_z_botem::ustawienia(sf::RenderWindow* Window)//gracz oraz komputer ustawiaj� nicki oraz statki
{

	render_api* renderer = render_api::GetInstance();
	strcpy_s(nick1, renderer->podaj_nick(Window).c_str()); //podanie nicku przez gracza1
	renderer->render_planszy_przy_ustawianiu(plansza1_1, plansza1_2, Window);//funkcja w ktorej gracz1 ustawia wszystkie swoje statki

	//wy�wietlenie ekranu z info o ustawianiu statk�w przez komputer
	sf::Event ruch_komputera_event;
	bool wyjsc_z_okna = false;
	while (Window->isOpen() && !wyjsc_z_okna) {
		while (Window->pollEvent(ruch_komputera_event)) {
			if (ruch_komputera_event.type == sf::Event::MouseButtonPressed) {}
			renderer->komputer_ustawia_statki(Window);
			wyjsc_z_okna = true;
			break;
		}
	}
	strcpy_s(nick2, "Komputer");//ustawienie drugiego nicku jako 'Komputer'
	ustawienie_statkow_bot(plansza2_1, plansza2_2);//funkcja gdzie komputer ustawia statki
}


OstatnioTrafionePole* gra_z_botem::strzal_bot(Plansza plansza1, Plansza plansza2, int x, int y)//funkcja gdzie komputer losuje w ktore pole strzelic
{
	return obecna_strategia->strzal_bota(plansza1, plansza2, x, y);
}

int gra_z_botem::przebieg_jednej_tury(sf::RenderWindow* Window, render_api* renderer)//funkcja do przeprowadzenia tury gry(gracz vs komputer)
{
	int czy_trafione = 0;
	int jezeli_wygrana = 0;
	
	while (1)
	{
			bool nowa_zmiana = true;
			bool wyjsc_z_okna = false;
			int trafienia_bota_z_rzedu = 0;
			sf::Event ruch_komputera_event;
			jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral

			if (jezeli_wygrana == 1)//jezeli wygral
			{
				if (trafienia_1 != 0 || trafienia_2 != 0)wygrana(Window, nick1);//wyswietlenie statystyk
				return 1;
			}
			//oddawanie strza�u przez gracza na wyrenderowanej planszy
			std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
			renderer->render_planszy_gra(plansza1_1, plansza1_2, plansza2_1, plansza2_2, Window, 3, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
			std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
			
			jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
			if (jezeli_wygrana == 1)//jezeli wygral
			{
				if (trafienia_1 != 0 || trafienia_2 != 0) wygrana(Window, nick1);//wyswietlenie statystyk
				return 1;
			}
			//op�nienie, �eby wy�wietli� komunikat o pudle
			while (Window->isOpen() && !wyjsc_z_okna) {
				sf::sleep(sf::milliseconds(1000));
				wyjsc_z_okna = true;
				break;
			}
			
			wyjsc_z_okna = false;
			while (Window->isOpen() && !wyjsc_z_okna) {
				while (Window->pollEvent(ruch_komputera_event)) {
					if (ruch_komputera_event.type == sf::Event::MouseButtonPressed) {

					}
					renderer->ruch_wykonuje_komputer(Window);
					wyjsc_z_okna = true;
					break;
				}
			}
		do
		{
			//oddanie strza�u przez bota
			OstatnioTrafionePole* ostatnio_trafione = strzal_bot(plansza1_1, plansza2_2, ostatnio_trafiony_x, ostatnio_trafiony_y);//wywolanie funkcji w ktorej komputer wybiera gdzie strzelic i sprawdzenie gdzie trafil
			czy_trafione = ostatnio_trafione->wynik_trafienia;
			ostatnio_trafiony_x = ostatnio_trafione->x;
			ostatnio_trafiony_y = ostatnio_trafione->y;
			printf("Czy bot trafil: %d\n", czy_trafione);
			oddane_strzaly_2++;//doliczenie do statystyk oddane strzaly

			//sprawdzanie czy trafil
			if (czy_trafione == -1) {
				zmien_strategie(new StrategiaBota_StrzalLosowy());
				trafienia_bota_z_rzedu = 0;
			}
			if (czy_trafione == 2) {
				zmien_strategie(new StrategiaBota_StrzalLosowy());
				trafienia_bota_z_rzedu = 0;
			}
			if (czy_trafione == 1)
			{
				trafienia_bota_z_rzedu++;
				if (trafienia_bota_z_rzedu == 4) 
				{ 
					zmien_strategie(new StrategiaBota_StrzalLosowy()); 
					trafienia_bota_z_rzedu = 0; 
				}

				//w przypadku trafienia zmiana strategii na strzelanie w okolice tego trafienia do momentu spud�owania
				if(nowa_zmiana) zmien_strategie(new StrategiaBota_Atak_Blisko_Trafienia());
				nowa_zmiana = false;
				trafienia_2++;//doliczenie do statystyvk trafione strzaly
			}

			jezeli_wygrana = czy_wygrana(plansza1_1);//sprawdzenie czy komputer wygral
			if (jezeli_wygrana == 1)//jezeli wygral
			{
				//printf("WYGRAL: %s \n", nick2);
				if (trafienia_1 != 0 && trafienia_2 != 0) wygrana(Window, nick2);//wyswietlenie statystyk
				return 1;
			}
		} while (czy_trafione == 1 || czy_trafione == 2);//strzela do poki trafia lub trafil w to w co juz strzelal(bot nie marnuje strzalow na stzrelanie w cos co juz strzelal)
		zmien_strategie(new StrategiaBota_StrzalLosowy()); //po zako�czeniu tury powr�t do strategii losowych strza��w
		return 0;//koniec tury
	}
}

void gra_z_botem::ustawienie_statkow_jednomasztowych(render_api* renderer, Plansza plansza1) {
	unsigned int wspolrzedna_x, wspolrzedna_y;
	int odpowiedz = 0;
	for (int i = 0; i < 4; i++)//ustawianie statkow jednomasztowych
	{
		do
		{
			//komputer losuje 2 liczby z przedzialu 1-10
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y);//sprawdzanie czy w wylosowanej pozycji moze stac statek
		} while (odpowiedz != 1);//losuje do poki nie wylosuje dobrej pozycji
		plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = '1';//wpisanie statku do tablicy w odpowiednie miejsce
	}
}

void gra_z_botem::ustawienie_statkow_dwumasztowych(render_api* renderer, Plansza plansza1) {
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja;
	int odpowiedz = -1;
	for (int i = 0; i < 3; i++)//ustawianie statkow dwumasztowych
	{
		while (1)
		{
			odpowiedz = -1;
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				for (int j = 0; j < 2 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - j);
					//odp=plansza1->czymozetusta�(x,y);
					//plansza{
					//	char tab[10][10];
					//	czy_moze_tu_stac(int x, int y){};
					//}

					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				for (int j = 0; j < 2 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + j, wspolrzedna_y);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 3)
			{
				for (int j = 0; j < 2 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x - j, wspolrzedna_y);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				for (int j = 0; j < 2 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + j);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
		{
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = '2';
			plansza1.pola_planszy[wspolrzedna_y - 2][wspolrzedna_x - 1]->symbol = '2';
		}
		else if (orientacja == 2)
		{
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = '2';
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x]->symbol = '2';
		}
		else if (orientacja == 3)
		{
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = '2';
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 2]->symbol = '2';
		}
		else if (orientacja == 4)
		{
			plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - 1]->symbol = '2';
			plansza1.pola_planszy[wspolrzedna_y][wspolrzedna_x - 1]->symbol = '2';
		}
	}
}

void gra_z_botem::ustawienie_statkow_trojmasztowych(render_api* renderer, Plansza plansza1) {
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja;
	int odpowiedz = 0;
	for (int i = 0; i < 2; i++)//ustawianie statkow trzymasztowych
	{
		while (1)
		{
			odpowiedz = -1;
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				for (int j = 0; j < 3 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - j);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				for (int j = 0; j < 3 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + j, wspolrzedna_y);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 3)
			{
				for (int j = 0; j < 3 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x - j, wspolrzedna_y);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				for (int j = 0; j < 3 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + j);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1) 
			for (int j = 1;j < 4; j++) plansza1.pola_planszy[wspolrzedna_y - j][wspolrzedna_x - 1]->symbol = '3';
		else if (orientacja == 2)
			for (int j = -1;j< 2; j++) plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x + j]->symbol = '3';
		else if (orientacja == 3)
			for (int j = 1; j < 4; j++) plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x - j]->symbol = '3';
		else if (orientacja == 4)
			for (int j = -1; j< 2; j++) plansza1.pola_planszy[wspolrzedna_y + j][wspolrzedna_x - 1]->symbol = '3';
	}
}

void gra_z_botem::ustawienie_statkow_czteromasztowych(render_api* renderer, Plansza plansza1) {
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja;
	int odpowiedz = -1;
	for (int i = 0; i < 1; i++)//ustawianie statkow czteromasztowego
	{
		
		while (1)
		{
			odpowiedz = -1;
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				for (int j = 0; j < 4 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - j);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				for (int j = 0; j < 4 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x + j, wspolrzedna_y);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 3)
			{
				for (int j = 0; j < 4 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x - j, wspolrzedna_y);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				for (int j = 0; j < 4 && odpowiedz != 0; j++) {
					odpowiedz = plansza1.czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + j);
					if (odpowiedz == 0) break;
				}
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
			for (int j = 1; j < 5; j++) plansza1.pola_planszy[wspolrzedna_y - j][wspolrzedna_x - 1]->symbol = '4';
		else if (orientacja == 2)
			for (int j = -1; j < 3; j++) plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x + j]->symbol = '4';
		else if (orientacja == 3)
			for (int j = 1; j < 5; j++) plansza1.pola_planszy[wspolrzedna_y - 1][wspolrzedna_x -j]->symbol = '4';
		else if (orientacja == 4)
			for (int j = -1; j< 3; j++) plansza1.pola_planszy[wspolrzedna_y + j][wspolrzedna_x - 1]->symbol = '4';
	}
}

void gra_z_botem::ustawienie_statkow_bot(Plansza plansza1, Plansza plansza2)//funkcja w ktorej komputer losuje gdzie postawic statki
{
	render_api* renderer = render_api::GetInstance();
	int odpowiedz = 0;

	gra_z_botem::ustawienie_statkow_jednomasztowych(renderer, plansza1);
	
	gra_z_botem::ustawienie_statkow_dwumasztowych(renderer, plansza1);
	
	gra_z_botem::ustawienie_statkow_trojmasztowych(renderer, plansza1);

	gra_z_botem::ustawienie_statkow_czteromasztowych(renderer, plansza1);
	
	//wypisywanie planszy bota w konsoli (wy��cznie dla �atwego debugu)
	std::cout << "WYGENEROWANA PLANSZA BOTA\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if(plansza1.pola_planszy[i][j]->symbol!=' ')
				std::cout << plansza1.pola_planszy[i][j]->symbol;
			else std::cout << '-';
		}std::cout << "\n";
	}
	std::cout << "\n";
}
