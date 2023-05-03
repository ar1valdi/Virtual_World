#pragma once
#include "consts.h"

#define _NOCURSOR	0
#define _NORMALCURSOR	1

void gotoxy(int x, int y);		// move cursor to the position (x,y)
int wherex(void);			// return x coordinate of the cursor
int wherey(void);			// return y coordinate of the cursor 
void _setcursortype(int cur_t);		// set cursor type: _NOCURSOR, _SOLIDCURSOR or _NORMALCURSOR

void textbackground(int newcolor);	// set background color of new characters
void textcolor(int newcolor);		// set foreground color of new characters

void clrscr(void);			// clear entire screen

// write a saved portion from buffer to screen
void puttext(int left, int top, int right, int bottom, void *source);

// bonus functions
void settitle(const char *title);