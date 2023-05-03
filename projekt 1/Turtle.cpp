#include "Turtle.h"
#include "World.h"
#include "conio2.h"

Turtle::Turtle(int x, int y, World* w) : Animal("Turtle", x, y, 2, 1, w) {}
void Turtle::draw() const{
	world->addToDrawMap(*this, TURTLE_COLOR);
}
void Turtle::action() {
	int chance = std::rand() % 100 + 1;
	if (chance <= 75)
		return; 
	
	world->setField(pos.x, pos.y, EMPTY_SPACE);

	updatePrevPos();
	moveRandomly();
	Organism* collided = world->checkCollision(*this);

	if (collided != nullptr)
		collision(*collided);

	if (pos.x != -1)
		world->setField(pos.x, pos.y, this);
}
short Turtle::reflected(const Organism& attacker) {
	if (attacker.getStrengh() < 5)
		return REFLECTED_MOVE;

	if (this->strengh > attacker.getStrengh())
		return REFLECTED_KILL;

	return NOT_REFLECTED;
}
