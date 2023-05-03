#include "Wolf.h"
#include "conio2.h"
#include "World.h"

Wolf::Wolf(int x, int y, World* w) : Animal("Wolf", x, y, 9, 5, w) {}
void Wolf::draw() const {
	//gotoxy(world->getPos().x + pos.x * 2, world->getPos().y + pos.y);
	//textcolor(WOLF_COLOR);
	//putch(ASCII_BLOCK);
	//putch(ASCII_BLOCK);
	//textcolor(WHITE);
	
	world->addToDrawMap(*this, WOLF_COLOR);
}