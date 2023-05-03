#pragma once
#include "Plant.h"

class Nightshade : public Plant
{
public:
	Nightshade(int x, int y, World* w);
	void draw() const override;
	void collision(Organism& withWho) override;
};

