#pragma once
#include "Window.h"

class DialogWindow : public Window
{
private:
	std::string logs[DIALOG_WINDOW_H - 2];
	int logsCol[DIALOG_WINDOW_H - 2][2];

	std::string newLogs[DIALOG_WINDOW_H - 2];
	int newLogsCol[DIALOG_WINDOW_H - 2][2];

	int newMsgs;

	DialogWindow(int x, int y, int w, int h);
public:
	static DialogWindow& getInstance(int x=0, int y=0, int w=0, int h=0);
	void printMsg(std::string msg, int color = WHITE, int bgColor=BLACK);
	void printErr(std::string msg);
	void drawMsgs();
	void clearMsgs();
};