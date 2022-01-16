#include "bazowa.h"
#include "string.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include "render_api.h"
#pragma warning( disable : 6386 )
#pragma warning(disable:4996)

#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822
using namespace std;

rozgrywka::rozgrywka() :tryb_gry(0), nick1("Gracz1"), nick2("Gracz2"), oddane_strzaly_1(0), oddane_strzaly_2(0), trafienia_1(0), trafienia_2(0)//konstruktor
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			//uzupelnianie tablic(plansz) pustymi polami
			plansza1_1[i][k] = { ' ' };
			plansza1_2[i][k] = { ' ' };
			plansza2_1[i][k] = { ' ' };
			plansza2_2[i][k] = { ' ' };
		}
	}
}

void rozgrywka::ustawienia(sf::RenderWindow* Window)
{
}

void rozgrywka::pokaz_plansze_przy_ustawianiu(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow* Window)//funkcja tworzy i pokazuje plansze z przeslanych dwoch tablic dwuwymiarowych
{
	render_api* renderer = new render_api();
	renderer->render_planszy_przy_ustawianiu(plansza1, plansza2, Window);
}
void rozgrywka::pokaz_plansze_gra(char plansza1[10][10], char plansza2[10][10], char plansza2_1[10][10], char plansza2_2[10][10], sf::RenderWindow* Window, int typ, unsigned int oddane_strzaly_1, unsigned  int oddane_strzaly_2, unsigned  int trafienia_1, unsigned  int trafienia_2)//funkcja tworzy i pokazuje plansze z przeslanych dwoch tablic dwuwymiarowych
{
	render_api* renderer = new render_api();
	//cout << "pokaz_plansze\n";
	renderer->render_planszy_gra(plansza1, plansza2, plansza2_1, plansza2_2, Window, typ, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);
	//cout << "Wyrenderowano calosc!\n";
}
int rozgrywka::czy_wygrana(char plansza[10][10])//funkcja sprawdza czy w przeslanej tablicy znajduja sie jeszcze symbole oznaczajace niezatopiony statek i zwraca odpowiednia informacje
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (plansza[i][k] == '1' || plansza[i][k] == '2' || plansza[i][k] == '3' || plansza[i][k] == '4')
			{
				return 0;
			}
		}
	}
	return 1;
}


void rozgrywka::wygrana(sf::RenderWindow* Window, char nick[])//funkcja ktora wyswietla statystyki po wygranej jednej ze stron
{
	

	//cout << "rozgrywka::wygrana()\n";
	render_api* renderer = new render_api();
	bool wyszedl_z_okna = false;
	sf::Event wyjdzdomenuevent;
	if (trafienia_1 != 0 && trafienia_2 != 0) {
		while (Window->isOpen() && !wyszedl_z_okna) {
			while (Window->pollEvent(wyjdzdomenuevent)) {
				if (wyjdzdomenuevent.type == sf::Event::MouseButtonPressed) {

				}
				renderer->drukuj_statystyki(Window, nick, nick1, nick2, oddane_strzaly_1, oddane_strzaly_2, trafienia_1, trafienia_2);

				if (wyjdzdomenuevent.type == sf::Event::KeyPressed) {
					if (wyjdzdomenuevent.key.code == sf::Keyboard::Return)
					{
						//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
						wyszedl_z_okna = true;
						renderer->clear_screen(Window);
						break;
					}
				}
			}
		}
	}
	
}


void rozgrywka::podawanie_orientacji_statku(unsigned int* orientacja)//funkcja pobiera od uzytkownika orientacje statku na planszy
{
}

