#include "Legend.h"
#include "conio2.h"
#include <iostream>
using namespace std;

Legend::Legend(int x, int y, int w, int h)
	: Window(x, y, w, h) {}
Legend& Legend::getInstance(int x, int y, int w, int h) {
	static Legend instance(x, y, w, h);
	return instance;
}
void Legend::drawLegend() {
	textcolor(SHEEP_COLOR);
	gotoxy(winPos.x * 2 + 1, winPos.y + 1);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Sheep";

	textcolor(WOLF_COLOR);
	gotoxy(winPos.x * 2+ 1, winPos.y + 2);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Wolf";

	textcolor(FOX_COLOR);
	gotoxy(winPos.x * 2 + 1, winPos.y + 3);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Fox";

	textcolor(TURTLE_COLOR);
	gotoxy(winPos.x * 2 + 1, winPos.y + 4);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Turtle";

	textcolor(ANTELOPE_COLOR);
	gotoxy(winPos.x * 2 + 1, winPos.y + 5);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Antelope";

	textcolor(CYBERSHEEP_COLOR);
	gotoxy(winPos.x * 2 + 1, winPos.y + 6);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Cybersheep";

	textcolor(GRASS_COLOR);
	gotoxy(winPos.x * 2 + 20, winPos.y + 1);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Grass";

	textcolor(DANDELION_COLOR);
	gotoxy(winPos.x * 2 + 20, winPos.y + 2);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Dandelion";;

	textcolor(GUARANA_COLOR);
	gotoxy(winPos.x * 2 + 20, winPos.y + 3);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Guarana";;

	textcolor(NIGHTSHADE_COLOR);
	gotoxy(winPos.x * 2 + 20, winPos.y + 4);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Nightshade";;

	textcolor(PINE_BORSCH_COLOR);
	gotoxy(winPos.x * 2 + 20, winPos.y + 5);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Pine Borsch";;

	textcolor(HUMAN_COLOR);
	gotoxy(winPos.x * 2 + 20, winPos.y + 6);
	cout << ASCII_BLOCK << ASCII_BLOCK << " - Human";
}