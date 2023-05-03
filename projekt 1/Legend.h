#pragma once
#include "Window.h"

class Legend : public Window
{
private:
	Legend(int x, int y, int w, int h);
public:
	static Legend& getInstance(int x=0, int y=0, int w=0, int h=0);
	void drawLegend();
};