int rozgrywka::czy_moze_tu_stac(unsigned int wspolrzedna_x, unsigned int wspolrzedna_y, char plansza[10][10])//funkcja sprawdza czy postawiony statek w tej pozycji nie
{																											//bedzie kolidowal z juz postawionymi statkami lub czy nie
	//czy nie wychodzi za tablice																			//wychodzi za plansze
	if (wspolrzedna_x > 10 || wspolrzedna_x < 1 || wspolrzedna_y > 10 || wspolrzedna_y < 1)					//zwraca 0 jezeli nie moze stac na tej pozycji lub 1 jezeli moze
	{
		return 0;
	}
	if (plansza[wspolrzedna_y - 1][wspolrzedna_x - 1] != ' ')
	{
		return 0;
	}
	if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy czegos nie dotyka po lewej)
	{
		if (plansza[wspolrzedna_y - 1][wspolrzedna_x - 2] != ' ')
		{
			return 0;
		}
	}
	else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy czegos nie dotyka po prawej)
	{
		if (plansza[wspolrzedna_y - 1][wspolrzedna_x] != ' ')
		{
			return 0;
		}
	}
	else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy nie dotyka czegos z obu stron)
	{
		if (plansza[wspolrzedna_y - 1][wspolrzedna_x] != ' ' || plansza[wspolrzedna_y - 1][wspolrzedna_x - 2] != ' ')
		{
			return 0;
		}
	}
	if (wspolrzedna_y == 10)//jezeli dotyka dolna sciane(sprawdzamy tylko czy czegos nie dotyka u gory)
	{
		if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 1] != ' ')
		{
			return 0;
		}
	}
	else if (wspolrzedna_y == 1)//jezeli dotyka dolna sciane(sprawdzamy tylko czy czegos nie dotyka u dolu)
	{
		if (plansza[wspolrzedna_y][wspolrzedna_x - 1] != ' ')
		{
			return 0;
		}
	}
	else//jezeli nie dotyka dotyka zadnej sciany(gornej lub dolnej)(sprawdzamy czy nie dotyka czegos u gory i dolu)
	{
		if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 1] != ' ' || plansza[wspolrzedna_y][wspolrzedna_x - 1] != ' ')
		{
			return 0;
		}
	}
	if (wspolrzedna_y > 1)//jezeli nie dotyka gornej sciany
	{
		if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy lewy gorny rog jest wolny)
		{
			if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 2] != ' ')
			{
				return 0;
			}
		}
		else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy prawy gorny rog jest wolny)
		{
			if (plansza[wspolrzedna_y - 2][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
		else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy gorne rogi sa wolne)
		{
			if (plansza[wspolrzedna_y - 2][wspolrzedna_x - 2] != ' ' || plansza[wspolrzedna_y - 2][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
	}
	if (wspolrzedna_y < 10)//jezeli nie dotyka dolnej sciany
	{
		if (wspolrzedna_x == 10)//jezeli dotyka prawej sciany(sprawdzamy tylko czy lewy dolny rog jest wolny)
		{
			if (plansza[wspolrzedna_y][wspolrzedna_x - 2] != ' ')
			{
				return 0;
			}
		}
		else if (wspolrzedna_x == 1)//jezeli dotyka lewej sciany(sprawdzamy tylko czy prawy dolny rog jest wolny)
		{
			if (plansza[wspolrzedna_y][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
		else//jezeli nie dotyka zadnej sciany(lewej lub prawej)(sprawdzamy czy dolne rogi sa wolne)
		{
			if (plansza[wspolrzedna_y][wspolrzedna_x - 2] != ' ' || plansza[wspolrzedna_y][wspolrzedna_x] != ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}

void rozgrywka::ustawienie_statkow(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow* Window)//funkcja  ustawia statki na planszy(wersja dla gracza)
{
	pokaz_plansze_przy_ustawianiu(plansza1, plansza2, Window);//pokazanie odpowiedniej planszy
}

void rozgrywka::zapisywanie(sf::RenderWindow* Window)//funkcja do zapisania stanu gry
{
	fstream plik;
	render_api* renderer = new render_api();
	string nazwa_pliku;
	sf::Text text;
	text.setFillColor(sf::Color::Black);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");
	text.setFont(retrofont);
	text.setCharacterSize(50);
	text.setPosition(sf::Vector2f(75, 250));
	string nazwa_pliku_od_usera;
	
	bool koniec_zapisu = false;
	
	while (Window->isOpen() && !koniec_zapisu)
	{
		sf::Event save_event;
		renderer->wczytaj_save_background_method(Window, text);
		while (Window->pollEvent(save_event)) {
			if (save_event.type == sf::Event::Closed) {
				Window->close();
			}
			if (save_event.type == sf::Event::MouseButtonPressed) {

			}
			//przy wpisaniu jakiejœ literki
			if (save_event.type == sf::Event::TextEntered)
			{
				bool przejsc_dalej = false;
				//if normalny_klawisz
				if (save_event.text.unicode < 127 &&
					save_event.text.unicode >= 48 &&
					save_event.text.unicode != '\n' &&
					save_event.text.unicode != '\r' &&
					save_event.text.unicode != 10 &&
					save_event.text.unicode != '\v' &&
					save_event.text.unicode != 27 &&
					save_event.text.unicode != 32 &&
					save_event.text.unicode != '\b' &&
					text.getString().getSize() < 16)
				{
					nazwa_pliku_od_usera += static_cast<char>(save_event.text.unicode);
					text.setString(nazwa_pliku_od_usera); //dodaj do stringa

				}
				//je¿eli masz co usuwaæ, to usuñ ostatnio dodany znak
				else if (text.getString().getSize() > 0 && save_event.text.unicode == '\b') {
					nazwa_pliku_od_usera.pop_back();
					text.setString(nazwa_pliku_od_usera);
				}
				else if ((save_event.text.unicode == '\n' || save_event.text.unicode == '\r') && text.getString().getSize() > 0) {
					plik.open(nazwa_pliku_od_usera, ios::out);
					if (plik.good() == false)//jezeli nie udalo sie otworzyc pliku
					{
						cout << "NIE UDALO SIE ZAPISAC PLIKU\n";
						break;//powrot na poczatek petli, aby uzytkownik mogl jeszcze raz podac nazwe pliku do zapisu
					}
					for (int i = 0; i < 10; i++)
					{
						for (int k = 0; k < 10; k++)
						{
							if (plansza1_1[i][k] == ' ')
							{
								plansza1_1[i][k] = '0';
							}
							if (plansza1_2[i][k] == ' ')
							{
								plansza1_2[i][k] = '0';
							}
							if (plansza2_1[i][k] == ' ')
							{
								plansza2_1[i][k] = '0';
							}
							if (plansza2_2[i][k] == ' ')
							{
								plansza2_2[i][k] = '0';
							}
						}
					}
					//zapisywanie wszystkich danych do pliku
					plik << tryb_gry << "\t" << nick1 << "\t" << nick2 << "\t" << oddane_strzaly_1 << "\t" << oddane_strzaly_2 << "\t" << trafienia_1 << "\t" << trafienia_2 << "\n";
					for (int i = 0; i < 10; i++)
					{
						for (int k = 0; k < 10; k++)
						{
							plik << plansza1_1[i][k] << "\t";
						}
					}
					plik << endl;
					for (int i = 0; i < 10; i++)
					{
						for (int k = 0; k < 10; k++)
						{
							plik << plansza1_2[i][k] << "\t";
						}
					}
					plik << endl;
					for (int i = 0; i < 10; i++)
					{
						for (int k = 0; k < 10; k++)
						{
							plik << plansza2_1[i][k] << "\t";
						}
					}
					plik << endl;
					for (int i = 0; i < 10; i++)
					{
						for (int k = 0; k < 10; k++)
						{
							plik << plansza2_2[i][k] << "\t";
						}
					}
					plik << endl;
					plik.close();//zamkniecie pliku(po tej funkcji powrot do menu glownego)
					renderer->zapisano_pomyœlnie(Window);
					Sleep(1000);
					koniec_zapisu = true;
					Window->clear();
					break;
				}
			}
		}
	}
	
}

int rozgrywka::wczytywanie(FILE* plik, sf::RenderWindow* Window)//funkcja do wczytania stanu gry
{
	render_api* renderer = new render_api();
	rewind(plik);//przewiniecie pliku do poczatku
	//wczytanie wszystkich danych z pliku(ORAZ ICH KONTROLA !)
	fscanf(plik, "%d%s%s%d%d%d%d", &tryb_gry, nick1, nick2, &oddane_strzaly_1, &oddane_strzaly_2, &trafienia_1, &trafienia_2);
	if (tryb_gry != 1 && tryb_gry != 2)//sprawdzanie czy nie wczytano blednych danych
	{
		return 0;
	}
	//sprawdzanie czy do tablic nie wczytano nieprawidlowych danych(jezeli tak, zwracamy 0 co oznacza uszkodzony plik, w przeciwnym wypadku zwracamy 1 co oznacza prawidlowe wczytanie danych)
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			fscanf(plik, "%s", &plansza1_1[i][k]);
			if (plansza1_1[i][k] != '0' && plansza1_1[i][k] != '.' && plansza1_1[i][k] != '1' && plansza1_1[i][k] != '2' && plansza1_1[i][k] != '3' && plansza1_1[i][k] != '4' && plansza1_1[i][k] != 'x')
			{
				return 0;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			fscanf(plik, "%s", &plansza1_2[i][k]);
			if ((plansza1_2[i][k] != '0') && plansza1_2[i][k] != '.' && plansza1_2[i][k] != 'x')
			{
				return 0;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			fscanf(plik, "%s", &plansza2_1[i][k]);
			if (plansza2_1[i][k] != '0' && plansza2_1[i][k] != '.' && plansza2_1[i][k] != '1' && plansza2_1[i][k] != '2' && plansza2_1[i][k] != '3' && plansza2_1[i][k] != '4' && plansza2_1[i][k] != 'x')
			{
				return 0;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			fscanf(plik, "%s", &plansza2_2[i][k]);
			if (plansza2_2[i][k] != '0' && plansza2_2[i][k] != '.' && plansza2_2[i][k] != 'x')
			{
				return 0;
			}
		}
	}
	fclose(plik);//zamkniecie pliku
	//zamiana w tablicach symobli oznaczajacych puste miejsce na puste miejsca
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (plansza1_1[i][k] == '0')
			{
				plansza1_1[i][k] = ' ';
			}
			if (plansza1_2[i][k] == '0')
			{
				plansza1_2[i][k] = ' ';
			}
			if (plansza2_1[i][k] == '0')
			{
				plansza2_1[i][k] = ' ';
			}
			if (plansza2_2[i][k] == '0')
			{
				plansza2_2[i][k] = ' ';
			}
		}
	}
	renderer->zaczyna(Window, nick1);
	return 1;//zwrocenie 1 jezeli wczytano pomyslnie
}
