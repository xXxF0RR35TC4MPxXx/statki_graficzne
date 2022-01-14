#pragma once
class render_api {
public:
	render_api();
	virtual void przerwy(int);//funkcja polimorficzna do ustawienia rzeczy przed rozpoczeciem stzrelania (nick i statki)
	virtual void instrukcja();
	virtual void error();
	virtual void main_menu();
	virtual void wybor_typu_gry();
	virtual void opcja_nie_istnieje();
	virtual void Czyszczenie_Bufora();
	virtual void niestety_nie_ma_takiej_opcji();
	virtual void podaj_nazwê_save();
	virtual void save_error();
	virtual void save_read_error();
	virtual void plik_uszkodzony();
	virtual void thx_4_playing();
	virtual void czy_zapisac_gre();
	virtual void nie_ma_opcji_zapisu();
	virtual void pudlo(int);
	virtual void trafienie();
	virtual void przeka¿_komputer();
	virtual std::string podaj_nick(sf::RenderWindow* Window);
	virtual std::string podaj_nick2(sf::RenderWindow* Window);
	virtual void b³êdny_nick();
	virtual void komputer_ustawia_statki(sf::RenderWindow* Window);
	virtual void ruch_wykonuje_komputer();
	virtual void clear_screen();
	virtual void ustawkolor(char);
	virtual void kolorplanszyprzeciwnika(char);
	virtual void resetkolor();
	virtual void wypisz_plansze(char plansza[10][10]);
	virtual int czy_wygrana(char plansza[10][10]);//funkcja sprawdza czy ktos juz nie zatopil wszystkich statkow

	virtual int czy_moze_tu_stac(unsigned int wspolrzedna_x, unsigned int wspolrzedna_y, char plansza[10][10]);//funkcja sprawdza czy na podanych koordynatach moze stac statek
	//renderowanie obu plansz
	virtual void legenda_planszy();
	virtual void render_planszy(char plansza1[10][10], char plansza2[10][10], sf::RenderWindow*);
	virtual void render_planszy_gra(char plansza1[10][10], char plansza2[10][10],char plansza2_1[10][10], char plansza2_2[10][10], sf::RenderWindow*, int typ, unsigned int& oddane_strzaly_1, unsigned int&  oddane_strzaly_2, unsigned int& trafienia_1, unsigned int& trafienia_2);
	virtual void b³êdna_wspó³rzêdna();
	virtual void podaj_wspó³rzêdne();
	virtual void nie_ma_opcji();
	virtual void ustawiasz_statek(int, int, sf::RenderWindow*, int, sf::Text);
	virtual void nie_mo¿na_postawiæ_statku();
	virtual void podaj_orientacjê();
	virtual void podaj_nazwê_pliku_do_zapisania_gry();
	virtual void nie_uda³o_siê();
	virtual void zapisano_pomyœlnie();
	virtual void wczytano_pomyœlnie();
	virtual void zaczyna(char*);
	unsigned int temp_hit1=0, temp_hit2=0, temp_shot1=0, temp_shot2=0;
};
