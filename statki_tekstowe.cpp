
#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "dziedziczace.h"
#include "render_api.h"
#include "mainmenu.h"
#include "wybor_typu_gry.h"
#include "zapis_save_yes_no.h"
#include "odczyt_save.h"
#pragma warning(disable:4996)
#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822
using namespace std;


template<typename T>
T rozpoczecie_gry(void)//funkcja pokazujaca menu dla rozpoczecia gry
{
	T wybor_gracza;
	render_api* renderer = new render_api();
	renderer->wybor_typu_gry();
	while (scanf_s("%d", &wybor_gracza) != 1 || wybor_gracza < 1 || wybor_gracza > 3 || getchar() != '\n')//wczytywanie wyboru uzytkownika
	{
		renderer->opcja_nie_istnieje();
	}
	
	if (wybor_gracza == 1)//jezeli gracz wybral gre z komputerem
	{
		return 1;
	}
	else if (wybor_gracza == 2)//jezeli gracz wybral gre z innym graczem
	{
		return 2;
	}
	else if (wybor_gracza == 3)//jezeli gracz wybral powrot do glownego menu
	{
		return 3;
	}
	else//w wyjatkowej sytuacji koniec programu
	{
		renderer->error();
		exit(0);//awaryjne zakonczenie programu
	}
}




