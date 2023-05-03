#include "AppControl.h"
#include "conio2.h"
#include "DialogWindow.h"
#include "Legend.h"
#include <iostream>
#include <conio.h>

int AppControl::inputInt() {
	int result = 0;
	char c = _getch();
	while (c != 13) {		// 13 == '\n'
		if (c == '\b' && result != 0) {
			result /= 10;
			gotoxy(wherex() - 1, wherey());
			putchar(' ');
			gotoxy(wherex() - 1, wherey());
		}
		else if (c >= '0' && c <= '9') {
			putchar(c);
			result = result * 10 + (c - '0');
		}
		c = _getch();
	}
	return result;
}

void AppControl::drawStaticElements(int worldW, int worldH) {
	gotoxy(1, 1);

	std::cout << "Jan Kaczerski, 193237";
	Window worldWindow(MAIN_BLOCK_POS_X, MAIN_BLOCK_POS_Y, worldW + 2, worldH + 2);
	DialogWindow& dialog = DialogWindow::getInstance(worldW + 2, MAIN_BLOCK_POS_Y, DIALOG_WINDOW_W, DIALOG_WINDOW_H);
	Legend& legend = Legend::getInstance(worldW + 2, MAIN_BLOCK_POS_Y + DIALOG_WINDOW_H - 1, LEGEND_WINDOW_W, LEGEND_WINDOW_H);
	
	dialog.changePos(worldW + 2, MAIN_BLOCK_POS_Y);
	legend.changePos(worldW + 2, MAIN_BLOCK_POS_Y + DIALOG_WINDOW_H - 1);

	worldWindow.drawWindow();
	dialog.drawWindow();
	legend.drawWindow();
	legend.drawLegend();
}