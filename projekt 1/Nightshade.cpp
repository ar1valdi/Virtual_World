#include "Nightshade.h"
#include "World.h"
#include "conio2.h"

Nightshade::Nightshade(int x, int y, World* w) : Plant("Nightshade", x, y, 99, w) {}
void Nightshade::draw() const {
	//coords where = world->getPosOnMap(pos.x, pos.y);
	//gotoxy(where.x, where.y);
	//textcolor(NIGHTSHADE_COLOR);
	//putch(ASCII_BLOCK);
	//putch(ASCII_BLOCK);
	//textcolor(WHITE);

	world->addToDrawMap(*this, NIGHTSHADE_COLOR);
}
void Nightshade::collision(Organism& withWho) {
	killByAnim();
	withWho.killByPlant();
}