#include "Animal.h"
#include <random>
#include "World.h"
#include "AllAnimals.h"
#include "Plant.h"
#include <vector>
#include "InvalidType.h"

Animal::Animal(std::string name, int x, int y, int strengh, int init, World* w) 
	: Organism(name, x,y,strengh, init ,w){
	prevPos = pos;
}
void Animal::moveRandomly() {
	std::vector<bool> checked = {false,false,false,false};
	//0 - left, 1 - right, 2 - up, 3 - down

	bool foundValid = false;
	while(!foundValid && std::find(checked.begin(), checked.end(), false) != checked.end()){
		int dir = rand() % 4;
		switch (dir) {
		case 0:
			if (pos.x - 1 < 0) {
				checked[0] = true;
				break;
			}
			foundValid = true;
			moveTo(pos.x - 1, pos.y);
			break;
		case 1:
			if (pos.x + 1 >= world->getWidth()) {
				checked[1] = true;
				break;
			}
			foundValid = true;
			moveTo(pos.x + 1, pos.y);
			break;
		case 2:
			if (pos.y - 1 < 0) {
				checked[2] = true;
				break;
			}
			foundValid = true;
			moveTo(pos.x, pos.y - 1);
			break;
		case 3:
			if (pos.y + 1 >= world->getHeight()) {
				checked[3] = true;
				break;
			}
			foundValid = true;
			moveTo(pos.x, pos.y + 1);
			break;
		}
	}
}
void Animal::updatePrevPos() {
	prevPos = pos;
}
void Animal::attack(Organism& who) {
	DialogWindow::getInstance().printMsg(this->name + " attacks " + who.getName() + "!", YELLOW);
	Animal* target = dynamic_cast<Animal*>(&who);
	if (target != nullptr) {
		Organism* loser;
		short result = target->reflected(*this);
		if (result == REFLECTED_KILL)
			loser = this;
		else if (result == NOT_REFLECTED)
			loser = &who;
		else if (result == RUNNED_AWAY)
			return;
		else {	// REFLECTED_MOVE
			moveBack();
			return;
		}
		loser->killByAnim();
	}
}
void Animal::collision(Organism& withWho) {
	if (getName() == withWho.getName()) {
		moveBack();
		world->setField(pos.x, pos.y, this);
		breed(withWho);
		withWho.blockTurn();
	}
	else if (dynamic_cast<Animal*>(&withWho)) {
		attack(withWho);
	}
	else if (dynamic_cast<Plant*>(&withWho)) {
		withWho.collision(*this);
	}
}
void Animal::breed(const Organism& withWho) {
	DialogWindow& dialog = DialogWindow::getInstance();
	bool foundSpace = false;
	coords newPos;
	coords from = pos;

	coords directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (auto& dir : directions) {
		int x = from.x + dir.x;
		int y = from.y + dir.y;
		if (x >= 0 && x < world->getWidth() && y >= 0 && y < world->getHeight() && world->getField(x,y) == EMPTY_SPACE) {
			newPos = { x, y };
			foundSpace = true;
			break;
		}
	}

	if (!foundSpace) {
		from = withWho.getPos();
		for (auto& dir : directions) {
			int x = from.x + dir.x;
			int y = from.y + dir.y;
			if (x >= 0 && x < world->getWidth() && y >= 0 && y < world->getHeight() && world->getField(x,y) == EMPTY_SPACE) {
				newPos = { x, y };
				foundSpace = true;
				break;
			}
		}
	}

	if (!foundSpace)
		return;

	Organism* newOrg;
	if (dynamic_cast<Sheep*>(this))
		newOrg = new Sheep(newPos.x, newPos.y, world);
	else if (dynamic_cast<Wolf*>(this))
		newOrg = new Wolf(newPos.x, newPos.y, world);
	else if (dynamic_cast<Fox*>(this))
		newOrg = new Fox(newPos.x, newPos.y, world);
	else if (dynamic_cast<Turtle*>(this))
		newOrg = new Turtle(newPos.x, newPos.y, world);
	else if (dynamic_cast<Antelope*>(this))
		newOrg = new Antelope(newPos.x, newPos.y, world);
	else if (dynamic_cast<Cybersheep*>(this))
		newOrg = new Cybersheep(newPos.x, newPos.y, world);
	else {
		throw InvalidType();
		return;
	}

	//if (this->getName() == "Antelope") {
	//	if (world->isOccupied(this)) {
	//		DialogWindow::getInstance().drawMsgs();
	//		int x = 0;
	//	}
	//}

	newOrg->blockTurn();
	world->addOrganism(newOrg);
	dialog.printMsg(this->name + " breeded! (" + std::to_string(newPos.x) + ", " + std::to_string(newPos.y) + ")", GREEN);
}
void Animal::moveTo(int x, int y) {
	pos = { x,y };
}
short Animal::reflected(const Organism& attacker) {
	if (attacker.getStrengh() < this->getStrengh())
		return REFLECTED_KILL;

	return NOT_REFLECTED;
}
void Animal::action() {
	world->setField(pos.x, pos.y, EMPTY_SPACE);
	updatePrevPos();

	moveRandomly();

	Organism* collided = world->checkCollision(*this);
	if (collided != nullptr)
		collision(*collided);

	if (pos.x != -1)
		world->setField(pos.x, pos.y, this);
}
void Animal::moveBack() {
	moveTo(prevPos.x, prevPos.y);
}
coords Animal::getPrevPos() {
	return prevPos;
}