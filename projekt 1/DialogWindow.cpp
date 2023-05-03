#include "DialogWindow.h"
#include "conio2.h"
#include <iostream>
using namespace std;

DialogWindow::DialogWindow(int x, int y, int w, int h) : Window(x, y, w, h) {
	for (int i = 0; i < height - 2; i++) {
		logs[i] = "";
		logsCol[i][0] = WHITE;
		logsCol[i][1] = BLACK;
	}
	newMsgs = 0;
}
DialogWindow& DialogWindow::getInstance(int x, int y, int w, int h) {
	static DialogWindow instance(x,y,w,h);
	return instance;
}
void DialogWindow::clearMsgs() {
	string cleanVerse = "";
	for (int i = 0; i < width * 2 - 4;i++) {
		cleanVerse += " ";
	}
	for (int i = 0; i < height - 2; i++) {
		logs[i] = cleanVerse;
		logsCol[i][0] = WHITE;
		logsCol[i][0] = BLACK;
	}
}
void DialogWindow::printMsg(std::string msg, int color, int bgColor) {
	// old slow version
	for (int i = height - 3; i > 0; i--) {
		logs[i] = logs[i - 1];
		logsCol[i][0] = logsCol[i - 1][0];
		logsCol[i][1] = logsCol[i - 1][1];
	}

	if (msg.length() > width * 2 - 3)
		msg.erase(width - 2, msg.length());
	else {
		while (msg.length() != width*2 - 4)
			msg += " ";
	}
	logs[0] = msg;
	logsCol[0][0] = color;
	logsCol[0][1] = bgColor;
}
void DialogWindow::drawMsgs() {
	for (int i = 0; i < height - 2; i++) {
		gotoxy(winPos.x * 2 + 1, winPos.y + 1 + i);
		textcolor(logsCol[i][0]);
		textbackground(logsCol[i][1]);
		cout << logs[i];
	}

	textcolor(WHITE);
	textbackground(BLACK);
}
void DialogWindow::printErr(string msg){
	msg = "ERR: " + msg;
	printMsg(msg, BLACK, RED);
}