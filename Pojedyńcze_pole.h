#pragma once

class pojedyñcze_pole
{
public:
	unsigned int x, y;
	char symbol;

	pojedyñcze_pole() { };
	pojedyñcze_pole(int x, int y, char s) {
		this->x = x;
		this->y = y;
		this->symbol = s;
	}
};