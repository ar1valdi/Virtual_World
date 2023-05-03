#include "World.h"
#include "consts.h"
#include "conio2.h"
#include <conio.h>
#include <iostream>
#include "operators.h"
#include "AppControl.h"
#include <fstream>

#include "Animal.h"
#include "Plant.h"
#include "AllAnimals.h"
#include "AllPlants.h"

#include "PosOutOfMap.h"
#include "InvalidType.h"
#include "SpawnOnTakenSpace.h"

World::World(int posX, int posY, int w, int h) {
	orgOnMap = new Organism**[w];

	for (int i = 0; i < w; i++) {
		orgOnMap[i] = new Organism*[h];
		for (int j = 0; j < h; j++) {
			orgOnMap[i][j] = EMPTY_SPACE;
		}
	}

	human = nullptr;
	mapToDraw = new char [h*w*4];
	pos.x = posX;
	pos.y = posY;
	worldH = h;
	worldW = w;
	numOfOrganismes = 0;
}

void World::addToDrawMap(const Organism& o, char color, char c) {
	mapToDraw[o.getPos().y * worldW * 4 + o.getPos().x * 4] = c;
	mapToDraw[o.getPos().y * worldW * 4 + o.getPos().x * 4 + 1] = 16*color;
	mapToDraw[o.getPos().y * worldW * 4 + o.getPos().x * 4 + 2] = c;
	mapToDraw[o.getPos().y * worldW * 4 + o.getPos().x * 4 + 3] = 16*color;
}

