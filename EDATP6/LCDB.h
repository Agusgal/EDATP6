#ifndef LCDB_H
#define LCDB_H

#include "BasicLCD.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_primitives.h>
#include <string>

#include "Error.h"

#define N_ROW 2
#define N_COLUMN 16
#define U_SIZE 50
#define DISPLAY_COLOR al_map_rgb(255, 0, 255)
#define LETTER_COLOR al_map_rgb(0, 0, 0)

class LCDB : public basicLCD
{
public:
	LCDB();
	virtual ~LCDB();

	virtual bool lcdInitOk();
	virtual lcdError& lcdGetError();
	virtual bool lcdClear();
	virtual bool lcdClearToEOL();
	virtual basicLCD& operator<<(const char c);
	virtual basicLCD& operator<<(const char* c);
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	virtual cursorPosition lcdGetCursorPosition();

private:
	ALLEGRO_DISPLAY* display; 
	ALLEGRO_FONT* font;
	char data[N_ROW][N_COLUMN]; //matriz donde se encuentra todo el texto del display
	void getLine(int nLine);	
	void printData();
	lcdError error;
	bool initOk;				
	cursorPosition cursorPos;	
	void clearDisp();
	bool nextPos(cursorPosition& pos);
	bool spaceDisp;	
	void printCursor(void);
	char line[N_COLUMN]; //linea que va a ser impresa en el display
};

#endif#pragma once