#include "LCDA.h"

LCDA::LCDA()
{
	this->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    if (!display) {

        fprintf(stderr, "Failed to create display !\n");
        //En caso de fallar devuelvo el error?? 
    }
}



basicLCD& LCDA::operator<<(const char* c)
{
    //sobrecarga


    return (*this);
}

bool LCDA::lcdMoveCursorUp()
{
    if (this->cursorP.row == 0)
    {
        return false;
    }
    else
    {
        this->cursorP.row -= 1;
    }
    return true;
}

bool LCDA::lcdMoveCursorDown()
{
    if(this->cursorP.row == 1)
    {
        return false;
    }
    else
    {
        this->cursorP.row += 1;
    }
    return true;
}

bool LCDA::lcdMoveCursorRight()
{
    if (this->cursorP.row == 0 && this->cursorP.column == 15)
    {
        this->cursorP.column = 0;
        this->cursorP.row = 1;
    }
    else if (this->cursorP.row == 1 && this->cursorP.column == 15)
    {
        return false;
    }
    else
    {
        this->cursorP.column += 1;
    }
    return true;
}

bool LCDA::lcdMoveCursorLeft()
{
    if (this->cursorP.row == 1 && this->cursorP.column == 0)
    {
        this->cursorP.column = 15;
        this->cursorP.row = 0;
    }
    else if(this->cursorP.row == 0 && this->cursorP.column == 0)
    {
        return false;
    }
    else
    {
        this->cursorP.column -= 1;
    }
    return true;
}


cursorPosition LCDA::lcdGetCursorPosition()
{
    return this->cursorP;
}


bool LCDA::lcdSetCursorPosition(const cursorPosition pos)
{
    int column = pos.column;
    int row = pos.row;

    if (column >= 0 && column <= 15)
    {
        this->cursorP.column = column;
    }
    else 
    {
        return false;
    }

    if (row == 0 || row == 1)
    {
        this->cursorP.row = row;
    }
    else
    {
        return false;
    }

    return true;
}