template<typename T>
T menu(RenderWindow *Window, render_api* renderer)//menu glowne
{
	T wybor_gracza;
	bool nowa_gra = true;
	mainmenu mainMenu(Window->getSize().x, Window->getSize().y);
	wybor_typu_gry wybor_typu_gry(Window->getSize().x, Window->getSize().y);
	zapis_save_yes_no zapis_yes_no(Window->getSize().x, Window->getSize().y);
	odczyt_save odczyt_save(Window->getSize().x, Window->getSize().y);
	//set background image
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::Texture MainTexture;
	MainTexture.loadFromFile("Texture/menu_background.jpg");
	background.setTexture(&MainTexture);

	RectangleShape Twórcy_background;
	Twórcy_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture AboutTexture;
	AboutTexture.loadFromFile("Texture/About_photo.png");
	Twórcy_background.setTexture(&AboutTexture);

	//photo to instructions
	RectangleShape Instrukcja_background;
	Instrukcja_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture InstructionTexture;
	InstructionTexture.loadFromFile("Texture/Instruction_photo.png");
	Instrukcja_background.setTexture(&InstructionTexture);

	//photo to instructions
	RectangleShape Wczytaj_save_background;
	Wczytaj_save_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture wczytaj_save_Texture;
	wczytaj_save_Texture.loadFromFile("Texture/podaj_nazwę_pliku.png");
	Wczytaj_save_background.setTexture(&wczytaj_save_Texture);

	RectangleShape błąd_odczytu_background;
	błąd_odczytu_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture błąd_odczytu_Texture;
	błąd_odczytu_Texture.loadFromFile("Texture/błąd_odczytu.png");
	błąd_odczytu_background.setTexture(&błąd_odczytu_Texture);

	RectangleShape plik_uszkodzony_background;
	plik_uszkodzony_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture plik_uszkodzony_Texture;
	plik_uszkodzony_Texture.loadFromFile("Texture/plik_uszkodzony.png");
	plik_uszkodzony_background.setTexture(&plik_uszkodzony_Texture);
	
	RectangleShape podaj_nick_background;
	podaj_nick_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture podaj_nick_Texture;
	podaj_nick_Texture.loadFromFile("Texture/podaj_nick.png");
	podaj_nick_background.setTexture(&podaj_nick_Texture);

	RectangleShape pusty_background;
	pusty_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	Texture pusty_texture;
	pusty_texture.loadFromFile("Texture/game_background.png");
	pusty_background.setTexture(&pusty_texture);

	rozgrywka* rozgrywka = NULL;
	Window->clear();
	Window->draw(background);
	mainMenu.draw(*Window);
	Window->display();
	while (Window->isOpen())
	{
		bool czy_exit = false;
		Event event;
		while (Window->pollEvent(event)&&!czy_exit)
		{
			if (event.type == sf::Event::MouseButtonPressed) {

			}
			if (event.type == Event::Closed)
			{
				Window->close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down) {
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return) {
					int x = mainMenu.MainMenuPressed();

					//gra
					if (x == 0) {
						while (Window->isOpen())
						{
							Event aevent;
							
							if (Window->pollEvent(aevent)) 
							{
								if (aevent.type == sf::Event::MouseButtonPressed) {

								}
								Window->clear();
								Window->draw(background);
								wybor_typu_gry.draw(*Window);
								Window->display();
								if (aevent.type == Event::Closed) {
									Window->close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Up) {
										wybor_typu_gry.MoveUp();
									}
									if (aevent.key.code == Keyboard::Down) {
										wybor_typu_gry.MoveDown();
									}
									if (aevent.key.code == Keyboard::Return) 
									{
										int y = wybor_typu_gry.WyborTypuGryPressed();
										if (y == 0) {
											bot bot;//inicjalizacja klasy dla gry gracz vs bot
											rozgrywka = &bot;
											if(nowa_gra)rozgrywka->ustawienia(Window);//wywolanie funkcji w ktorej uzytkownicy ustawiaja nicki i statki
											int licznik = 0, czy_zapisac = 0, czy_wygrana = 0;
											while (Window->isOpen() && !czy_exit)
											{
												nowa_gra = false;

												czy_wygrana = rozgrywka->gra(Window, renderer);//wywolanie funkcji do przeprowadzenia 1 tury gry i pobranie wartosci czy ktos wygral
												licznik++;//inkrementacja licznika do zapisania gry
												if (czy_wygrana == 1)//jezeli ktos wygral
												{
													nowa_gra = true;
													czy_exit = true;
													break;//powrot do menu glownego
												}
												if (licznik %4 == 0)//co 8 rund aby zapytac czy zapisac gre
												{
													//TUTAJ ZAPIS GRY
													Event xevent;
													Window->clear();
													Window->draw(pusty_background);
													zapis_yes_no.draw(*Window);
													Window->display();
													while (Window->waitEvent(xevent) && !czy_exit)
													{
														Window->clear();
														Window->draw(pusty_background);
														zapis_yes_no.draw(*Window);
														Window->display();
														if (xevent.type == sf::Event::MouseButtonPressed) {

														}
														
														if (xevent.type == Event::Closed) {
															Window->close();
														}
														if (xevent.type == Event::KeyPressed)
														{
															if (xevent.key.code == Keyboard::Left)
															{
																zapis_yes_no.MoveLeft();
															}
															if (xevent.key.code == Keyboard::Right)
															{
																zapis_yes_no.MoveRight();
															}
															if (xevent.key.code == Keyboard::Return)
															{
															
																if (zapis_yes_no.zapis_save_yes_no_pressed() == 0)
																{
																	rozgrywka->zapisywanie(Window);
																	czy_exit = true;
																	nowa_gra = true;
																	Window->clear();
																	break;
																}
																else if (zapis_yes_no.zapis_save_yes_no_pressed() == 1)
																{
																	Window->clear();
																	break;
																}
																licznik = 0;//zerowanie licznika
															}
														}
													}
												}
												
											}
										}
										else if (y == 1) 
										{ 
											gracz gracz;//inicjalizacja klasy dla gry gracz vs gracz
											rozgrywka = &gracz;
											if(nowa_gra)rozgrywka->ustawienia(Window);//wywolanie funkcji w ktorej uzytkownicy ustawiaja nicki i statki
											int licznik = 0, czy_zapisac = 0, czy_wygrana = 0;
											while (Window->isOpen() && !czy_exit)
											{
												nowa_gra = false;

												czy_wygrana = rozgrywka->gra(Window, renderer);//wywolanie funkcji do przeprowadzenia 1 tury gry i pobranie wartosci czy ktos wygral
												licznik++;//inkrementacja licznika do zapisania gry
												if (czy_wygrana == 1)//jezeli ktos wygral
												{
													nowa_gra = true;
													czy_exit = true;
													break;//powrot do menu glownego
												}
												if (licznik % 4 == 0)//co 8 rund aby zapytac czy zapisac gre
												{
													//TUTAJ ZAPIS GRY
													Event xevent;
													Window->clear();
													Window->draw(pusty_background);
													zapis_yes_no.draw(*Window);
													Window->display();
													while (Window->waitEvent(xevent) && !czy_exit)
													{
														Window->clear();
														Window->draw(pusty_background);
														zapis_yes_no.draw(*Window);
														Window->display();
														if (xevent.type == sf::Event::MouseButtonPressed) {

														}

														if (xevent.type == Event::Closed) {
															Window->close();
														}
														if (xevent.type == Event::KeyPressed)
														{
															if (xevent.key.code == Keyboard::Left)
															{
																zapis_yes_no.MoveLeft();
															}
															if (xevent.key.code == Keyboard::Right)
															{
																zapis_yes_no.MoveRight();
															}
															if (xevent.key.code == Keyboard::Return)
															{

																if (zapis_yes_no.zapis_save_yes_no_pressed() == 0)
																{
																	rozgrywka->zapisywanie(Window);
																	czy_exit = true;
																	nowa_gra = true;
																	Window->clear();
																	break;
																}
																else if (zapis_yes_no.zapis_save_yes_no_pressed() == 1)
																{
																	Window->clear();
																	break;
																}
																licznik = 0;//zerowanie licznika
															}
														}
													}
												}

											}
										}
										else {
											Window->clear();
											mainMenu.draw(*Window);
											Window->draw(background);
											Window->display();
											break;
										}
									}
								}
							}
						}
					}
					//save
					if (x == 1) {
						int rodzaj;
						char nazwa_pliku[101];
						
						sf::Text t;
						t.setFillColor(sf::Color::Black);
						sf::Font retrofont;
						retrofont.loadFromFile("retrofont.ttf");
						t.setFont(retrofont);
						t.setCharacterSize(50);
						t.setPosition(Vector2f(75, 250));
						string s;
						FILE* plik_zapis = NULL;
						bool pierwszy = true;

						while (Window->isOpen() && !czy_exit)
						{
							Event sevent;
							Window->clear();
							if (!pierwszy) { sleep(milliseconds(3000)); pierwszy = !pierwszy; }
							Window->draw(Wczytaj_save_background);
							Window->draw(t);
							Window->display();
							while (Window->pollEvent(sevent) && !czy_exit) {
								if (sevent.type == Event::Closed) {
									Window->close();
								}
								if (sevent.type == sf::Event::MouseButtonPressed) {

								}
								//przy wpisaniu jakiejś literki
								if (sevent.type == sf::Event::TextEntered) 
								{
									bool przejsc_dalej = false;
									//if escape
									if (sevent.text.unicode == 27) {
										Window->clear();
										mainMenu.draw(*Window);
										Window->draw(background);
										Window->display();
										czy_exit = true;
										break;
									}
									//if normalny_klawisz
									else if (sevent.text.unicode < 127 && 
										sevent.text.unicode >= 48 && 
										sevent.text.unicode != '\n' &&
										sevent.text.unicode != '\r' &&
										sevent.text.unicode != 10 &&
										sevent.text.unicode != '\v' &&
										sevent.text.unicode != 27 &&
										sevent.text.unicode != 32 &&
										sevent.text.unicode != '\b' &&
										t.getString().getSize() <16) 
										{
											s += static_cast<char>(sevent.text.unicode);
											t.setString(s); //dodaj do stringa
										
										}
									//jeżeli masz co usuwać, to usuń ostatnio dodany znak
									else if (t.getString().getSize() > 0 && sevent.text.unicode == '\b') {
										s.pop_back();
										t.setString(s);
									}
									else if ((sevent.text.unicode == '\n' || sevent.text.unicode == '\r') && t.getString().getSize() > 0 ) {
										string tempString = t.getString();
										int rodzaj = 0;
										const char* nazwa_pliku = tempString.c_str();
										plik_zapis = fopen(nazwa_pliku, "r");//otwarcie pliku do odczytu
										if (plik_zapis == NULL)
										{
											Window->draw(błąd_odczytu_background);
											s = "";
											pierwszy = false;
											t.setString(s);
											Window->draw(t);
											Window->display();

										}
										else 
										{
											fscanf(plik_zapis, "%d", &rodzaj);//wczytujemy z pliku jaki jest tryb gry(gracz vs gracz czy gracz vs komputer)
											if (rodzaj == 1)//jezeli tryb to gracz vs komputer
											{
												nowa_gra = false;
												bot bot;//inicjalizacja klasy dla gry gracz vs komputer
												rozgrywka = &bot;
											}
											else if (rodzaj == 2)//jezeli tryb to komputer vs komputer
											{
												nowa_gra = false;
												gracz gracz;//inicjalizacja klasy dla gry gracz vs gracz
												rozgrywka = &gracz;
											}
											else//w wyjatkowej sytuacji
											{
												Window->draw(plik_uszkodzony_background);
												Window->display();
												Sleep(3000);
												break;//powrot do menu glownego
											}
											

											
											int czy_wczytywanie_udane = 0;
											if(!nowa_gra)czy_wczytywanie_udane = rozgrywka->wczytywanie(plik_zapis, Window);//funkcja do wczytania stanu gry i pobranie wartosci czy udalo sie wczytac
											if (czy_wczytywanie_udane == 1){

												int licznik = 0, czy_zapisac = 0, czy_wygrana = 0;
												while (Window->isOpen() && !czy_exit)
												{
													czy_wygrana = rozgrywka->gra(Window, renderer);//wywolanie funkcji do przeprowadzenia 1 tury gry i pobranie wartosci czy ktos wygral
													licznik++;//inkrementacja licznika do zapisania gry
													if (czy_wygrana == 1)//jezeli ktos wygral
													{
														czy_exit = true;
														nowa_gra = true;
														break;//powrot do menu glownego
													}
													if (licznik % 4 == 0)//co 8 rund aby zapytac czy zapisac gre
													{
														//TUTAJ ZAPIS GRY
														Event xevent;
														Window->clear();
														Window->draw(pusty_background);
														zapis_yes_no.draw(*Window);
														Window->display();
														while (Window->waitEvent(xevent) && !czy_exit)
														{
															Window->clear();
															Window->draw(pusty_background);
															zapis_yes_no.draw(*Window);
															Window->display();
															if (xevent.type == sf::Event::MouseButtonPressed) {

															}

															if (xevent.type == Event::Closed) {
																Window->close();
															}
															if (xevent.type == Event::KeyPressed)
															{
																if (xevent.key.code == Keyboard::Left)
																{
																	zapis_yes_no.MoveLeft();
																}
																if (xevent.key.code == Keyboard::Right)
																{
																	zapis_yes_no.MoveRight();
																}
																if (xevent.key.code == Keyboard::Return)
																{

																	if (zapis_yes_no.zapis_save_yes_no_pressed() == 0)
																	{
																		rozgrywka->zapisywanie(Window);
																		czy_exit = true;
																		nowa_gra = true;
																		Window->clear();
																		break;
																	}
																	else if (zapis_yes_no.zapis_save_yes_no_pressed() == 1)
																	{
																		Window->clear();
																		break;
																	}
																	licznik = 0;//zerowanie licznika
																}
															}
														}
													}
													
												}
											}
											//przejdź dalej do ustawiania statków na planszy
										}
									}
								}
							}
						}
						
					}
					//instrukcje
					if (x == 2) {
						while (Window->isOpen())
						{
							Event aevent;
							if (Window->pollEvent(aevent)) {
								if (aevent.type == sf::Event::MouseButtonPressed) {

								}
								Window->clear();
								Window->draw(Instrukcja_background);
								Window->display();
								if (aevent.type == Event::Closed) {
									Window->close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										Window->clear();
										Window->draw(background);
										Window->display();
										break;
									}
								}
							}
						}
					}
					//twórcy
					if (x == 3) {
						while (Window->isOpen())
						{
							Event aevent;
							if (Window->pollEvent(aevent)) {
								if (aevent.type == sf::Event::MouseButtonPressed) {

								}
								Window->clear();
								Window->draw(Twórcy_background);
								Window->display();
								if (aevent.type == Event::Closed) {
									Window->close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										Window->clear();
										Window->draw(background);
										Window->display();
										break;
									}
								}
							}
						}
					}
					//wyjście
					if (x == 4)
					{
						Window->close();
						
						exit(0);
						return 4;
						break;
					}

				}
			}
			Window->clear();
			Window->draw(background);
			mainMenu.draw(*Window);
			Window->display();

		}
	}
}

void opis(void)
{
	//Wyswietlenie instrukcji dla gry
	render_api* renderer = new render_api();
	renderer->instrukcja();
}

int main()
{
	render_api* renderer = new render_api();
	sf::RenderWindow Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Main Menu", sf::Style::Default);

/*	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 920, 600, TRUE);*/

	srand((unsigned int)time(NULL));//liczby pseudolosowe
	while (Window.isOpen())//petla uruchamiajaca gre ciagle od nowa
	{
		menu<int>(&Window, renderer);//wywolanie funkcji menu(wybor gracza co chce zrobic)
	}
}
