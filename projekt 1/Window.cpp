#include "Window.h"
#include "conio2.h"
#include <string>
#include <iostream>
using namespace std;

void Window::drawWindow() {
	textcolor(FRAME_COLOR);
	string longSides = "";
	for (int i = 0; i < width*2; i++)
		longSides += ASCII_BLOCK;

	int drawX = (winPos.x - 1) * 2 + 1;

	gotoxy(drawX, winPos.y);
	cout << longSides;

	for (int i = 1; i < height - 1; i++) {
		gotoxy(drawX, winPos.y + i);
		cout << ASCII_BLOCK;
		cout << ASCII_BLOCK;
		gotoxy((winPos.x + width - 1)*2 - 1, winPos.y + i);
		cout << ASCII_BLOCK;
		cout << ASCII_BLOCK;
	}

	gotoxy(drawX, winPos.y + height - 1);
	cout << longSides;
	textcolor(WHITE);
}
void Window::changePos(int x, int y) {
	winPos.x = x;
	winPos.y = y;
}
Window::Window(int x, int y, int w, int h) :
	winPos({x,y}), height(h), width(w) {}