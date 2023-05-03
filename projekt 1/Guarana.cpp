#include "Guarana.h"
#include "World.h"
#include "conio2.h"

Guarana::Guarana(int x, int y, World* w) : Plant("Guarana", x, y, 0, w) {}
void Guarana::draw() const {
	world->addToDrawMap(*this, GUARANA_COLOR);
}
void Guarana::collision(Organism& withWho) {
	withWho.modifyStrengh(3);
	killByAnim();
}