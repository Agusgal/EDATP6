#include "LCDB.h"


LCDB::LCDB(){
    initOk = 1;
    spaceDisp = 1;
    this->display = al_create_display(DISPLAY_W, DISPLAY_H);
    if (!display) {

        fprintf(stderr, "Failed to create display !\n");
        initOk = 0;
    }

    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_font("love", 24, 0);

    clearDisp();
}

LCDB::~LCDB() {

}


bool LCDB::lcdInitOk() {
    return initOk;
}

lcdError& LCDB::lcdGetError() {
    return error;
}

bool LCDB::lcdClear() {
    clearDisp();
    cursorPos.row = 0;
    cursorPos.column = 0;
    //funcion que dibuje al cursor
    return true;
}

bool LCDB::lcdClearToEOL() {
   // Borra el display desde la posición actual
   // del cursor hasta el final de la línea.
    cursorPosition aux;
    writePos.row = cursorPos.row; //quizas es mas 1 o menos 1
    writePos.column = cursorPos.column;
    aux.row = cursorPos.row;
    aux.column = cursorPos.column;
    while (nextPos(aux)) {
        data[aux.row][aux.column] = '\0';
    }
    clearDisp();
    printData();
    return 1;
}

basicLCD& LCDB::operator<<(const char c) {
    if (spaceDisp) {
        data[writePos.row][writePos.column] = c;
        spaceDisp = nextPos(writePos);
    }
    printData();
    return (*this);
}

basicLCD& LCDB::operator<<(const char* c) {
 
    while ((*c != '\0')&&(spaceDisp)) //chequiar q este bien este terminador
    {
        data[writePos.row][writePos.column] = *c;
        c++;
        spaceDisp = nextPos(writePos);
    }

    printData();
    return (*this);
}

void LCDB::printData() {
    al_draw_text(font, al_map_rgb(0, 0, 0), 20.5, 4.5, 0, "hola");
    al_flip_display();
}

bool LCDB::nextPos(cursorPosition& pos) {
   
    if ((pos.column == 15) && (pos.row == 1)) {
        spaceDisp = 0;
        return false;
    }
    else if ((pos.column == 14) && (pos.row == 1)) {
        pos.column += 1;
        return false;
    }
    else if ((pos.column == 15) && (pos.row == 0)) {
        pos.column = 0;
        pos.row = 1;
    }
    else {
        pos.column += 1;
    }
    return true; //devuelve si sigue habiendo espacio disponible despues de la operacion

}

bool LCDB::lcdMoveCursorUp() {
    if (cursorPos.row == 0)
    {
        return false;
    }
    else
    {
        cursorPos.row -= 1;
    }
    return true;
}

bool LCDB::lcdMoveCursorDown() {
    if (cursorPos.row == 1)
    {
        return false;
    }
    else
    {
        cursorPos.row += 1;
    }
    return true;
}

bool LCDB::lcdMoveCursorRight() {
    if (cursorPos.row == 0 && cursorPos.column == 15)
    {
        cursorPos.column = 0;
        cursorPos.row = 1;
    }
    else if (cursorPos.row == 1 && cursorPos.column == 15)
    {
        return false;
    }
    else
    {
        this->cursorPos.column += 1;
    }
    return true;
}

bool LCDB::lcdMoveCursorLeft() {
    if (cursorPos.row == 1 && cursorPos.column == 0)
    {
        cursorPos.column = 15;
        cursorPos.row = 0;
    }
    else if (cursorPos.row == 0 && cursorPos.column == 0)
    {
        return false;
    }
    else
    {
        cursorPos.column -= 1;
    }
    return true;
}

bool LCDB::lcdSetCursorPosition(const cursorPosition pos) {
    if ((pos.column <= 15 && pos.column >= 0)&&(pos.row == 1 || pos.row == 0)){
        cursorPos.column = pos.column;
        cursorPos.row = pos.row;
    }
    else {
        return false;
    }
    return true;
}

cursorPosition LCDB::lcdGetCursorPosition() {
    return cursorPos;
}

void LCDB::clearDisp() {
    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_flip_display();
}

