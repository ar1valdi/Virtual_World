#include "plant.h"
#include "World.h"
#include "AllPlants.h"
#include <vector>
#include "InvalidType.h"

Plant::Plant(std::string name, int x, int y, int s, World* w) : Organism(name,x,y,s,0,w){}
void Plant::expand() {
	if (std::rand() % 100 + 1 > EXPAND_CHANCE)
		return;

	short checkedNum = 0;
	bool checked[4] = {false,false,false,false};
	coords sides[4] = { {0,1}, {0, -1}, {-1, 0}, {1,0} };
	coords newPos;
	
	// find accurate place for new plant
	bool foundValid = false;
	int side;

	for (int i = 0; i < 4; i++) {
		while (true) {
			side = std::rand() % 4;
			if (checked[side] == false) {
				newPos = { pos.x + sides[side].x, pos.y + sides[side].y };
				if (newPos.x >= 0 && newPos.x < world->getWidth() && newPos.y >= 0 && newPos.y < world->getHeight() && world->getField(newPos.x, newPos.y) == nullptr) {
					foundValid = true;
					i = 10;
					break;
				}
				checked[side] = true;
				break;
			}
		}
	}


	if (!foundValid) {
		return;
	}

	// add new plant
	Organism* newOrg;
	if (dynamic_cast<Grass*>(this))
		newOrg = new Grass(newPos.x, newPos.y, world);
	else if (dynamic_cast<Dandelion*>(this))
		newOrg = new Dandelion(newPos.x, newPos.y, world);
	else if (dynamic_cast<Guarana*>(this))
		newOrg = new Guarana(newPos.x, newPos.y, world);
	else if (dynamic_cast<Nightshade*>(this))
		newOrg = new Nightshade(newPos.x, newPos.y, world);
	else if (dynamic_cast<PineBorsch*>(this))
		newOrg = new PineBorsch(newPos.x, newPos.y, world);
	else {
		throw InvalidType();
		return;
	}

	world->addOrganism(newOrg);
	newOrg->blockTurn();
}
void Plant::action() {
	expand();
}
void Plant::collision(Organism& withWho) {
	DialogWindow::getInstance().printMsg(this->name + " eaten!");
	killByAnim();
}