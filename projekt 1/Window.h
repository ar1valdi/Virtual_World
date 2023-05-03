#pragma once
#include "UtilityStructs.h"
#include "consts.h"
#include <string>

class Window
{
protected:
	coords winPos;
	int width, height;
public:
	Window(int x, int y, int w, int h);
	virtual void drawWindow();
	void changePos(int x, int y);
};

