#pragma once

class pojedy�cze_pole
{
public:
	unsigned int x, y;
	char symbol;

	pojedy�cze_pole() { };
	pojedy�cze_pole(int x, int y, char s) {
		this->x = x;
		this->y = y;
		this->symbol = s;
	}
};