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

void rozgrywka::pokaz_plansze(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow* Window)//funkcja tworzy i pokazuje plansze z przeslanych dwoch tablic dwuwymiarowych
{
	render_api* renderer = new render_api();
	//cout << "pokaz_plansze\n";
	renderer->render_planszy(plansza1, plansza2, Window);
	//cout << "Wyrenderowano calosc!\n";
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
void rozgrywka::podawanie_pozycji(unsigned int* wspol_x, unsigned int* wspol_y)//funkcja pobiera od uzytkownika wspolrzedne X i Y dla statku
{
	//render_api* renderer = new render_api();
	while (scanf("%d%d", wspol_x, wspol_y) != 2 || *wspol_x > 10 || *wspol_y > 10 || getchar() != '\n')
	{
		//renderer->b³êdna_wspó³rzêdna();
	}
}

void rozgrywka::wygrana(sf::RenderWindow* Window, char nick[])//funkcja ktora wyswietla statystyki po wygranej jednej ze stron
{
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture background_texture;
	background_texture.loadFromFile("Texture/game_background.png");
	background.setTexture(&background_texture);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	//tekst "Twoje pole:"
	sf::Text game_over_text;
	game_over_text.setFillColor(sf::Color::Black);
	game_over_text.setFont(retrofont);
	game_over_text.setCharacterSize(38);
	game_over_text.setPosition(sf::Vector2f(230, 100));
	game_over_text.setString("KONIEC GRY");

	sf::Text wygral;
	wygral.setFillColor(sf::Color::Black);
	wygral.setFont(retrofont);
	wygral.setCharacterSize(38);
	wygral.setPosition(sf::Vector2f(145, 160));
	wygral.setString("Wygral: " + std::string(nick));

	sf::Text player1_name;
	player1_name.setFillColor(sf::Color::Black);
	player1_name.setFont(retrofont);
	player1_name.setCharacterSize(38);
	player1_name.setPosition(sf::Vector2f(76, 300));
	player1_name.setString(nick1);

	sf::Text player2_name;
	player2_name.setFillColor(sf::Color::Black);
	player2_name.setFont(retrofont);
	player2_name.setCharacterSize(38);
	player2_name.setPosition(sf::Vector2f(76, 400));
	player2_name.setString(nick2);

	sf::Text oddane_strzaly_player1_text;
	oddane_strzaly_player1_text.setFillColor(sf::Color::Black);
	oddane_strzaly_player1_text.setFont(retrofont);
	oddane_strzaly_player1_text.setCharacterSize(38);
	oddane_strzaly_player1_text.setPosition(sf::Vector2f(500, 300));
	oddane_strzaly_player1_text.setString(to_string(oddane_strzaly_1));

	sf::Text oddane_strzaly_player2_text;
	oddane_strzaly_player2_text.setFillColor(sf::Color::Black);
	oddane_strzaly_player2_text.setFont(retrofont);
	oddane_strzaly_player2_text.setCharacterSize(38);
	oddane_strzaly_player2_text.setPosition(sf::Vector2f(500, 400));
	oddane_strzaly_player2_text.setString(to_string(oddane_strzaly_2));

	sf::Text trafienia_player1_text;
	trafienia_player1_text.setFillColor(sf::Color::Black);
	trafienia_player1_text.setFont(retrofont);
	trafienia_player1_text.setCharacterSize(38);
	trafienia_player1_text.setPosition(sf::Vector2f(680, 300));
	trafienia_player1_text.setString(to_string(trafienia_1));

	sf::Text trafienia_player2_text;
	trafienia_player2_text.setFillColor(sf::Color::Black);
	trafienia_player2_text.setFont(retrofont);
	trafienia_player2_text.setCharacterSize(38);
	trafienia_player2_text.setPosition(sf::Vector2f(680, 400));
	trafienia_player2_text.setString(to_string(trafienia_2));

	sf::Text shots_text;
	shots_text.setFillColor(sf::Color::Black);
	shots_text.setFont(retrofont);
	shots_text.setCharacterSize(18);
	shots_text.setPosition(sf::Vector2f(460, 240));
	shots_text.setString("Strzalów:");

	sf::Text hit_text;
	hit_text.setFillColor(sf::Color::Black);
	hit_text.setFont(retrofont);
	hit_text.setCharacterSize(18);
	hit_text.setPosition(sf::Vector2f(630, 240));
	hit_text.setString("Trafieñ:");

	sf::Text enter_text;
	enter_text.setFillColor(sf::Color::Black);
	enter_text.setFont(retrofont);
	enter_text.setCharacterSize(22);
	enter_text.setPosition(sf::Vector2f(86, 500));
	enter_text.setString("Wcisnij ENTER, aby kontynuowac");

	//cout << "rozgrywka::wygrana()\n";
	render_api* renderer = new render_api();
	bool wyszedl_z_okna = false;
	sf::Event wyjdzdomenuevent;
	if (trafienia_1 != 0 && trafienia_2 != 0) {
		while (Window->isOpen() && !wyszedl_z_okna) {
			while (Window->pollEvent(wyjdzdomenuevent)) {
				if (wyjdzdomenuevent.type == sf::Event::MouseButtonPressed) {

				}
				//std::cout << "MA PRZEKAZAC KOMPUTER";
				Window->draw(background);
				Window->draw(game_over_text);
				Window->draw(wygral);
				Window->draw(player1_name);
				Window->draw(player2_name);
				Window->draw(oddane_strzaly_player1_text);
				Window->draw(oddane_strzaly_player2_text);
				Window->draw(trafienia_player1_text);
				Window->draw(trafienia_player2_text);
				Window->draw(hit_text);
				Window->draw(shots_text);
				Window->draw(enter_text);

				Window->display();
				if (wyjdzdomenuevent.type == sf::Event::KeyPressed) {
					if (wyjdzdomenuevent.key.code == sf::Keyboard::Return)
					{
						//std::cout << "WCISNIETO ENTER KIEDY MA PRZEKAZAC KOMPUTER";
						wyszedl_z_okna = true;
						Window->clear();
						break;
					}
				}
			}
		}
	}
	
}

int rozgrywka::strzal(char plansza1[10][10], char plansza2[10][10])//funkcja odopowiadaja za strzal gracza
{
	render_api* renderer = new render_api();
	unsigned int wspolrzedna_x, wspolrzedna_y;
	renderer->podaj_wspó³rzêdne();
	podawanie_pozycji(&wspolrzedna_x, &wspolrzedna_y);//wywolanie funkcji gdzie uzytkownik podaje wspolrzedne X i Y gdzie chce strzelic
	renderer->clear_screen();
	//sprawdzanie gdzie strzelil uzytkownik
	/*if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == ' ')//jezeli uzytkownik strzelil w puste pole
	{
		//ustawianie oznaczenia strzalu w odpowiednich tablicach
		plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = '.';
		plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = '.';
		return 0;
	}
	else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == 'x' || plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '.')//jezeli uzytkownik strzelil w juz strzelane pole
	{
		return 2;
	}
	else//jezeli uzytkownik trafil
	{
		//umieszczanie odpowiednich oznaczen statkow na tablicach
		if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '1')//jezeli statek jednomasztowy
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = '1';
		}
		else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '2')//jezeli statek dwumasztowy
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = '2';
		}
		else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '3')//jezeli statek trzymasztowy
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = '3';
		}
		else if (plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] == '4')//jezeli statek czteromasztowy
		{
			plansza2[wspolrzedna_y - 1][wspolrzedna_x - 1] = '4';
		}
		plansza1[wspolrzedna_y - 1][wspolrzedna_x - 1] = 'x';//ustawienie na planszy drugiego gracza oznaczenia, ze przeciwnik trafil
		return 1;
	}*/
	return 1;
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
	//cout << "ustawienie statkow\n";
	unsigned int wspolrzedna_x, wspolrzedna_y, orientacja;
	int odpowiedz = 0;
	pokaz_plansze(plansza1, plansza2, Window);//pokazanie odpowiedniej planszy
}

void rozgrywka::zapisywanie(sf::RenderWindow* Window)//funkcja do zapisania stanu gry
{
	fstream plik;
	render_api* renderer = new render_api();
	string nazwa_pliku;
	sf::Text t;
	t.setFillColor(sf::Color::Black);
	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");
	t.setFont(retrofont);
	t.setCharacterSize(50);
	t.setPosition(sf::Vector2f(75, 250));
	string s;
	sf::RectangleShape Wczytaj_save_background;
	Wczytaj_save_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture wczytaj_save_Texture;
	wczytaj_save_Texture.loadFromFile("Texture/podaj_nazwê_pliku.png");
	Wczytaj_save_background.setTexture(&wczytaj_save_Texture);
	bool koniec_zapisu = false;
	sf::RectangleShape zapis_udany_background;
	zapis_udany_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture zapis_udany_texture;
	zapis_udany_texture.loadFromFile("Texture/zapis_udany.png");
	zapis_udany_background.setTexture(&zapis_udany_texture);
	while (Window->isOpen() && !koniec_zapisu)
	{
		sf::Event sevent;
		Window->clear();
		Window->draw(Wczytaj_save_background);
		Window->draw(t);
		Window->display();
		while (Window->pollEvent(sevent)) {
			if (sevent.type == sf::Event::Closed) {
				Window->close();
			}
			if (sevent.type == sf::Event::MouseButtonPressed) {

			}
			//przy wpisaniu jakiejœ literki
			if (sevent.type == sf::Event::TextEntered)
			{
				bool przejsc_dalej = false;
				//if normalny_klawisz
				if (sevent.text.unicode < 127 &&
					sevent.text.unicode >= 48 &&
					sevent.text.unicode != '\n' &&
					sevent.text.unicode != '\r' &&
					sevent.text.unicode != 10 &&
					sevent.text.unicode != '\v' &&
					sevent.text.unicode != 27 &&
					sevent.text.unicode != 32 &&
					sevent.text.unicode != '\b' &&
					t.getString().getSize() < 16)
				{
					//cout << static_cast<char>(sevent.text.unicode);
					s += static_cast<char>(sevent.text.unicode);
					//cout << s + "\n";
					t.setString(s); //dodaj do stringa

				}
				//je¿eli masz co usuwaæ, to usuñ ostatnio dodany znak
				else if (t.getString().getSize() > 0 && sevent.text.unicode == '\b') {
					s.pop_back();
					//cout << s + "\n";
					//s.erase(s.size() - 1, 1);
					t.setString(s);
				}
				else if ((sevent.text.unicode == '\n' || sevent.text.unicode == '\r') && t.getString().getSize() > 0) {
					plik.open(s, ios::out);
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
					Window->clear();
					Window->draw(zapis_udany_background);
					Window->display();
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
	sf::Text text_odliczania;
	sf::Text text_odliczania2;

	sf::Font retrofont;
	retrofont.loadFromFile("retrofont.ttf");

	text_odliczania.setFillColor(sf::Color::Black);
	text_odliczania.setFont(retrofont);
	text_odliczania.setCharacterSize(30);
	text_odliczania.setPosition(sf::Vector2f(136, 157));
	text_odliczania.setString("");

	text_odliczania2.setFillColor(sf::Color::Black);
	text_odliczania2.setFont(retrofont);
	text_odliczania2.setCharacterSize(24);
	text_odliczania2.setPosition(sf::Vector2f(294, 400));
	text_odliczania2.setString("");
	sf::RectangleShape wczytaj_save_background;
	wczytaj_save_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture wczytaj_save_texture;
	wczytaj_save_texture.loadFromFile("Texture/game_background.png");
	wczytaj_save_background.setTexture(&wczytaj_save_texture);

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
	int count = 3;
	while (Window->isOpen() && count > 0) {
		Window->clear();
		text_odliczania.setString("Rozpoczyna: " + string(nick1));
		text_odliczania2.setString("Start za " + to_string(count));
		Window->draw(wczytaj_save_background);
		Window->draw(text_odliczania);
		Window->draw(text_odliczania2);
		Window->display();
		count--;
		sf::sleep(sf::milliseconds(1000));
	}
	return 1;//zwrocenie 1 jezeli wczytano pomyslnie
}
