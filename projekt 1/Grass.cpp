#include "Grass.h"
#include "World.h"
#include "conio2.h"

Grass::Grass(int x, int y, World* w) : Plant("Grass", x, y, 0, w) {}
void Grass::draw() const{
	world->addToDrawMap(*this, GRASS_COLOR);
}