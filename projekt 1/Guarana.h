#pragma once
#include "Plant.h"

class Guarana : public Plant
{
public:
	Guarana(int x, int y, World* w);
	void draw() const override;
	void collision(Organism& withWho) override;
};