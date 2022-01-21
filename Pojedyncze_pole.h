#pragma once

class pojedyncze_pole
{
public:
	unsigned int x, y;
	char symbol;

	pojedyncze_pole() { };
	pojedyncze_pole(int x, int y, char s) {
		this->x = x;
		this->y = y;
		this->symbol = s;
	}
};