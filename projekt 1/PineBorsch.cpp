#include "PineBorsch.h"
#include "World.h"
#include "Animal.h"
#include "conio2.h"
#include <vector>

PineBorsch::PineBorsch(int x, int y, World* w) : Plant("Pine_Borsch", x, y, 10, w) {}
void PineBorsch::draw() const {
	world->addToDrawMap(*this, PINE_BORSCH_COLOR);
}
void PineBorsch::action() {
	expand();
	killInRadius();
}
void PineBorsch::collision(Organism& withWho) {
	killByAnim();
	if (withWho.getName() == "Cybersheep")
		return;
	else
		withWho.killByPlant();
}
void PineBorsch::killInRadius() {
	std::vector<coords> sides = 
	{ {pos.x - 1, pos.y}, { pos.x + 1, pos.y }, { pos.x, pos.y - 1 }, { pos.x, pos.y + 1 },
	  {pos.x - 1, pos.y - 1}, { pos.x - 1, pos.y + 1}, { pos.x + 1, pos.y - 1 }, { pos.x + 1, pos.y + 1 }
	};
	for (auto side : sides) {
		if (side.x >= 0 && side.x < world->getWidth() && side.y >= 0 && side.y < world->getHeight()) {
			if (world->getField(side.x, side.y) != EMPTY_SPACE) {
				Animal* toKill = dynamic_cast<Animal*>(world->getField(side.x, side.y));
				if (toKill != nullptr && toKill->getName() != "Cybersheep")
					toKill->killByPlant();
			}
		}
	}
}
void PineBorsch::actionDoneAlways() {
	killInRadius();
}