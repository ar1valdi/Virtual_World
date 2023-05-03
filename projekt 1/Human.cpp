#include "World.h"
#include "Human.h"
#include "conio2.h"
#include <conio.h>

Human::Human(int x, int y, World* w) : Animal("Human", x, y, 5, 4, w) {
	direction = { 1, 0 };
	spellCD = 0;
}
void Human::draw() const {
	world->addToDrawMap(*this, HUMAN_COLOR, ASCII_SMILE);
}
void Human::updateSpellCD() {
	if (spellCD != 0)
		spellCD--;
}
void Human::useSpell() {
	if (spellCD == 0) {
		DialogWindow::getInstance().printMsg("Spell activated!", BLACK, GREEN);
		DialogWindow::getInstance().drawMsgs();
		spellCD = 10;
	}
}
void Human::action() {
	world->setField(pos.x, pos.y, EMPTY_SPACE);
	if (pos.y + direction.y >= 0 && pos.y + direction.y < world->getHeight() &&
		pos.x + direction.x >= 0 && pos.x + direction.x < world->getWidth()) {
			
		updatePrevPos();
		Organism* collided = moveAndCollCheck(pos.x + direction.x, pos.y + direction.y);

		if (collided != nullptr && (dynamic_cast<Animal*>(collided) || spellCD <= 5))
			collision(*collided);
			
		else if (spellCD > 7) {
			if (pos.y + direction.y >= 0 && pos.y + direction.y < world->getHeight() &&
				pos.x + direction.x >= 0 && pos.x + direction.x < world->getWidth()) {

				updatePrevPos();
				moveTo(pos.x + direction.x, pos.y + direction.y);
			}
			collided = world->checkCollision(*this);

			if (collided != nullptr)
				collision(*collided);
		}

		else if (spellCD > 5) {
			int chance = std::rand() % 100 + 1;
			if (chance <= 50) {
				if (pos.y + direction.y >= 0 && pos.y + direction.y < world->getHeight() &&
					pos.x + direction.x >= 0 && pos.x + direction.x < world->getWidth()) {

					updatePrevPos();
					moveTo(pos.x + direction.x, pos.y + direction.y);
				}
			}
			collided = world->checkCollision(*this);

			if (collided != nullptr)
				collision(*collided);
		}
	}

	updateSpellCD();
	if (pos.x != -1)
		world->setField(pos.x, pos.y, this);
}
void Human::setDirection() {
	char in = _getch();
	if (in == KEY_UP)
		direction = { 0, -1 };
	else if (in == KEY_DOWN)
		direction = { 0, 1 };
	else if (in == KEY_RIGHT)
		direction = { 1, 0 };
	else if (in == KEY_LEFT)
		direction = { -1, 0 };
}
Organism* Human::moveAndCollCheck(int x, int y) {
	moveTo(x,y);
	return world->checkCollision(*this);
}
short Human::getSpellCD() {
	return spellCD;
}
Human::~Human() {
	world->setHumanKilled();
}