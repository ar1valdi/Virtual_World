#pragma once
#include "Animal.h"

class Turtle : public Animal
{
public:
	Turtle(int x, int y, World* w);
	void draw() const override;
	void action() override;
	short reflected(const Organism& attacker) override;
};

