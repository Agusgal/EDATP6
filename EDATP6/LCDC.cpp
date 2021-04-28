#define _CRT_SECURE_NO_WARNINGS

#include "LCDC.h"

#define FONT		"../Fonts/OpenSans-Semibold.ttf"
#define LCD			"../Images/lcd.png"
#define FPS			60

int LcdC::initAllegro()
{
	int error = -1;
	//inicializo cada componente relacionado con allegro

	this->punteros.font = al_load_font(FONT, 45, 0);
	if (this->punteros.font)
	{
		this->punteros.display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

		if (this->punteros.display)
		{
			this->punteros.lcd = al_load_bitmap(LCD);

			if (this->punteros.lcd)
			{
			}
			else
			{
				error = 3;
			}
		}
		else
		{
			error = 2;
		}		
	}
	else
	{
		error = 1;
	}

	if (error == -1) //En caso de una inicialización correcta se dibuja el entorno, se inicializan timers, etc.
	{
		//al_register_event_source(pointers->eventQueue, al_get_display_event_source(pointers->display));
		//al_register_event_source(pointers->eventQueue, al_get_keyboard_event_source());
		al_draw_bitmap(this->punteros.lcd, 0, 0, 0);
		//al_register_event_source(pointers->eventQueue, al_get_timer_event_source(pointers->timer));
		//al_start_timer(pointers->timer);
		//al_flip_display();
	}
	else // Si hubo errores destruyo los recursos
	{
		destroyAllegro();
	}

	return error;
}

//destruyo ciertos componentes de allegro (para destruir todo : error = 3)
void LcdC::destroyAllegro()
{
	if (this->punteros.lcd)
		al_destroy_bitmap(this->punteros.lcd);
	if (this->punteros.display)
		al_destroy_display(this->punteros.display);
	if (this->punteros.font)
		al_destroy_font(this->punteros.font);
}

LcdC::LcdC()
{
	this->cursor.column = 0;
	this->cursor.row = 0;

	this->text[0] = "                ";
	this->text[1] = "                ";

	int error = initAllegro();

	this->error = lcdError(NO_ERROR);

	switch (error)
	{
	case 1:
		//error de fuentes
		break;
	case 2:
		//error de display
		break;
	case 3:
		//error de eventos
		break;
	}
}

LcdC::~LcdC()
{
	destroyAllegro();
}

void LcdC::redraw()
{
	al_draw_bitmap(this->punteros.lcd, 0, 0, 0);
	al_draw_text(this->punteros.font, green, 98, 85, 0, this->text[0].c_str());
	al_draw_text(this->punteros.font, green, 98, 140, 0, this->text[1].c_str());
}

bool LcdC::lcdInitOk()
{
	if (this->error.getErrorCode() == NO_ERROR)
	{
		return true;
	}
	else
	{
		return false;
	}
}


lcdError& LcdC::lcdGetError()
{
	return this->error;
}

bool LcdC::lcdClear()
{
	this->text[0] = "                ";
	this->text[1] = "                ";

	this->cursor.column = 0;
	this->cursor.row = 0;

	redraw();

	return true;
}


bool LcdC::lcdClearToEOL()
{
	this->text[this->cursor.row].replace(this->cursor.column, 16 - this->cursor.column, 16 - this->cursor.column, ' ');
	redraw();

	return true;
}



basicLCD& LcdC::operator<<(const char c)
{
	if (c >= 32 && c <= 126)
	{
		if (this->cursor.column < 15)
		{
			this->text[this->cursor.row].replace(this->cursor.column, 1, 1, c);
			this->cursor.column +=1;
		}
		else if (this->cursor.row == 0)
		{
			this->text[this->cursor.row].replace(this->cursor.column, 1, 1, c);
			this->cursor.column = 0;
			this->cursor.row = 1;
		}
		else if (this->cursor.row == 1)
		{
			this->text[this->cursor.row].replace(this->cursor.column, 1, 1, c);
		}
	}
	redraw();

	return *this;
}

basicLCD& LcdC::operator<<(const char* c)
{
	//sobrecarga = escritura en pantalla 

	return *this;
}

bool LcdC::lcdMoveCursorUp()
{
	if (this->cursor.row == 0)
	{
		return false;
	}
	else
	{
		this->cursor.row = 0;
	}

	redraw();

	return true;
}

bool LcdC::lcdMoveCursorDown()
{
	if (this->cursor.row == 1)
	{
		return false;
	}
	else
	{
		this->cursor.row = 1;
	}

	redraw();

	return true;
}

bool LcdC::lcdMoveCursorRight()
{
	if (this->cursor.row == 0 && this->cursor.column == 16)
	{
		this->cursor.column = 0;
		this->cursor.row = 1;
	}
	else if (this->cursor.row == 1 && this->cursor.column == 16)
	{
		return false;
	}
	else
	{
		this->cursor.column +=1;
	}

	redraw();

	return true;
}

bool LcdC::lcdMoveCursorLeft()
{
	if (this->cursor.row == 1 && this->cursor.column == 0)
	{
		this->cursor.column = 16;
		this->cursor.row = 0;
	}
	else if (this->cursor.row == 0 && this->cursor.column == 0)
	{
		return false;
	}
	else
	{
		this->cursor.column -= 1;
	}

	redraw();

	return true;
}


cursorPosition LcdC::lcdGetCursorPosition()
{
	return this->cursor;
}


bool LcdC::lcdSetCursorPosition(const cursorPosition pos)
{
	if ((pos.column >= 0 && pos.column <= 16) && (pos.row == 0 || pos.row == 1))
	{
		this->cursor.column = pos.column;
		this->cursor.row = pos.row;
	}
	else
	{
		return false;
	}

	return true;
}