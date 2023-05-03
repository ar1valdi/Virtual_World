#pragma once
// frames and positions
#define FRAME_COLOR			LIGHTGRAY
#define DIALOG_WINDOW_W		20
#define DIALOG_WINDOW_H		20
#define MAIN_BLOCK_POS_X	1
#define MAIN_BLOCK_POS_Y	3
#define LEGEND_WINDOW_W		20
#define LEGEND_WINDOW_H		8

// directions
#define KEY_UP				72
#define KEY_DOWN			80
#define KEY_LEFT			75	
#define KEY_RIGHT			77

// world array spaces
#define EMPTY_SPACE nullptr

// plants
#define EXPAND_CHANCE		33

// types of reflection
#define REFLECTED_KILL		0
#define NOT_REFLECTED		1
#define REFLECTED_MOVE		2
#define RUNNED_AWAY			3

// colors (compatible with conio2.h)
#define BLACK				0
#define BLUE				1
#define GREEN				2
#define CYAN				3
#define RED					4
#define MAGENTA				5
#define BROWN				6
#define LIGHTGRAY			7
#define DARKGRAY			8
#define LIGHTBLUE			9
#define LIGHTGREEN			10
#define LIGHTCYAN			11
#define LIGHTRED			12
#define LIGHTMAGENTA		13
#define YELLOW				14
#define WHITE				15

// colors on world
#define DEF_COLOR_IN		BLACK
#define DEF_COLOR_OUT		BLACK

#define WOLF_COLOR			DARKGRAY
#define SHEEP_COLOR			WHITE
#define FOX_COLOR			BROWN
#define ANTELOPE_COLOR		YELLOW
#define TURTLE_COLOR		CYAN
#define CYBERSHEEP_COLOR	LIGHTBLUE

#define GRASS_COLOR			GREEN
#define DANDELION_COLOR		LIGHTMAGENTA
#define GUARANA_COLOR		LIGHTRED
#define NIGHTSHADE_COLOR	BLUE
#define PINE_BORSCH_COLOR	RED

#define HUMAN_COLOR			MAGENTA

// extended ascii table
#define ASCII_BLOCK			(char)219
#define ASCII_DOTS			(char)176
#define ASCII_SPACE			(char)32
#define ASCII_SMILE			(char)2

// default animals
#define SHEEP_NUMBER		10
#define WOLF_NUMBER			10
#define TURTLE_NUMBER		10
#define ANTELOPE_NUMBER		10
#define FOX_NUMBER			10
#define GRASS_NUMBER		10
#define DANDELION_NUMBER	10
#define GUARANA_NUMBER		10
#define NIGHTSHADE_NUMBER	10
#define PINE_BORSCH_NUMBER	10
#define SPAWN_HUMAN			true

// cybersheep is not workin properlly
#define CYBERSHEEP_NUMBER	0

#define DEBUG_MODE			false