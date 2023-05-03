#pragma once
#include "Plant.h"

class Grass : public Plant{
public:
	Grass(int x, int y, World* w);
	void draw() const override;
};