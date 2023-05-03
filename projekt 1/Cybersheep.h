#pragma once
#include "Animal.h"

class Cybersheep : public Animal
{
public:
	Cybersheep(int x, int y, World* w);
	void draw() const override;
	void collision(Organism& withWho) override;
	void action() override;
};

