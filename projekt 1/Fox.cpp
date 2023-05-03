#include "Fox.h"
#include "conio2.h"
#include "World.h"
#include "DialogWindow.h"
#include <vector>
#include <iostream>
#include <algorithm>

Fox::Fox(int x, int y, World* w) : Animal("Fox", x, y, 3, 7, w) {}

void Fox::draw() const{
	world->addToDrawMap(*this, FOX_COLOR);
}
void Fox::moveRandomly(){

	int walls = 0;
	if (pos.x == 0)
		walls++;
	if (pos.y == 0)
		walls++;
	if (pos.x == world->getWidth() - 1)
		walls++;
	if (pos.y == world->getHeight() - 1)
		walls++;

	Animal::moveRandomly();
	Animal* a = dynamic_cast<Animal*>(world->checkCollision(*this));

	std::vector<std::pair<int, int>> alreadyTried;
	short tries = 1;
	std::pair<int, int> helper;
	
	while (a != nullptr && a->getStrengh() <= this->getStrengh()) {

		if (tries >= 4 - walls) {
			moveBack();
			break;
		}
		
		alreadyTried.push_back({pos.x, pos.y});

		int c = 0;
		do {
			moveBack();
			Animal::moveRandomly();
			helper.first = pos.x;
			helper.second = pos.y;
			c++;
		} while (std::find(alreadyTried.begin(), alreadyTried.end(), helper) != alreadyTried.end());
		a = dynamic_cast<Animal*>(world->checkCollision(*this));

		tries++;
	}
}