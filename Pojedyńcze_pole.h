#pragma once

class pojedyńcze_pole
{
public:
	unsigned int x, y;
	char symbol;

	pojedyńcze_pole() { };
	pojedyńcze_pole(int x, int y, char s) {
		this->x = x;
		this->y = y;
		this->symbol = s;
	}
};