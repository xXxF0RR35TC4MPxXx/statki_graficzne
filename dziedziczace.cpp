#pragma warning( disable : 6386 )
#pragma warning(disable:4996)
#include "dziedziczace.h"

#include <string>
#include <Windows.h>
#include "render_api.h"
#include <iostream>
#include "KontekstStrategiiBota.h"

#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822

#define ATAKBLISKOTRAFIENIA 2
#define STRZA£LOSOWY 1
gra_z_graczem::gra_z_graczem() :rozgrywka()//konstruktor
{
	tryb_gry = 2;
}

int gra_z_graczem::gra(sf::RenderWindow* Window, render_api* renderer)//funkcja do przeprowadzenia tury gry(gracz vs gracz)
{
	int czy_trafione = 0;
	int jezeli_wygrana = 0;
	while (1)
	{
		sf::Event przekazkomputerevent;
		bool wyszedl_z_okna = false;
		jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			wygrana(Window, nick1);//wyswietlenie statystyk
			return 1;
		}
		
		std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";

		renderer->render_planszy_gra(plansza1_1, plansza1_2, plansza2_1, plansza2_2, Window, 1, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
		std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		sf::sleep(sf::milliseconds(1000));
		
		jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			if (trafienia_1 != 0 && trafienia_2 != 0)wygrana(Window, nick1);//wyswietlenie statystyk
			return 1;
		}
		
		
		wyszedl_z_okna = false;
		while (Window->isOpen() && !wyszedl_z_okna) {
			while (Window->pollEvent(przekazkomputerevent)) {
				if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {

				}
				renderer->przeka¿_komputer(Window);
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
		
		wyszedl_z_okna = false;
		jezeli_wygrana = czy_wygrana(plansza1_1);//sprawdzanie czy gracz zatopil juz wszystkie statki
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			if(trafienia_1 !=0 && trafienia_2 !=0) wygrana(Window, nick2);//wyswietlenie statystyk
			return 1;
		}
		std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";

		renderer->render_planszy_gra(plansza2_1, plansza2_2, plansza1_1, plansza1_2, Window, 2, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);

		std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
		sf::sleep(sf::milliseconds(1000));

		jezeli_wygrana = czy_wygrana(plansza1_1);//sprawdzanie czy gracz zatopil juz wszytskie statki
		if (jezeli_wygrana == 1)//jezeli wygral
		{
			if (trafienia_1 != 0 && trafienia_2 != 0) wygrana(Window, nick2);//wyswietlenie statystyk
			return 1;
		}
		while (Window->isOpen() && !wyszedl_z_okna) {
			while (Window->pollEvent(przekazkomputerevent)) {
				if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {}

				renderer->przeka¿_komputer(Window);
				if (przekazkomputerevent.type == sf::Event::KeyPressed) {
					if (przekazkomputerevent.key.code == sf::Keyboard::Return)
					{
						wyszedl_z_okna = true;
						renderer->clear_screen(Window);
						break;
					}
				}
			}
		}
		return 0;//koniec tury
	}
}

