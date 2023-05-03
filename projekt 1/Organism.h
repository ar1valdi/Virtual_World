#pragma once
#include "DialogWindow.h"
#include "UtilityStructs.h"
#include <string>
#include "World.h"

class Organism
{
private:
	friend void World::load();
protected:
	bool turnBlock;
	std::string name;
	int strengh, initiative;
	coords pos;
	World* world;
public:
	Organism(std::string name, int x, int y, int strengh, int init, World* w);	// todo better constructors
	virtual void collision(Organism& withWho) = 0;
	virtual void action() = 0;
	virtual void draw() const = 0;
	const int getStrengh() const;
	const int getInit() const;
	const std::string getName() const;
	const coords getPos() const;
	void blockTurn();
	void unblockTurn();
	const bool canMakeTurn() const;
	void modifyStrengh(short modifyBy);
	void killByAnim();
	void killByPlant();
	virtual void actionDoneAlways() {}	// most organismes dont have it, so i declare it empty but virtual
	virtual ~Organism() {}
};