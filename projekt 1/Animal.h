#pragma once
#include "Organism.h"
#include "DialogWindow.h";
#include <string>

class Animal : public Organism
{
	friend void World::load();
protected:
	coords prevPos;

	void breed(const Organism& withWhog);
	virtual void action() override;
	void collision(Organism& withWho) override;
	virtual void moveRandomly();
	void updatePrevPos();
	void moveBack();
	void moveTo(int x, int y);
	Animal(std::string name, int x, int y, int strengh, int init, World* w);
	virtual void attack(Organism& who);

	virtual ~Animal() {}
public:
	virtual short reflected(const Organism& attacker);
	coords getPrevPos();
};

