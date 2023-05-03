#pragma once
#include "Organism.h"

class Plant : public Organism
{
protected:
	Plant(std::string name, int x, int y, int s, World* w);
public:
	virtual void expand();
	virtual void action() override;
	void collision(Organism& withWho) override;
};