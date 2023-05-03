#include<windows.h>
#include"conio2.h"
#include <malloc.h>

HANDLE conHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(conHandle, pos);
};

int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(conHandle, &conInfo);
	COORD pos = conInfo.dwCursorPosition;
	return pos.X;
};

int wherey() {	
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(conHandle, &conInfo);
	COORD pos = conInfo.dwCursorPosition;
	return pos.Y;
};

void _setcursortype(int cur_t) {
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(conHandle, & cursor_info);
	if (cur_t == _NOCURSOR) {
		cursor_info.bVisible = FALSE;
	} else if(cur_t == _NORMALCURSOR) {
		cursor_info.bVisible = TRUE;
		cursor_info.dwSize = 13;
	} else return;
	SetConsoleCursorInfo(conHandle, &cursor_info);
};

void textbackground(int newcolor) {
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(conHandle, &conInfo);
	SetConsoleTextAttribute(conHandle, 16*newcolor);
};

void textcolor(int newcolor) {
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(conHandle, &conInfo);
	SetConsoleTextAttribute(conHandle, newcolor);
};

void clrscr() {
	system("cls");
};

static WORD ToWinAttribs(int attrib) {
	WORD rv = 0;
	if (attrib & 1) rv |= FOREGROUND_BLUE;
	if (attrib & 2) rv |= FOREGROUND_GREEN;
	if (attrib & 4) rv |= FOREGROUND_RED;
	if (attrib & 8) rv |= FOREGROUND_INTENSITY;
	if (attrib & 16) rv |= BACKGROUND_BLUE;
	if (attrib & 32) rv |= BACKGROUND_GREEN;
	if (attrib & 64) rv |= BACKGROUND_RED;
	if (attrib & 128) rv |= BACKGROUND_INTENSITY;
	return rv;
};

void puttext(int left, int top, int right, int bottom, void *source) {
	SMALL_RECT sqr = { left - 1, top - 1, right - 1, bottom - 1 };
	COORD pos = { 0,0 }, size = { right - left + 1, bottom - top + 1 };
	CHAR_INFO *buf;
	buf = (CHAR_INFO *)alloca((right - left + 1) * (bottom - top + 1) * sizeof(CHAR_INFO));

	for(int i = 0; i < (right - left + 1) * (bottom - top + 1); i++) {
		buf[i].Char.AsciiChar = ((char *)source)[i * 2];
		buf[i].Attributes = ToWinAttribs(((char *)source)[i * 2 + 1]);
	};
	WriteConsoleOutputA(conHandle, buf, size, pos, &sqr);
};

void settitle(const char *title) {
	SetConsoleTitleA(title);
};