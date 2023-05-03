#pragma once
#include "UtilityStructs.h"
#include "DialogWindow.h"
#include <vector>

class Organism;
class Human;

class World
{
private:
	int worldH, worldW, numOfOrganismes;
	coords pos;		// position where to draw world
	Human* human;
	std::vector<Organism*> org;
	Organism*** orgOnMap;
	char* mapToDraw;

	void nextTurn();
	void save();
	void deleteKilled();
	const void drawWorld() const;
	const void drawField() const;
	coords getPosOnMap(int x, int y) const;
	coords randomFreePosition(); 
public:
	World(int w, int h, int posX, int posY);

	void setHumanKilled();
	void setField(int x, int y, Organism* val);
	int getWidth() const;
	int getHeight() const;
	const coords getPos() const;
	Organism* getClosestOrgTo(std::string name, coords pos);
	Organism* getField(int x, int y) const;

	void startSimulation();
	void addOrganism(Organism* o);
	void addToDrawMap(const Organism& o, char color, char c=ASCII_SPACE);
	void spawnDefAnimals();
	Organism* checkCollision(const Organism& o);
	void load();

	~World();
};

