#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define Max_wybor 3
class wybor_typu_gry {
public:
	wybor_typu_gry();
	wybor_typu_gry(float width, float height);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int WyborTypuGryPressed() {
		return WyborTypuGrySelected;
	}
	~wybor_typu_gry();

private:
	int WyborTypuGrySelected;
	Font font;
	Text numer_typu_gry[Max_wybor];
};