#pragma once
#include "Animal.h"

class Antelope : public Animal
{
private:
	coords ogPos;
	// return true if ran, false if there was no place
	bool moveToSafePlace();
	void attack(Organism& who) override;
public:
	Antelope(int x, int y, World* w);
	void draw() const override;
	void action() override;
	void collision(Organism& withWho) override; 
	short reflected(const Organism& attacker) override;
};

