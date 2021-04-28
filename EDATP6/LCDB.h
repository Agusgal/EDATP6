#ifndef LCDB_H
#define LCDB_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "BasicLCD.h"


#define DISPLAY_W 200
#define DISPLAY_H 20
#define N_ROW 2
#define N_COLUMN 16


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

	char data[N_ROW][N_COLUMN];
	void printData();
	lcdError error; 
	bool initOk;
	cursorPosition cursorPos;
	cursorPosition writePos; //ya se puede escribir aca
	void clearDisp();
	bool nextPos(cursorPosition& pos);
	bool spaceDisp; //1 si hay espacio disponible

	//funcion que dibuje al cursor
};

#endif