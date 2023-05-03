#include "Dandelion.h"
#include "World.h"
#include "conio2.h"

Dandelion::Dandelion(int x, int y, World* w) : Plant("Dandelion", x, y, 0, w) {}
void Dandelion::draw() const {
	//coords where = world->getPosOnMap(pos.x, pos.y);
	//gotoxy(where.x, where.y);
	//textcolor(DANDELION_COLOR);
	//putch(ASCII_BLOCK);
	//putch(ASCII_BLOCK);
	//textcolor(WHITE);
	world->addToDrawMap(*this, DANDELION_COLOR);
}
void Dandelion::action() {
	expand();
	expand();
	expand();
}