#define _CRT_SECURE_NO_WARNINGS

#include "LCDC.h"

#define FONT		"../Fonts/OpenSans-Semibold.ttf"
#define LCD			"../Images/lcd.png"
#define FPS			60

int LcdC::initAllegro()
{
	int error = -1;
	//inicializo cada componente relacionado con allegro
	if (al_init())
	{
		if (al_init_image_addon())
		{
			if (1)
			{
				if (1)
				{
					if (1)
					{
						if (1)
						{
							this->punteros.font = al_load_font(FONT, 40, 0);
							if (this->punteros.font)
							{
								this->punteros.display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

								if (this->punteros.display)
								{
									//this->punteros.eventQueue = al_create_event_queue();

									if (1)
									{
										this->punteros.lcd = al_load_bitmap(LCD);

										if (this->punteros.lcd)
										{
											//this->punteros.timer = al_create_timer((float)(1.0 / FPS));
											if (1)
											{

											}
											else
											{
												fprintf(stderr, "failed to create timers!\n");
												error = 5;
											}

										}
										else
										{
											fprintf(stderr, "failed to load bitmaps!\n");
											error = 4;
										}
									}
									else
									{
										fprintf(stderr, "failed to create event queue!\n");
										error = 3;
									}*/
								}
								else
								{
									fprintf(stderr, "failed to create display\n");
									error = 2;
								}
							}
							else
							{
								fprintf(stderr, "failed to create font!\n");
								error = 1;
							}
						}
						else
						{
							fprintf(stderr, "failed to install allegro keyboard!\n");
							error = 0;
						}
					}
					else
					{
						fprintf(stderr, "failed to initialize allegro ttf fonts!\n");
						error = 0;
					}
				}
				else
				{
					fprintf(stderr, "failed to initialize allegro fonts!\n");
					error = 0;
				}
			}
			else
			{
				fprintf(stderr, "failed to initialize allegro graphics!\n");
				error = 0;
			}
		}
		else
		{
			fprintf(stderr, "failed to initialize image addon!\n");
			error = 0;
		}
	}
	else
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		error = 0;
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
		destroyAllegro(error);
	}

	return error;
}

//destruyo ciertos componentes de allegro (para destruir todo : error = 5)
void LcdC::destroyAllegro(int error)
{
	int i = 0;
	switch (error)
	{
	case 5:
		if (this->punteros.timer)
			al_destroy_timer(this->punteros.timer);
	case 4:
		if (this->punteros.lcd)
			al_destroy_bitmap(this->punteros.lcd);
	case 3:
		if (this->punteros.eventQueue)
			al_destroy_event_queue(this->punteros.eventQueue);
	case 2:
		if (this->punteros.display)
			al_destroy_display(this->punteros.display);
	case 1:
		if (this->punteros.font)
			al_destroy_font(this->punteros.font);
	case 0:
		break;
	}
}

LcdC::LcdC()
{
	this->cursor.column = 0;
	this->cursor.row = 0;

	this->text[0].clear();
	this->text[1].clear();

	int error = initAllegro();

	this->error = lcdError(NO_ERROR);

	switch (error)
	{
	case 0:
		//error de base
		break;
	case 1:
		//error de fuentes
		break;
	case 2:
		//error de display
		break;
	case 3:
		//error de eventos
		break;
	case 4:
		//error de imagenes
		break;
	case 5:
		//error de timers
		break;
	}
	int a = 0;
}

LcdC::~LcdC()
{
	destroyAllegro(5);
}

void LcdC::redraw()
{
	al_draw_bitmap(this->punteros.lcd, 0, 0, 0);
	al_draw_text(this->punteros.font, green, 10, 10, 0, this->text[0].c_str());
	al_draw_text(this->punteros.font, green, 10, 70, 0, this->text[1].c_str());
	//al_flip_display();
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
	this->text[0].clear();
	this->text[1].clear();

	this->cursor.column = 0;
	this->cursor.row = 0;

	redraw();

	return true;
}


bool LcdC::lcdClearToEOL()
{
	this->text[this->cursor.row].replace(this->cursor.column, 1, 1, '\0');
	redraw();

	return true;
}



basicLCD& LcdC::operator<<(const char c)
{
	if (c >= 32 && c <= 126)
	{
		if (this->cursor.column < 15)
			this->text[this->cursor.row].replace(this->cursor.column, 1, 1, c);
		if (this->cursor.row == 0)
		{
			this->cursor.column = 0;
			this->cursor.row = 1;
			this->text[this->cursor.row].replace(this->cursor.column, 1, 1, c);
		}
		else
		{

		}
	}
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
		(this->cursor.column)++;
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
		(this->cursor.column)--;
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