#include "BasicLCD.h"
#include "LCDA.h"
#include "Config.h"
#include <typeinfo>

int main(void) {


	bool running = true;

	if (!initAllegro())
	{
		return -1;
	}

	ALLEGRO_EVENT_QUEUE* keyQueue = al_create_event_queue();
	al_register_event_source(keyQueue, al_get_keyboard_event_source());


	//LCD array
	std::array <basicLCD*, LCDN > lcds;

	//Array that says which lcd is in use
	bool selectedLcd[LCDN];

	//LCds are created and assigned
	//lcds[2] = new LcdA();
	//lcds[1] = new LcdA();
	//lcds[0] = new LcdA();

	//al_clear_to_color(al_map_rgba_f(1, 1, 0.8, 1));

	//al_flip_display();


	//lcds[0]->lcdGetError().setCode(NO_ERROR);

	basicLCD* lcd;
	lcd = new LcdA();

	//Main loop.
	while (running)
	{
		//for (basicLCD* lcd : lcds)

		while (lcd->lcdGetError().getErrorCode() == NO_ERROR)
		{
			al_flip_display();
				
			ALLEGRO_EVENT ev;
			if (al_get_next_event(keyQueue, &ev))
			{
				int prueba = ev.keyboard.keycode;
				switch (ev.type)
				{
					case ALLEGRO_EVENT_KEY_CHAR:
						if (ev.keyboard.unichar >= 32)
						{
							const char aChar = ev.keyboard.unichar;
							lcd->operator<<(aChar);
						}
						else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
						{
							lcd->lcdClear();
						}
						else if (ev.keyboard.keycode == ALLEGRO_KEY_TAB)
						{
							lcd->lcdClearToEOL();
						}
						else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
						{
							lcd->lcdMoveCursorRight();
						}
						else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
						{
							lcd->lcdMoveCursorLeft();
						}
						else if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
						{
							lcd->lcdMoveCursorUp();
						}
						else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
						{
							lcd->lcdMoveCursorDown();
						}
						else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
						{
							lcd->lcdGetError().setCode(CLOSE_DISPLAY);
						}
						break;
					default:
						break;
				}
			}
		}

		if (lcd->lcdGetError().getErrorCode() == CLOSE_DISPLAY)
		{
			delete lcd;
			lcd = new LcdA;
		}
			
		
	}



	delete lcds[0];

	return 0;
}