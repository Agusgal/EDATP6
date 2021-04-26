#ifndef LCDA_H
#define LCDA_H
//Completar metodos virtuales puros
//Dibujo en allegro
// Datos miembros y métdoos, auxiliares de funcionamiento


//updateScreen, Draw, 

#include "allegro5/allegro.h"
#include "BasicLCD.h"


#define DISPLAY_WIDTH       200
#define DISPLAY_HEIGHT		20


class LCDA : public basicLCD
{
public:
    LCDA();
	virtual ~LCDA();


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
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMER* flipTimer;

	double displaySizeX;
	double displaySizeY;

	double fps;

	cursorPosition cursorP;




protected:
	//Stuff
};

#endif