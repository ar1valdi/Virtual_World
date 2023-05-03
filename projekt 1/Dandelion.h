#pragma once
#include "Plant.h"

class Dandelion : public Plant
{
public:
	Dandelion(int x, int y, World* w);
	void draw() const override;
	void action() override;
};

