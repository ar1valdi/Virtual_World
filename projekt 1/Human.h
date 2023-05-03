#pragma once
#include "Animal.h"

class Human : public Animal
{
private:
	coords direction;
	short spellCD;
	friend void World::load();

	void updateSpellCD();
	Organism* moveAndCollCheck(int x, int y);
public:

	Human(int x, int y, World* w);
	void draw() const override;
	void action() override;
	void useSpell();
	short getSpellCD();
	void setDirection();
	~Human();
};

