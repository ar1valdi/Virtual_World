#include "Sheep.h"
#include "conio2.h"
#include "World.h"

Sheep::Sheep(int x, int y, World* w) : Animal("Sheep", x, y, 4, 4, w) {}
void Sheep::draw() const {
	world->addToDrawMap(*this, SHEEP_COLOR);
}