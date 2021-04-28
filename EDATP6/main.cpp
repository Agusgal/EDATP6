#include "BasicLCD.h"
#include "LCDA.h"
#include "Config.h"
#include <typeinfo>

#include "Gui.h"
#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"


void MainWindowSelector(Gui& myGui, basicLCD* lcd);

int main(void) {


	bool running = true;
	bool showMainWindow = true;
	bool displaySelector[LCDN] = {true, false, false};

	if (!initAllegro())
	{
		return -1;
	}

	ALLEGRO_EVENT_QUEUE* keyQueue = al_create_event_queue();
	al_register_event_source(keyQueue, al_get_keyboard_event_source());


	Gui myGui;

	
	basicLCD* lcd;

	int selector = myGui.showMainWindow();
	if (selector == 1)
	{
		lcd = new LcdA();
	}
	else if (selector == 2)
	{
		lcd = new LcdA();
	}
	else
	{
		lcd = new LcdA();
	}


	//lcd = new LcdA();

	//Main loop.
	while (running)
	{	
		
		bool closeDisplay = false;
		while (lcd->lcdGetError().getErrorCode() == NO_ERROR && !closeDisplay)
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
							closeDisplay = true;
						
						}
						break;
					default:
						break;
				}
			}
		}

		if (closeDisplay)
		{
			delete lcd;

			int selector = myGui.showMainWindow();
			if (selector == 1)
			{
				lcd = new LcdA();
			}
			else if (selector == 2)
			{
				lcd = new LcdA();//debe ser B
			}
			else if (selector == 3)
			{
				lcd = new LcdA();//debe ser C
			}
			

			closeDisplay = false;
		}
			
		
	}


	return 0;
}





void MainWindowSelector(Gui &myGui, basicLCD* lcd)
{
	int selector = myGui.showMainWindow();
	if (selector == 1)
	{
		lcd = new LcdA();
	}
	else if (selector == 2)
	{
		lcd = new LcdA();
	}
	else
	{
		lcd = new LcdA();
	}
}