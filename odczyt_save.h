#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define Max_wybor 3
class odczyt_save {
public:
	odczyt_save();
	odczyt_save(float width, float height);

	~odczyt_save();

private:
	Font font;
};