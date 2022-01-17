
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
T menu(RenderWindow *Window, render_api* renderer)//menu glowne
{

	bool nowa_gra = true;
	mainmenu mainMenu(Window->getSize().x, Window->getSize().y);
	wybor_typu_gry wybor_typu_gry(Window->getSize().x, Window->getSize().y);
	zapis_save_yes_no zapis_yes_no(Window->getSize().x, Window->getSize().y);
	odczyt_save odczyt_save(Window->getSize().x, Window->getSize().y);
	rozgrywka* rozgrywka = NULL;

	while (Window->isOpen())
	{
		bool czy_exit = false;
		Event event;
		renderer->main_menu(Window, mainMenu);
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
								renderer->wybor_typ_gry(Window, wybor_typu_gry);
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
													renderer->czy_zapisac_gre(Window, zapis_yes_no);
													while (Window->waitEvent(xevent) && !czy_exit)
													{
														renderer->czy_zapisac_gre(Window, zapis_yes_no);
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
												if (licznik % 4 == 0)//co 8 rund (4 tury) aby zapytac czy zapisac gre
												{
													//TUTAJ ZAPIS GRY
													Event xevent;
													renderer->czy_zapisac_gre(Window, zapis_yes_no);
													while (Window->waitEvent(xevent) && !czy_exit)
													{
														renderer->czy_zapisac_gre(Window, zapis_yes_no);
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
											renderer->main_menu(Window, mainMenu);
											break;
										}
									}
								}
							}
						}
					}
					//save
					if (x == 1) {
						sf::Text text;
						text.setFillColor(sf::Color::Black);
						sf::Font retrofont;
						retrofont.loadFromFile("retrofont.ttf");
						text.setFont(retrofont);
						text.setCharacterSize(50);
						text.setPosition(Vector2f(75, 250));
						string napis;
						FILE* plik_zapis = NULL;
						bool pierwszy = true;

						while (Window->isOpen() && !czy_exit)
						{
							Event sevent;
							Window->clear();
							if (!pierwszy) { sleep(milliseconds(3000)); pierwszy = !pierwszy; }
							renderer->wczytaj_save_background_method(Window, text);
							while (Window->pollEvent(sevent) && !czy_exit) 
							{
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
										renderer->main_menu(Window, mainMenu);
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
										text.getString().getSize() <16) 
										{
											napis += static_cast<char>(sevent.text.unicode);
											text.setString(napis); //dodaj do stringa
										
										}
									//jeżeli masz co usuwać, to usuń ostatnio dodany znak
									else if (text.getString().getSize() > 0 && sevent.text.unicode == '\b') {
										napis.pop_back();
										text.setString(napis);
									}
									else if ((sevent.text.unicode == '\n' || sevent.text.unicode == '\r') && text.getString().getSize() > 0 ) {
										string tempString = text.getString();
										int rodzaj = 0;
										const char* nazwa_pliku = tempString.c_str();
										plik_zapis = fopen(nazwa_pliku, "r");//otwarcie pliku do odczytu
										if (plik_zapis == NULL)
										{
											
											napis = "";
											pierwszy = false;
											text.setString(napis);
											renderer->błąd_odczytu_save(Window, text);

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
												renderer->plik_uszkodzony(Window);
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
														renderer->czy_zapisac_gre(Window, zapis_yes_no);
														while (Window->waitEvent(xevent) && !czy_exit)
														{
															renderer->czy_zapisac_gre(Window, zapis_yes_no);
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
								renderer->instrukcja(Window);
								if (aevent.type == Event::Closed) {
									Window->close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										renderer->draw_empty_background(Window);
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
								renderer->twórcy(Window);
								if (aevent.type == Event::Closed) {
									Window->close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										renderer->draw_empty_background(Window);
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
			renderer->main_menu(Window, mainMenu);

		}
	}
}


int main()
{
	render_api* renderer = new render_api();
	sf::RenderWindow Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Statki!", sf::Style::Default);

	srand((unsigned int)time(NULL));//liczby pseudolosowe
	while (Window.isOpen())
	{
		menu<int>(&Window, renderer);//wywolanie funkcji menu(wybor gracza co chce zrobic)
	}
	return 0;
}
