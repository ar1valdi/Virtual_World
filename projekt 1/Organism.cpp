#include <string>
#include "Animal.h"
#include "Human.h"
#include "World.h"
#include "DialogWindow.h"
#include <string>

Organism::Organism(std::string name, int x, int y, int strengh, int init, World* w) 
	: name(name), pos({ x,y }), strengh(strengh), initiative(init), world(w) {
	turnBlock = false;
}
const int Organism::getStrengh() const {
	return strengh;
}
const int Organism::getInit() const {
	return initiative;
}
const std::string Organism::getName() const {
	return name;
}
const coords Organism::getPos() const {
	return pos;
}
void Organism::blockTurn() {
	turnBlock = true;
}
void Organism::unblockTurn() {
	turnBlock = false;
}
const bool Organism::canMakeTurn() const {
	return !turnBlock;
}
void Organism::modifyStrengh(short modifyBy) {
	strengh += modifyBy;
}
void Organism::killByAnim() {
	blockTurn();
	pos = { -1,-1 };
	DialogWindow::getInstance().printMsg(this->name + " killed!", RED);
}
void Organism::killByPlant() {
	blockTurn();
	coords tempPos = pos;
	pos = { -1,-1 };

	world->setField(tempPos.x, tempPos.y, EMPTY_SPACE);

	DialogWindow::getInstance().printMsg(this->name + " killed!", RED);
}