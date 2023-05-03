#include "Cybersheep.h"
#include "conio2.h"
#include "World.h"
#include "PineBorsch.h"

Cybersheep::Cybersheep(int x, int y, World* w) : Animal("Cybersheep", x, y, 11, 4, w) {}

void Cybersheep::draw() const {
	world->addToDrawMap(*this, CYBERSHEEP_COLOR);
}
void Cybersheep::collision(Organism& withWho) {
	if (getName() == withWho.getName()) {
		moveBack();
		breed(withWho);
		withWho.blockTurn();
	}
	else if (dynamic_cast<Animal*>(&withWho)) {
		attack(withWho);
	}
	else if (dynamic_cast<Plant*>(&withWho)) {
		if (dynamic_cast<PineBorsch*>(&withWho)) {
			withWho.killByAnim();
			return;
		}
		withWho.collision(*this);
	}
}
void Cybersheep::action() {
	world->setField(pos.x, pos.y, nullptr);
	Organism* closestBorsch = world->getClosestOrgTo("Pine_Borsch", pos);

	// if there is no borsch act as normal sheep
	if (closestBorsch == nullptr) {
		Animal::action();
		return;
	}

	updatePrevPos();
	
	if (abs(pos.x - closestBorsch->getPos().x) > abs(pos.y - closestBorsch->getPos().y)) {
		if (pos.x > closestBorsch->getPos().x)
			moveTo(pos.x - 1, pos.y);
		else
			moveTo(pos.x + 1, pos.y);
	}
	else {
		if (pos.y > closestBorsch->getPos().y)
			moveTo(pos.x, pos.y - 1);
		else
			moveTo(pos.x, pos.y + 1);
	}

	Organism* collided = world->checkCollision(*this);

	if (collided != nullptr)
		collision(*collided);

	if(pos.x != -1)
		world->setField(pos.x, pos.y, this);
}