#include "game_screen.h"
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


void game_screen::draw(RenderWindow& window, char plansza1[10][10], char plansza2[10][10], int typ) {
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
			if (plansza1[i][j] == '1')
			{
				sprite_pustego_pola.setTexture(&sprite_1_tile);
			}
			else if (plansza1[i][j] == '2')
			{
				sprite_pustego_pola.setTexture(&sprite_2_tile);
			}
			else if (plansza1[i][j] == '3')
			{
				sprite_pustego_pola.setTexture(&sprite_3_tile);
			}
			else if (plansza1[i][j] == '4')
			{
				sprite_pustego_pola.setTexture(&sprite_4_tile);
			}
			else if (plansza1[i][j] == 'x')
			{
				sprite_pustego_pola.setTexture(&sprite_hit_tile);
			}
			else if (plansza1[i][j] == '.')
			{
				sprite_pustego_pola.setTexture(&sprite_miss_tile);
			}
			else{
				sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
			}
			
			sprite_pustego_pola.setPosition(69 + (i * TILE_WIDTH), 160 + (j * TILE_HEIGHT));
			Window->draw(sprite_pustego_pola);
			std::string var = "Wyrenderowano: plansza1[" + std::to_string(i) + "][" + std::to_string(j) + "] == " + std::to_string(plansza1[i][j]) + "\n";

			//cout << var;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			RectangleShape sprite_pustego_pola;
			sprite_pustego_pola.setSize(Vector2f(30, 30));
			if (plansza2[i][j] == 'x')
			{
				sprite_pustego_pola.setTexture(&sprite_hit_tile);
			}
			else if (plansza2[i][j] == '.')
			{
				sprite_pustego_pola.setTexture(&sprite_miss_tile);
			}
			else {
				sprite_pustego_pola.setTexture(&sprite_pustego_pola_texture);
			}
			sprite_pustego_pola.setPosition(450 + (j * TILE_WIDTH), 160 + (i * TILE_HEIGHT));
			Window->draw(sprite_pustego_pola);
			std::string var = "Wyrenderowano: plansza2[" + std::to_string(i) + "][" + std::to_string(j) + "] == " + std::to_string(plansza1[i][j]) + "\n";
			//cout << var;
		}
	}
	RectangleShape sprite_podœwietlonego_pola;
	if (typ == 1) {
		int p1 = floor(PoleSelected / 10);
		int p2 = PoleSelected % 10;

		sprite_podœwietlonego_pola.setFillColor(Color::White);
		sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
		sprite_podœwietlonego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
	}
	else if (typ == 2) {
		int p1 = floor(PoleSelected / 10);
		int p2 = PoleSelected % 10;

		sprite_podœwietlonego_pola.setFillColor(Color::White);
		sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
		sprite_podœwietlonego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
	}
	
	Window->draw(sprite_podœwietlonego_pola);
}

void game_screen::MoveUp(char plansza[10][10], int typ) {
	
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
		char temp_char = plansza[p1][p2];
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
		RectangleShape sprite_podœwietlonego_pola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected -= 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			
			sprite_podœwietlonego_pola.setFillColor(Color::White);
			sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podœwietlonego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected -= 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			sprite_podœwietlonego_pola.setFillColor(Color::White);
			sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podœwietlonego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		
		Window->draw(sprite_podœwietlonego_pola);
	}
}

void game_screen::MoveDown(char plansza[10][10], int typ) {
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
		char temp_char = plansza[p1][p2];
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
		

		RectangleShape sprite_podœwietlonego_pola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected += 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			sprite_podœwietlonego_pola.setFillColor(Color::White);
			sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podœwietlonego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected += 10;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			sprite_podœwietlonego_pola.setFillColor(Color::White);
			sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podœwietlonego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		
		Window->draw(sprite_podœwietlonego_pola);
	}
}

void game_screen::MoveLeft(char plansza[10][10], int typ) {

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
		char temp_char = plansza[p1][p2];
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
		
		RectangleShape sprite_podœwietlonego_pola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected-- ;
		p1 = floor(PoleSelected / 10);
		p2 = PoleSelected % 10;
		
		sprite_podœwietlonego_pola.setFillColor(Color::White);
		sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
		sprite_podœwietlonego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected--;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;

			sprite_podœwietlonego_pola.setFillColor(Color::White);
			sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podœwietlonego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		Window->draw(sprite_podœwietlonego_pola);
	}
}

void game_screen::MoveRight(char plansza[10][10], int typ) {
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
		char temp_char = plansza[p1][p2];
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
		RectangleShape sprite_podœwietlonego_pola;
		if (typ == 1) {
			sprite_pustego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected++;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podœwietlonego_pola.setFillColor(Color::White);
			sprite_podœwietlonego_pola.setPosition(69 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		else if (typ == 2) {
			sprite_pustego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
			PoleSelected++;
			p1 = floor(PoleSelected / 10);
			p2 = PoleSelected % 10;
			sprite_podœwietlonego_pola.setSize(Vector2f(30, 30));
			sprite_podœwietlonego_pola.setFillColor(Color::White);
			sprite_podœwietlonego_pola.setPosition(450 + (p2 * TILE_WIDTH), 160 + (p1 * TILE_HEIGHT));
		}
		Window->draw(sprite_podœwietlonego_pola);
	}
}