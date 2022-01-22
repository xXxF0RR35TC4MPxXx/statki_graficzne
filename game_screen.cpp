#include "game_screen.h"
#include <math.h>
#define WINDOW_HEIGHT 613
#define WINDOW_WIDTH 822
#define TILE_WIDTH 30
#define TILE_HEIGHT 30


game_screen::game_screen(float width, float height, RenderWindow* Window)
{
	this->Window = Window;
	PoleSelected = 0;
}

game_screen::~game_screen() {

}


void game_screen::draw(RenderWindow& window, Plansza plansza1, Plansza plansza2, int typ) {
	Texture sprite_pustego_pola_texture;
	sprite_pustego_pola_texture.loadFromFile("Texture/empty_tile.png");
	Texture sprite_1_tile;
	sprite_1_tile.loadFromFile("Texture/1_tile.png");
	Texture sprite_2_tile;
	sprite_2_tile.loadFromFile("Texture/2_tile.png");
	Texture sprite_3_tile;
	sprite_3_tile.loadFromFile("Texture/3_tile.png");
	Texture sprite_4_tile;
	sprite_4_tile.loadFromFile("Texture/4_tile.png");
	Texture sprite_hit_tile;
	sprite_hit_tile.loadFromFile("Texture/hit_tile.png");
	Texture sprite_miss_tile;
	sprite_miss_tile.loadFromFile("Texture/missed_tile.png");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int p2 = floor(PoleSelected / 10);
			int p1 = PoleSelected % 10;
			RectangleShape sprite_pustego_pola;
			sprite_pustego_pola.setSize(Vector2f(30, 30));
			if (plansza1.pola_planszy[i][j]->symbol == '1')
			{
				sprite_pustego_pola.setTexture(&sprite_1_tile);
			}
			else if (plansza1.pola_planszy[i][j]->symbol == '2')
			{
				sprite_pustego_pola.setTexture(&sprite_2_tile);
			}
			else if (plansza1.pola_planszy[i][j]->symbol == '3')
			{
				sprite_pustego_pola.setTexture(&sprite_3_tile);
			}
			else if (plansza1.pola_planszy[i][j]->symbol == '4')
			{
				sprite_pustego_pola.setTexture(&sprite_4_tile);
			}
			else if (plansza1.pola_planszy[i][j]->symbol == 'x')
			{
				sprite_pustego_pola.setTexture(&sprite_hit_tile);
			}
			else if (plansza1.pola_planszy[i][j]->symbol == '.')
			{
				sprite_pustego_pola.setTexture(&sprite_miss_tile);
			}
			else{
				sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
			}
			
			sprite_pustego_pola.setPosition(69 + (i * TILE_WIDTH), 160 + (j * TILE_HEIGHT));
			Window->draw(sprite_pustego_pola);
			std::string var = "Wyrenderowano: plansza1[" + std::to_string(i) + "][" + std::to_string(j) + "] == " + std::to_string(plansza1.pola_planszy[i][j]->symbol) + "\n";

			//cout << var;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			RectangleShape sprite_pustego_pola;
			sprite_pustego_pola.setSize(Vector2f(30, 30));
			if (plansza2.pola_planszy[i][j]->symbol == 'x')
			{
				sprite_pustego_pola.setTexture(&sprite_hit_tile);
			}
			else if (plansza2.pola_planszy[i][j]->symbol == '.')
			{
				sprite_pustego_pola.setTexture(&sprite_miss_tile);
			}
			else {
				sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
			}
			sprite_pustego_pola.setPosition(450 + (j * TILE_WIDTH), 160 + (i * TILE_HEIGHT));
			Window->draw(sprite_pustego_pola);
			std::string var = "Wyrenderowano: plansza2[" + std::to_string(i) + "][" + std::to_string(j) + "] == " + std::to_string(plansza1.pola_planszy[i][j]->symbol) + "\n";
			//cout << var;
		}
	}
	RectangleShape spritepodpola;
	if (typ == 1) {
		int p1 = floor(PoleSelected / 10);
		int p2 = PoleSelected % 10;

		spritepodpola.setFillColor(Color::White);
		spritepodpola.setSize(Vector2f(30, 30));
		spritepodpola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
	}
	else if (typ == 2) {
		int p1 = floor(PoleSelected / 10);
		int p2 = PoleSelected % 10;

		spritepodpola.setFillColor(Color::White);
		spritepodpola.setSize(Vector2f(30, 30));
		spritepodpola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
	}
	
	Window->draw(spritepodpola);
}

