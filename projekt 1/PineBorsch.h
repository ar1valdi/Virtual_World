#pragma once
#include "Plant.h"

class PineBorsch : public Plant
{
	void killInRadius();
public:
	PineBorsch(int x, int y, World* w);
	void draw() const override;
	void action() override;
	void collision(Organism& withWho) override;
	void actionDoneAlways() override;
};

