#ifndef GUI_H
#define GUI_H  1

#include <stdio.h>

#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Gui {
public:
    Gui();
    int mainWindow(void);

    int showMainWindow(void);

    int configureEvents(void);
    int configureImGui(void);

private:
    int selectedDisplay;


    int guiWindowSizeX;

    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT ev;
    ALLEGRO_TIMER* flipTimer;

    double displaySizeX;
    double displaySizeY;

    bool runningMain;
    bool closeWindow;

    double fps;
};



#endif