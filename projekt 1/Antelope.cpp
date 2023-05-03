#include "Antelope.h"
#include "conio2.h"
#include "Plant.h"
#include "World.h"

Antelope::Antelope(int x, int y, World* w) : Animal("Antelope", x, y, 4,4, w) {}

void Antelope::draw() const {
	world->addToDrawMap(*this, ANTELOPE_COLOR);
}
void Antelope::action() {
	ogPos = { pos.x, pos.y };
	world->setField(pos.x, pos.y, EMPTY_SPACE);
	updatePrevPos();
	moveRandomly();

	Organism* collided = world->checkCollision(*this);

	if (collided != nullptr && dynamic_cast<Animal*>(collided)) {
		collision(*collided);
	}
	else {
		short deltaX = pos.x - prevPos.x;
		short deltaY = pos.y - prevPos.y;
		updatePrevPos();

		if (deltaY == 1 && pos.y + 1 < world->getHeight())
			moveTo(pos.x, pos.y + 1);
		else if (deltaY == -1 && pos.y - 1 >= 0)
			moveTo(pos.x, pos.y - 1);
		else if (deltaX == 1 && pos.x + 1 < world->getWidth())
			moveTo(pos.x + 1, pos.y);
		else if (deltaX == -1 && pos.x - 1 >= 0)
			moveTo(pos.x - 1, pos.y);

		collided = world->checkCollision(*this);
		if (collided != nullptr)
			collision(*collided);
	}

	if (pos.x != -1)
		world->setField(pos.x, pos.y, this);
}
void Antelope::collision(Organism& withWho) {
	if (getName() == withWho.getName()) {
		if (pos.x == 0 && pos.y == 0)
			int x = 0;

		moveBack();
		
		// antelope can 'jump over' flowers so
		// when it goes back onto it, it has to be eaten
		Organism* collided = world->checkCollision(*this);

		if(collided != nullptr)
			collision(*collided);

		if(pos.x != -1)
		//moveTo(ogPos.x, ogPos.y);
		world->setField(pos.x, pos.y, this);
		
		breed(withWho);
		withWho.blockTurn();
	}
	else if (dynamic_cast<Animal*>(&withWho)) {
		short chance = std::rand() % 100 + 1;
		if (chance > 50) {
			attack(withWho);
		}
		else {
			if (!moveToSafePlace())
				attack(withWho);
		}
	}
	else if (dynamic_cast<Plant*>(&withWho)) {
		withWho.collision(*this);
	}
}
void Antelope::attack(Organism& who) {
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
			moveTo(ogPos.x, ogPos.y);
			return;
		}
		loser->killByAnim();
	}
}
bool Antelope::moveToSafePlace() {
	bool escaped = false;
	if (pos.y + 1 < world->getHeight() && world->getField(pos.x, pos.y + 1) == EMPTY_SPACE) {
		updatePrevPos();
		escaped = true;
		moveTo(pos.x, pos.y + 1);
	}
	else if (pos.y - 1 >= 0 && world->getField(pos.x, pos.y - 1) == EMPTY_SPACE) {
		updatePrevPos();
		escaped = true;
		moveTo(pos.x, pos.y - 1);
	}
	else if (pos.x + 1 < world->getWidth() && world->getField(pos.x + 1, pos.y) == EMPTY_SPACE) {
		updatePrevPos();
		escaped = true;
		moveTo(pos.x + 1, pos.y);
	}
	else if (pos.x - 1 >= 0 && world->getField(pos.x - 1, pos.y) == EMPTY_SPACE) {
		updatePrevPos();
		escaped = true;
		moveTo(pos.x - 1, pos.y);
	}

	if (escaped) {
		DialogWindow::getInstance().printMsg("Antelope has moved to safe place!", YELLOW);
		world->setField(pos.x, pos.y, this);
		return true;
	}

	DialogWindow::getInstance().printMsg("Antelope couldn't find safe place!", YELLOW);
	return false;
}
short Antelope::reflected(const Organism& attacker) {
	short chance = std::rand() % 100 + 1;

	if (chance > 50) {
		if (moveToSafePlace()) {
			return RUNNED_AWAY;
		}
	}
	
	if (this->strengh > attacker.getStrengh())
		return REFLECTED_KILL;
	
	return NOT_REFLECTED;
}