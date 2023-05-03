#pragma once
#include "Animal.h"

class Fox : public Animal
{
public:
	Fox(int x, int y, World* w);
	void draw() const override;
	void moveRandomly() override;
};