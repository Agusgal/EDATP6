#include "LCDB.h"
#include <iostream>

using namespace std;


LCDB::LCDB() {
    initOk = 1;
    error = lcdError(NO_ERROR);
    spaceDisp = 1;
    cursorPos.row = 0;
    cursorPos.column = 0;
   // writePos.row = 0;
    //writePos.column = 0;

    if (!(font = al_load_font("../Fonts/love.ttf", U_SIZE, 0)) && initOk) {
        fprintf(stderr, "Failed to initialize the font !\n");
        initOk = false;
    }




    this->display = al_create_display(N_COLUMN * U_SIZE, N_ROW * U_SIZE * 2);
    if (!display) {

        fprintf(stderr, "Failed to create display !\n");
        initOk = 0;
    }
    lcdClear();
}

LCDB::~LCDB() {
    al_destroy_display(display);
}

bool LCDB::lcdInitOk() {
    

    if (!(font = al_load_font("../Fonts/love.ttf", U_SIZE, 0)) && initOk) {
        fprintf(stderr, "Failed to initialize the font !\n");
        initOk = false;
    }
    return initOk;
}

lcdError& LCDB::lcdGetError() {
    return error;
}

bool LCDB::lcdClear() {
    clearDisp();
    cursorPos.row = 0;
    cursorPos.column = 0;
    for (int i = 0; i < N_COLUMN * N_ROW; i++) {
        data[cursorPos.row][cursorPos.column] = ' ';
        nextPos(cursorPos);
    }
    spaceDisp = 1;
    cursorPos.row = 0;
    cursorPos.column = 0;
    printCursor();
    return true;
}

bool LCDB::lcdClearToEOL() {
    cursorPosition aux;

    aux.row = cursorPos.row;
    aux.column = cursorPos.column;
    while (nextPos(aux)) {
        data[aux.row][aux.column] = ' ';
    }
    clearDisp();
    printCursor();
    printData();
    return 1;
}

basicLCD& LCDB::operator<<(const char c) {
    clearDisp();
    if (data[cursorPos.row][cursorPos.column] == ' ') {

        data[cursorPos.row][cursorPos.column] = c;
        spaceDisp = nextPos(cursorPos);
    }
    printCursor();
    printData();
    return (*this);
}

basicLCD& LCDB::operator<<(const char* c) {
    int sizeC = 0;
    const char* auxPtr = c;
    while (*auxPtr != 0) {
        sizeC++;
        auxPtr++;
    }
    if (sizeC > (N_ROW) * (N_COLUMN)) {
        int substract = sizeC - (N_ROW) * (N_COLUMN);
        for (int i = 0; i < substract; i++) {
            c++;
        }
    }
    while (*c != '\0')
    {
        data[cursorPos.row][cursorPos.column] = *c;
        c++;
        spaceDisp = nextPos(cursorPos);
    }
    printCursor();
    printData();
    return (*this);
}

void LCDB::printData() {
    for (int i = 0; i < N_ROW; i++) {
        getLine(i);
        al_draw_textf(font, LETTER_COLOR, 2 * U_SIZE, 2 * U_SIZE * i, 0, line);
    }
    al_flip_display();
}

void LCDB::getLine(int line) {

    for (int i = 0; i < 16; i++) {
        this->line[i] = data[line][i];
    }
}

bool LCDB::nextPos(cursorPosition& pos) {

    if ((pos.column == (N_COLUMN - 1)) && (pos.row == (N_ROW - 1))) {
        spaceDisp = 0;
        return false;
    }
    else if ((pos.column == (N_COLUMN - 2)) && (pos.row == (N_ROW - 1))) {
        pos.column += 1;
        return false;
    }
    else if ((pos.column == (N_COLUMN - 1)) && (pos.row == 0)) {
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
    clearDisp();
    printCursor();
    printData();
    return true;
}

bool LCDB::lcdMoveCursorDown() {
    if (cursorPos.row == (N_ROW - 1))
    {
        return false;
    }
    else
    {
        cursorPos.row += 1;
    }
    clearDisp();
    printCursor();
    printData();
    return true;
}

bool LCDB::lcdMoveCursorRight() {
    if (cursorPos.row == 0 && cursorPos.column == (N_COLUMN - 1))
    {
        cursorPos.column = 0;
        cursorPos.row = 1;
    }
    else if (cursorPos.row == 1 && cursorPos.column == (N_COLUMN - 1))
    {
        return false;
    }
    else
    {
        this->cursorPos.column += 1;
    }
    clearDisp();
    printCursor();
    printData();
    return true;
}

bool LCDB::lcdMoveCursorLeft() {
    if (cursorPos.row == 1 && cursorPos.column == 0)
    {
        cursorPos.column = N_COLUMN - 1;
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
    clearDisp();
    printCursor();
    printData();
    return true;
}

bool LCDB::lcdSetCursorPosition(const cursorPosition pos) {
    if ((pos.column <= (N_COLUMN - 1) && pos.column >= 0) && (pos.row == 1 || pos.row == 0)) {
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

void LCDB::printCursor(void)
{
   al_draw_line(100+ 38 * (cursorPos.column), 2 * (cursorPos.row) * U_SIZE + 20, 100 + 38 * (cursorPos.column), 4 * (cursorPos.row) * U_SIZE + 80, al_map_rgb(0, 0, 0), 2);
}

void LCDB::clearDisp() {
    al_clear_to_color(DISPLAY_COLOR);
    al_flip_display();
}

