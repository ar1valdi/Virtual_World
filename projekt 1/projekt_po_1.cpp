#pragma once
#include <iostream>
#include "DialogWindow.h"
#include "conio2.h"
#include "World.h"
#include "Organism.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Cybersheep.h"
#include "Human.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Nightshade.h"
#include "PineBorsch.h"
#include "Legend.h"
#include "AppControl.h"
using namespace std;

int main()
{
	srand(time(NULL));
	// enter dimensions
	int W, H;
	cout << "Jan Kaczerski, 193237";
	cout << "\nEnter dimensions:\nWidth: ";
	W = AppControl::inputInt();
	cout << "\nHeight: ";
	H = AppControl::inputInt();

	clrscr();
	_setcursortype(_NOCURSOR);
	AppControl::drawStaticElements(W, H);

	World world(MAIN_BLOCK_POS_X + 2, MAIN_BLOCK_POS_Y + 1, W, H);

	world.spawnDefAnimals();
	world.startSimulation();
	
	gotoxy(1, MAIN_BLOCK_POS_Y + world.getHeight() + 5);
	return 0;
}