void gra_z_graczem::ustawienia(sf::RenderWindow* Window)//gracze ustawiaja nicki oraz statki
{
	sf::Event przekazkomputerevent;
	bool wyszedl_z_okna = false;
	render_api* renderer = new render_api();

	strcpy_s(nick1, renderer->podaj_nick(Window).c_str()); //wpisanie nicku przez gracza1
	ustawienie_statkow(plansza1_1, plansza1_2, Window);//funkcja w ktorej gracz1 ustawia wszystkie swoje statki
	
	//rysowanie okna mówi¹cego graczowi1, aby przekaza³ komputer drugiej osobie.
	while (Window->isOpen() && !wyszedl_z_okna) {
		while (Window->pollEvent(przekazkomputerevent)) {
			if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {}
			renderer->przeka¿_komputer(Window);
			if (przekazkomputerevent.type == sf::Event::KeyPressed) {
				if (przekazkomputerevent.key.code == sf::Keyboard::Return)
				{
					wyszedl_z_okna = true;
					renderer->clear_screen(Window);
					break;
				}
			}
		}
	}wyszedl_z_okna = false;


	strcpy_s(nick2, renderer->podaj_nick(Window).c_str());  //wpisanie nicku przez gracza2
	ustawienie_statkow(plansza2_1, plansza2_2, Window);//funkcja w ktorej gracz2 ustawia wszystkie swoje statki
	
	//rysowanie okna mówi¹cego graczowi2, aby przekaza³ komputer pierwszej osobie.
	while (Window->isOpen() && !wyszedl_z_okna) {
		while (Window->pollEvent(przekazkomputerevent)) {
			//pusty warunek dla wciœniêcia myszy jest dlatego, bo bez niego program czasami siê zawiesza³
			//bo nie wiedzia³ co zrobiæ dla klikniêcia np. je¿eli pomiêdzy ruchem gracza a komputera
			//nastêpowa³a zmiana "focusa" okien w systemie (np. jak wejdziemy w Firefoxa i potem wrócimy do okna gry).
			if (przekazkomputerevent.type == sf::Event::MouseButtonPressed) {}

			renderer->przeka¿_komputer(Window);
			if (przekazkomputerevent.type == sf::Event::KeyPressed) {
				if (przekazkomputerevent.key.code == sf::Keyboard::Return)
				{
					wyszedl_z_okna = true;
					renderer->clear_screen(Window);
					break;
				}
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


gra_z_botem::gra_z_botem() :rozgrywka() //konstruktor
{
	kontekst_strategii_bota = new KontekstStrategiiBota(new StrategiaBota_Strza³Losowy);
	tryb_gry = 1;
}

void gra_z_botem::ustawienia(sf::RenderWindow* Window)//gracz oraz komputer uswtaiaja nicki oraz statki
{

	render_api* renderer = new render_api();
	strcpy_s(nick1, renderer->podaj_nick(Window).c_str()); //podanie nicku przez gracza1
	ustawienie_statkow(plansza1_1, plansza1_2, Window);//funkcja gdzie gracz1 ustawia statki

	sf::Event ruch_komputera_event;
	bool wyjsc_z_okna = false;
	while (Window->isOpen() && !wyjsc_z_okna) {
		while (Window->pollEvent(ruch_komputera_event)) {
			if (ruch_komputera_event.type == sf::Event::MouseButtonPressed) {

			}
			renderer->komputer_ustawia_statki(Window);
			wyjsc_z_okna = true;
			break;
		}
	}
	strcpy_s(nick2, "Komputer");//ustawienie drugiego nicku jako 'Komputer'
	ustawienie_statkow_bot(plansza2_1, plansza2_2);//funkcja gdzie komputer ustawia statki
}


OstatnioTrafionePole* gra_z_botem::strzal_bot(char plansza1[10][10], char plansza2[10][10], int x, int y)//funkcja gdzie komputer losuje w ktore pole strzelic
{
	//KontekstStrategiiBota strategia_bota_atak_blisko_trafienia(new StrategiaBota_Atak_Blisko_Trafienia());
	return kontekst_strategii_bota->nastêpnyStrza³Bota(plansza1_1, plansza2_2, x, y);
}

int gra_z_botem::gra(sf::RenderWindow* Window, render_api* renderer)//funkcja do przeprowadzenia tury gry(gracz vs komputer)
{
	int czy_trafione = 0;
	int jezeli_wygrana = 0;
	
	while (1)
	{
			bool nowa_zmiana = true;
			sf::Event ruch_komputera_event;
			jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral

			if (jezeli_wygrana == 1)//jezeli wygral
			{
				if (trafienia_1 != 0 || trafienia_2 != 0)wygrana(Window, nick1);//wyswietlenie statystyk
				return 1;
			}
			std::cout << "Wartosci zmiennych przed ta tura: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";

			renderer->render_planszy_gra(plansza1_1, plansza1_2, plansza2_1, plansza2_2, Window, 3, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);

			std::cout << "Wartosci zmiennych po tej turze: " + std::to_string(oddane_strzaly_1) + ", " + std::to_string(oddane_strzaly_2) + ", " + std::to_string(trafienia_1) + ", " + std::to_string(trafienia_2) + "\n";
			bool wyjsc_z_okna = false;
			jezeli_wygrana = czy_wygrana(plansza2_1);//sprawdzenie czy gracz wygral
			if (jezeli_wygrana == 1)//jezeli wygral
			{
				if (trafienia_1 != 0 || trafienia_2 != 0) wygrana(Window, nick1);//wyswietlenie statystyk
				return 1;
			}
			//opóŸnienie, ¿eby wyœwietliæ komunikat o pudle
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
			OstatnioTrafionePole* ostatnio_trafione = strzal_bot(plansza1_1, plansza2_2, ostatnio_trafiony_x, ostatnio_trafiony_y);//wywolanie funkcji w ktorej komputer wybiera gdzie strzelic i sprawdzenie gdzie trafil
			czy_trafione = ostatnio_trafione->wynik_trafienia;
			ostatnio_trafiony_x = ostatnio_trafione->x;
			ostatnio_trafiony_y = ostatnio_trafione->y;
			printf("Czy bot trafil: %d\n", czy_trafione);
			oddane_strzaly_2++;//doliczenie do statystyk oddane strzaly
			//sprawdzanie czy trafil
			if (czy_trafione == 1)
			{
				
				//w przypadku trafienia zmiena strategii na strzelanie w okolice tego trafienia do momentu spud³owania
				if(nowa_zmiana)kontekst_strategii_bota->zmieñ_strategiê(new StrategiaBota_Atak_Blisko_Trafienia());
				nowa_zmiana = false;
				trafienia_2++;//doliczenie do statystyk trafione strzaly
			}
			jezeli_wygrana = czy_wygrana(plansza1_1);//sprawdzenie czy komputer wygral
			if (jezeli_wygrana == 1)//jezeli wygral
			{
				//printf("WYGRAL: %s \n", nick2);
				if (trafienia_1 != 0 && trafienia_2 != 0) wygrana(Window, nick2);//wyswietlenie statystyk
				return 1;
			}
		} while (czy_trafione == 1 || czy_trafione == 2);//strzela do poki trafia lub trafil w to w co juz strzelal(bot nie marnuje strzalow na stzrelanie w cos co juz strzelal)
		kontekst_strategii_bota->zmieñ_strategiê(new StrategiaBota_Strza³Losowy());
		return 0;//koniec tury
	}
}

void gra_z_botem::ustawienie_statkow_bot(char plansza1[10][10], char plansza2[10][10])//funkcja w ktorej komputer losuje gdzie postawic statki
{
	render_api* renderer = new render_api();
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja;
	int odpowiedz = 0;
	for (int i = 0; i < 4; i++)//ustawianie statkow jednomasztowych
	{
		do
		{
			//komputer losuje 2 liczby z przedzialu 1-10
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);//sprawdzanie czy w wylosowanej pozycji moze stac statek
		} while (odpowiedz != 1);//losuje do poki nie wylosuje dobrej pozycji
		plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '1';//wpisanie statku do tablicy w odpowiednie miejsce
	}
	for (int i = 0; i < 3; i++)//ustawianie statkow dwumasztowych
	{
		while (1)
		{
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 1, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;

			}
			else if (orientacja == 3)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y - 2][wspolrzedna_x - 1] = '2';
		}
		else if (orientacja == 2)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '2';
		}
		else if (orientacja == 3)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 2] = '2';
		}
		else if (orientacja == 4)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
			plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '2';
		}
	}
	for (int i = 0; i < 2; i++)//ustawianie statkow trzymasztowych
	{
		while (1)
		{
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 2, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;

			}
			else if (orientacja == 3)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x - 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 2, plansza1);
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 2][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 3][wspolrzedna_x - 1] = '3';
		}
		else if (orientacja == 2)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x + 1] = '3';
		}
		else if (orientacja == 3)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 2] = '3';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 3] = '3';
		}
		else if (orientacja == 4)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '3';
			plansza1[wspolrzedna_y + 1][wspolrzedna_x - 1] = '3';
		}
	}
	for (int i = 0; i < 1; i++)//ustawianie statkow czteromasztowego
	{
		while (1)
		{
			//komputer losuje 2 liczby z przedzialu 1-10 oraz orientacji statku 1-4
			wspolrzedna_x = (rand() % 10) + 1;
			wspolrzedna_y = (rand() % 10) + 1;
			orientacja = (rand() % 4) + 1;
			//sprawdzanie czy w danej orientacji moze stac statek poprzez wywolywanie funkcji sprawdzajacej to dla kazdej wspolrzednej w ktorej bedzie sie znajdowal statek
			if (orientacja == 1)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 2, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y - 3, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 2)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x + 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x + 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x + 3, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 3)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x - 1, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x - 2, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x - 3, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
			}
			else if (orientacja == 4)
			{
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 1, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 2, plansza1);
				if (odpowiedz == 0) continue;
				odpowiedz = renderer->czy_moze_tu_stac(wspolrzedna_x, wspolrzedna_y + 3, plansza1);
				if (odpowiedz == 0) continue;
			}
			break;//jezeli moze stac w takim miejscu przerwanie petli
		}
		//wpisaniu statku do tablicy w odpowiednie miejsce(w zaleznosci od orientacji)
		if (orientacja == 1)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 2][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 3][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 4][wspolrzedna_x - 1] = '4';
		}
		else if (orientacja == 2)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x + 1] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x + 2] = '4';
		}
		else if (orientacja == 3)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 2] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 3] = '4';
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 4] = '4';
		}
		else if (orientacja == 4)
		{
			plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y + 1][wspolrzedna_x - 1] = '4';
			plansza1[wspolrzedna_y + 2][wspolrzedna_x - 1] = '4';
		}
	}
	std::cout << "WYGENEROWANA PLANSZA BOTA\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if(plansza1[i][j]!=' ')
				std::cout << plansza1[i][j];
			else std::cout << '-';
		}std::cout << "\n";
	}
	std::cout << "\n";
}