void game_screen::MoveUp(Plansza plansza, int typ) {
	
	if (PoleSelected > 9)
	{
		Texture sprite_pustego_pola_texture;
		sprite_pustego_pola_texture.loadFromFile("Texture/empty_tile.png");
		Texture sprite_1_tile;
		sprite_1_tile.loadFromFile("Texture/1_tile.png");
		Texture sprite_2_tile;
		sprite_2_tile.loadFromFile("Texture/2_tile.png");
		Texture sprite_3_tile;
		sprite_3_tile.loadFromFile("Texture/3_tile.png");
		Texture sprite_4_tile;
		sprite_4_tile.loadFromFile("Texture/4_tile.png");
		Texture sprite_hit_tile;
		sprite_hit_tile.loadFromFile("Texture/hit_tile.png");
		Texture sprite_miss_tile;
		sprite_miss_tile.loadFromFile("Texture/missed_tile.png");
		RectangleShape sprite_pustego_pola;
		sprite_pustego_pola.setSize(Vector2f(30, 30));
		int p2 = floor(PoleSelected/10);
		int p1 = PoleSelected % 10;
		char temp_char = plansza.pola_planszy[p1][p2]->symbol;
		if (temp_char == '1')
		{
			sprite_pustego_pola.setTexture(&sprite_1_tile);
		}
		else if (temp_char == '2')
		{
			sprite_pustego_pola.setTexture(&sprite_2_tile);
		}
		else if (temp_char == '3')
		{
			sprite_pustego_pola.setTexture(&sprite_3_tile);
		}
		else if (temp_char == '4')
		{
			sprite_pustego_pola.setTexture(&sprite_4_tile);
		}
		else if (temp_char == 'x')
		{
			sprite_pustego_pola.setTexture(&sprite_hit_tile);
		}
		else if (temp_char == '.')
		{
			sprite_pustego_pola.setTexture(&sprite_miss_tile);
		}
		else {
			sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
		}
		RectangleShape spritepodpola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected -= 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			
			spritepodpola.setFillColor(Color::White);
			spritepodpola.setSize(Vector2f(30, 30));
			spritepodpola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected -= 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			spritepodpola.setFillColor(Color::White);
			spritepodpola.setSize(Vector2f(30, 30));
			spritepodpola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		
		Window->draw(spritepodpola);
	}
}

void game_screen::MoveDown(Plansza plansza, int typ) {
	if (PoleSelected < 90) {
		Texture sprite_pustego_pola_texture;
		sprite_pustego_pola_texture.loadFromFile("Texture/empty_tile.png");
		Texture sprite_1_tile;
		sprite_1_tile.loadFromFile("Texture/1_tile.png");
		Texture sprite_2_tile;
		sprite_2_tile.loadFromFile("Texture/2_tile.png");
		Texture sprite_3_tile;
		sprite_3_tile.loadFromFile("Texture/3_tile.png");
		Texture sprite_4_tile;
		sprite_4_tile.loadFromFile("Texture/4_tile.png");
		Texture sprite_hit_tile;
		sprite_hit_tile.loadFromFile("Texture/hit_tile.png");
		Texture sprite_miss_tile;
		sprite_miss_tile.loadFromFile("Texture/missed_tile.png");
		RectangleShape sprite_pustego_pola;
		sprite_pustego_pola.setSize(Vector2f(30, 30));
		int p1 = floor(PoleSelected / 10);
		int p2 = PoleSelected % 10;
		char temp_char = plansza.pola_planszy[p1][p2]->symbol;
		if (temp_char == '1')
		{
			sprite_pustego_pola.setTexture(&sprite_1_tile);
		}
		else if (temp_char == '2')
		{
			sprite_pustego_pola.setTexture(&sprite_2_tile);
		}
		else if (temp_char == '3')
		{
			sprite_pustego_pola.setTexture(&sprite_3_tile);
		}
		else if (temp_char == '4')
		{
			sprite_pustego_pola.setTexture(&sprite_4_tile);
		}
		else if (temp_char == 'x')
		{
			sprite_pustego_pola.setTexture(&sprite_hit_tile);
		}
		else if (temp_char == '.')
		{
			sprite_pustego_pola.setTexture(&sprite_miss_tile);
		}
		else {
			sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
		}
		

		RectangleShape spritepodpola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected += 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			spritepodpola.setFillColor(Color::White);
			spritepodpola.setSize(Vector2f(30, 30));
			spritepodpola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected += 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			spritepodpola.setFillColor(Color::White);
			spritepodpola.setSize(Vector2f(30, 30));
			spritepodpola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		
		Window->draw(spritepodpola);
	}
}