const void World::drawWorld() const {
	for (int i = 0; i < worldH; i++) {
		for (int j = 0; j < worldW * 4; j += 4) {
			int id = i * worldW * 4 + j;
			for (int z = 0; z < 4; z += 2) {
				mapToDraw[id + z] = ASCII_DOTS;
				mapToDraw[id + z + 1] = 16 * DEF_COLOR_OUT + DEF_COLOR_IN;
			}
		}
	}

	for (int i = 0; i < numOfOrganismes; i++) {
		org[i]->draw();
	}

	puttext(pos.x, pos.y, pos.x + worldW*2 - 1, pos.y + worldH - 1, mapToDraw);

	DialogWindow::getInstance().drawMsgs();
}
coords World::randomFreePosition() {
	if (numOfOrganismes == worldW * worldH)
		return { -1,-1 };

	bool foundPlace = false;
	coords newPos;
	while (!foundPlace) {
		newPos.x = std::rand() % worldW;
		newPos.y = std::rand() % worldH;
		if (orgOnMap[newPos.x][newPos.y] == nullptr)
			foundPlace = true;
	}
	return newPos;
}
void World::spawnDefAnimals() {
	int sizeOfMap = worldW * worldH;
	coords newPos;

	// Sheep
	for (int i = 0; i < SHEEP_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Sheep(newPos.x, newPos.y, this));
	}

	// Wolf
	for (int i = 0; i < WOLF_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Wolf(newPos.x, newPos.y, this));
	}

	// Turtle
	for (int i = 0; i < TURTLE_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Turtle(newPos.x, newPos.y, this));
	}

	// Antelope
	for (int i = 0; i < ANTELOPE_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Antelope(newPos.x, newPos.y, this));
	}

	// Cybersheep
	for (int i = 0; i < CYBERSHEEP_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Cybersheep(newPos.x, newPos.y, this));
	}

	// Fox
	for (int i = 0; i < FOX_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Fox(newPos.x, newPos.y, this));
	}

	// Grass
	for (int i = 0; i < GRASS_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Grass(newPos.x, newPos.y, this));
	}

	// Dandelion
	for (int i = 0; i < DANDELION_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Dandelion(newPos.x, newPos.y, this));
	}

	// Guarana
	for (int i = 0; i < GUARANA_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Guarana(newPos.x, newPos.y, this));
	}

	// Nightshade
	for (int i = 0; i < NIGHTSHADE_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new Nightshade(newPos.x, newPos.y, this));
	}

	// Pine Borsch
	for (int i = 0; i < PINE_BORSCH_NUMBER; i++) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		addOrganism(new PineBorsch(newPos.x, newPos.y, this));
	}
	
	if (SPAWN_HUMAN) {
		newPos = randomFreePosition();
		if (newPos.x == -1) return;
		human = new Human(newPos.x, newPos.y, this);
		addOrganism(human);
	}
}
void World::addOrganism(Organism* o) {
	bool added = 0;
	coords p = o->getPos();

	if (p.x < 0 || p.x >= worldW || p.y < 0 || p.y >= worldH)
		throw PosOutOfMap();
	if (orgOnMap[p.x][p.y] != EMPTY_SPACE)
		throw SpawnOnTakenSpace();

	if (numOfOrganismes == 0) {
		org.push_back(o);
		numOfOrganismes++;
		orgOnMap[o->getPos().x][o->getPos().y] = o;
		return;
	}

	for (int i = 0; i < numOfOrganismes; i++){
		if (org[i]->getInit() < o->getInit()) {
			org.insert(org.begin() + i, o);
			added = 1;
			break;
		}
	}

	// if the organism has the lowest initative and has not been added
	if (!added) {
		org.push_back(o);
	}

	orgOnMap[o->getPos().x][o->getPos().y] = o;
	numOfOrganismes++;
}
void World::nextTurn() {
	for (int i = 0; i < numOfOrganismes; i++) {
		if (org[i]->canMakeTurn())
			org[i]->action();
		else
			org[i]->actionDoneAlways();
	}
	
	for (int i = 0; i < numOfOrganismes; i++)
		org[i]->unblockTurn();

	deleteKilled();

	drawWorld();
}
void World::deleteKilled() {
	int deleted = 0;

	for (int i = 0; i < org.size(); i++) {
		if (org[i]->getPos().x == -1) {
			delete org[i];
			org.erase(org.begin() + i);
			numOfOrganismes--;
			i--;
		}
	}
}
Organism* World::getClosestOrgTo(std::string name, coords from) {
	Organism* closest = nullptr;

	// this is longer than longest manhattan
	// distance in the world
	int minDistance = worldW + worldH;

	for (int i = 0; i < numOfOrganismes; i++) {
		if (org[i]->getName() == name) {
			int dis = abs(org[i]->getPos().x - from.x) + abs(org[i]->getPos().y - from.y);
			if (dis < minDistance) {
				closest = org[i];
				minDistance = dis;
			}
		}
	}

	return closest;
}
Organism* World::checkCollision(const Organism& o) {
	return orgOnMap[o.getPos().x][o.getPos().y];
}
const void World::drawField() const {
	gotoxy(worldW*2+DIALOG_WINDOW_W*2 + 10, 1);
	for (int i = 0; i < worldH; i++) {
		for (int j = 0; j < worldW; j++) {
			if (orgOnMap[j][i] == EMPTY_SPACE)
				std::cout << '_';
			else
				std::cout << '#';
		}
		gotoxy(worldW * 2 + DIALOG_WINDOW_W*2 + 10, 1 + i + 1);
	}
}
int World::getHeight() const {
	return worldH;
}
int World::getWidth() const {
	return worldW;
}
const coords World::getPos() const {
	return pos;
}
void World::setField(int x, int y, Organism* val) {
	if (x != -1 && y != -1)
		orgOnMap[x][y] = val;
}
Organism* World::getField(int x, int y) const{
	return orgOnMap[x][y];
}
coords World::getPosOnMap(int x, int y) const {
	return { pos.x + x * 2, pos.y + y };
}
World::~World() {
	while (org.size() != 0) {
		delete org[0];
		org.erase(org.begin());
	}

	for (int i = 0; i < worldW; i++)
		delete[] orgOnMap[i];
	delete[] orgOnMap;

	delete[] mapToDraw;
}
void World::save() {
	using namespace std;
	fstream saveFile;
	saveFile.open("save", ios::out);

	if (!saveFile.good()) {
		DialogWindow::getInstance().printErr("Can't create file to save into!");
		DialogWindow::getInstance().drawMsgs();
		return;
	}

	deleteKilled();
	saveFile << worldW << ' ' << worldH;
	for (int i = 0; i < numOfOrganismes; i++) {
		saveFile << '\n' << org[i]->getName() << '\n';
		saveFile << org[i]->getPos().x << ' ';
		saveFile << org[i]->getPos().y << '\n';
		saveFile << !org[i]->canMakeTurn() << '\n';
		saveFile << org[i]->getStrengh();
		Animal* anim = dynamic_cast<Animal*>(org[i]);
		if (anim) {
			saveFile << '\n' << anim->getPrevPos().x << ' ';
			saveFile << anim->getPrevPos().y;
			Human* hum = dynamic_cast<Human*>(anim);
			if (hum)
				saveFile << '\n' << hum->getSpellCD();
		}
	}


	DialogWindow::getInstance().printMsg("Saved Sucessfully!", WHITE, LIGHTCYAN);
	DialogWindow::getInstance().drawMsgs();
}
void World::load(){
	using namespace std;
	fstream saveFile("save", ios::in);

	if (!saveFile.good()) {
		DialogWindow::getInstance().printErr("Can't open file to load!");
		DialogWindow::getInstance().drawMsgs();
		return;
	}

	human = nullptr;
	while (org.size() != 0) {
		delete org[0];
		org.erase(org.begin());
	}

	for (int i = 0; i < worldW; i++)
		delete[] orgOnMap[i];
	delete[] orgOnMap;

	delete[] mapToDraw;
	numOfOrganismes = 0;

	saveFile >> worldW;
	saveFile >> worldH;

	mapToDraw = new char[worldW * worldH * 4];
	orgOnMap = new Organism **[worldW];
	for (int i = 0; i < worldW; i++) {
		orgOnMap[i] = new Organism *[worldH];
		for (int j = 0; j < worldH; j++) {
			orgOnMap[i][j] = EMPTY_SPACE;
		}
	}

	string newName;
	coords newPos;
	coords newPrevPos;
	bool newBlocked;

	while (saveFile >> newName) {
		Organism* newOrg;

		saveFile >> newPos.x;
		saveFile >> newPos.y;
		
		if (newName == "Sheep")
			newOrg = new Sheep(newPos.x, newPos.y, this);
		else if (newName == "Wolf")
			newOrg = new Wolf(newPos.x, newPos.y, this);
		else if (newName == "Fox")
			newOrg = new Fox(newPos.x, newPos.y, this);
		else if (newName == "Antelope")
			newOrg = new Antelope(newPos.x, newPos.y, this);
		else if (newName == "Turtle")
			newOrg = new Turtle(newPos.x, newPos.y, this);
		else if (newName == "Cybersheep")
			newOrg = new Cybersheep(newPos.x, newPos.y, this);
		else if (newName == "Human")
			newOrg = new Human(newPos.x, newPos.y, this);
		else if (newName == "Grass")
			newOrg = new Grass(newPos.x, newPos.y, this);
		else if (newName == "Dandelion")
			newOrg = new Dandelion(newPos.x, newPos.y, this);
		else if (newName == "Guarana")
			newOrg = new Guarana(newPos.x, newPos.y, this);
		else if (newName == "Nightshade")
			newOrg = new Nightshade(newPos.x, newPos.y, this);
		else if (newName == "Pine_Borsch")
			newOrg = new PineBorsch(newPos.x, newPos.y, this);
		else
			throw InvalidType();

		saveFile >> newOrg->turnBlock;
		saveFile >> newOrg->strengh;

		Animal* animRepr = dynamic_cast<Animal*>(newOrg);
		if (animRepr) {
			saveFile >> animRepr->prevPos.x;
			saveFile >> animRepr->prevPos.y;

			Human* humRepr = dynamic_cast<Human*>(newOrg);
			if (humRepr) {
				saveFile >> humRepr->spellCD;
				human = humRepr;
			}
		}

		if (numOfOrganismes == 4)
			int x = 0;
		addOrganism(newOrg);
	}

	DialogWindow::getInstance().clearMsgs();
	DialogWindow::getInstance().printMsg("Game loaded!", WHITE, CYAN);
	DialogWindow::getInstance().drawMsgs();
}
void World::setHumanKilled() {
	human = nullptr;
}
void World::startSimulation() {
	drawWorld();

	char in = 0;
	DialogWindow dialog = DialogWindow::getInstance();

	while (in != 'q' && in != 'Q') {
		in = _getch();
		if (in == '\r') {
			nextTurn();
			DialogWindow::getInstance().printMsg("next turn");
		}
		else if (in == 's' || in == 'S')
			save();
		else if (in == 'l' || in == 'L') {
			load();
			clrscr();
			AppControl::drawStaticElements(worldW, worldH);
			drawWorld();
		}
		else if (in == -32 && human != nullptr)
			human->setDirection();
		else if (in == ' ' && human != nullptr)
			human->useSpell();
	
		if(DEBUG_MODE)
			drawField();
	}
}