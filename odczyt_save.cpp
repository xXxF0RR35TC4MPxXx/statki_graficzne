#include "odczyt_save.h"

odczyt_save::odczyt_save(float width, float height)
{
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Nie ma takiego fontu!";
	}

}

odczyt_save::~odczyt_save() {

}