void game_screen::MoveLeft(Plansza plansza, int typ) {

	if (PoleSelected % 10 != 0) {
		Texture sprite_pustego_pola_texture;
		sprite_pustego_pola_texture.loadFromFile("Texture/empty_tile.png");
		Texture sprite_1_tile;
		sprite_1_tile.loadFromFile("Texture/1_tile.png");
		Texture sprite_2_tile;
		sprite_2_tile.loadFromFile("Texture/2_tile.png");
		Texture sprite_3_tile;
		sprite_3_tile.loadFromFile("Texture/3_tile.png");
		Texture sprite_4_tile;
		sprite_4_tile.loadFromFile("Texture/4_tile.png");
		Texture sprite_hit_tile;
		sprite_hit_tile.loadFromFile("Texture/hit_tile.png");
		Texture sprite_miss_tile;
		sprite_miss_tile.loadFromFile("Texture/missed_tile.png");
		RectangleShape sprite_pustego_pola;
		sprite_pustego_pola.setSize(Vector2f(30, 30));
		int p1 = floor(PoleSelected / 10);
		int p2 = PoleSelected % 10;
		char temp_char = plansza.pola_planszy[p1][p2]->symbol;
		if (temp_char == '1')
		{
			sprite_pustego_pola.setTexture(&sprite_1_tile);
		}
		else if (temp_char == '2')
		{
			sprite_pustego_pola.setTexture(&sprite_2_tile);
		}
		else if (temp_char == '3')
		{
			sprite_pustego_pola.setTexture(&sprite_3_tile);
		}
		else if (temp_char == '4')
		{
			sprite_pustego_pola.setTexture(&sprite_4_tile);
		}
		else if (temp_char == 'x')
		{
			sprite_pustego_pola.setTexture(&sprite_hit_tile);
		}
		else if (temp_char == '.')
		{
			sprite_pustego_pola.setTexture(&sprite_miss_tile);
		}
		else {
			sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
		}
		
		RectangleShape sprite_podswietlonego_pola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected-- ;
		p1 = floor(PoleSelected / 10);
		p2 = PoleSelected % 10;
		
		sprite_podswietlonego_pola.setFillColor(Color::White);
		sprite_podswietlonego_pola.setSize(Vector2f(30, 30));
		sprite_podswietlonego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected--;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;

			sprite_podswietlonego_pola.setFillColor(Color::White);
			sprite_podswietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podswietlonego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		Window->draw(sprite_podswietlonego_pola);
	}
}

void game_screen::MoveRight(Plansza plansza, int typ) {
	if (PoleSelected % 10 != 9) {
		Texture sprite_pustego_pola_texture;
		sprite_pustego_pola_texture.loadFromFile("Texture/empty_tile.png");
		Texture sprite_1_tile;
		sprite_1_tile.loadFromFile("Texture/1_tile.png");
		Texture sprite_2_tile;
		sprite_2_tile.loadFromFile("Texture/2_tile.png");
		Texture sprite_3_tile;
		sprite_3_tile.loadFromFile("Texture/3_tile.png");
		Texture sprite_4_tile;
		sprite_4_tile.loadFromFile("Texture/4_tile.png");
		Texture sprite_hit_tile;
		sprite_hit_tile.loadFromFile("Texture/hit_tile.png");
		Texture sprite_miss_tile;
		sprite_miss_tile.loadFromFile("Texture/missed_tile.png");
		RectangleShape sprite_pustego_pola;
		sprite_pustego_pola.setSize(Vector2f(30, 30));
		int p1 = floor(PoleSelected / 10);
		int p2 = PoleSelected % 10;
		char temp_char = plansza.pola_planszy[p1][p2]->symbol;
		if (temp_char == '1')
		{
			sprite_pustego_pola.setTexture(&sprite_1_tile);
		}
		else if (temp_char == '2')
		{
			sprite_pustego_pola.setTexture(&sprite_2_tile);
		}
		else if (temp_char == '3')
		{
			sprite_pustego_pola.setTexture(&sprite_3_tile);
		}
		else if (temp_char == '4')
		{
			sprite_pustego_pola.setTexture(&sprite_4_tile);
		}
		else if (temp_char == 'x')
		{
			sprite_pustego_pola.setTexture(&sprite_hit_tile);
		}
		else if (temp_char == '.')
		{
			sprite_pustego_pola.setTexture(&sprite_miss_tile);
		}
		else {
			sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
		}
		RectangleShape spritepodpola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected++;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			spritepodpola.setSize(Vector2f(30, 30));
			spritepodpola.setFillColor(Color::White);
			spritepodpola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected++;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			spritepodpola.setSize(Vector2f(30, 30));
			spritepodpola.setFillColor(Color::White);
			spritepodpola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		Window->draw(spritepodpola);
	}
}