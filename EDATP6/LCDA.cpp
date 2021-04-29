#include "LCDA.h"

LcdA::LcdA()
{
    try
    {
        this->cursorP = cursorPosition();
        this->error = lcdError(NO_ERROR);


        this->messages[0] = "                ";
        this->messages[1] = "                ";

    
      
        
        this->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
        if (!display)
        {
            throw(AL_CREATE_DISPLAY_ERROR);
        }

        this->font = al_load_font("../Fonts/courier.ttf", 55, NULL);
        if (!this->font)
        {
            throw(AL_CREATE_FONT_ERROR);
        }

        al_clear_to_color(SCREEN_COLOR);

        al_set_window_title(this->display, "LCD A");
  

        //Draws iniitla message and cursor
        drawMessage();
        drawCursor();

    }
    catch (unsigned long code) 
    {
        lcdError tempError = lcdError(code);
        
        this->error = tempError;
    }
    
    
    

}

LcdA::~LcdA()
{
    al_destroy_display(this->display);
    al_destroy_font(this->font);
}

bool LcdA::lcdInitOk()
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


lcdError& LcdA::lcdGetError()
{
    return this->error;
}

bool LcdA::lcdClear()
{
    
    
    this->messages[0] = "                ";
    this->messages[1] = "                ";

    this->cursorP.row = 0;
    this->cursorP.column = 0;

    clearScreen();
    drawMessage();
    drawCursor();


    return true;
}


bool LcdA::lcdClearToEOL()
{
    
    int linesToClear = 16 - cursorP.column;
    std::string emptyStr(linesToClear, ' ');
    
    messages[cursorP.row].replace(cursorP.column, linesToClear, emptyStr);

    clearScreen();
    drawMessage();
    drawCursor();

    return true;
}



basicLCD& LcdA::operator<<(const char c)
{
    int msgId = cursorP.row;
    
    std::string str(1, c);
    

    if (messages[msgId][cursorP.column] == ' ')
    {
        messages[msgId].replace(cursorP.column, 1, str);
        cursorP.column += 1;
    }
  

    clearScreen();
    drawMessage();
    drawCursor();


    return *this;
}

basicLCD& LcdA::operator<<(const char* c)
{
    int msgId = cursorP.row;

    std::string str = c;


    if (messages[msgId][cursorP.column] == ' ')
    {
        messages[msgId].replace(cursorP.column, str.length(), str);
        cursorP.column += 1;
    }


    clearScreen();
    drawMessage();
    drawCursor();


    return *this;
}

bool LcdA::lcdMoveCursorUp()
{
    if (this->cursorP.row == 0)
    {
        return false;
    }
    else
    {
        this->cursorP.row -= 1;
    }
    
    clearScreen();
    drawMessage();
    drawCursor();
    return true;
}

bool LcdA::lcdMoveCursorDown()
{
    if(this->cursorP.row == 1)
    {
        return false;
    }
    else
    {
        this->cursorP.row += 1;
    }
   
    clearScreen();
    drawMessage();
    drawCursor();
    return true;
}

bool LcdA::lcdMoveCursorRight()
{
    if (this->cursorP.row == 0 && this->cursorP.column == 16)
    {
        this->cursorP.column = 0;
        this->cursorP.row = 1;
    }
    else if (this->cursorP.row == 1 && this->cursorP.column == 16)
    {
        return false;
    }
    else
    {
        this->cursorP.column += 1;
    }

    clearScreen();
    drawMessage();
    drawCursor();
    return true;
}

bool LcdA::lcdMoveCursorLeft()
{
    if (this->cursorP.row == 1 && this->cursorP.column == 0)
    {
        this->cursorP.column = 16;
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

    clearScreen();
    drawMessage();
    drawCursor();
    return true;
}


cursorPosition LcdA::lcdGetCursorPosition()
{
    return this->cursorP;
}


bool LcdA::lcdSetCursorPosition(const cursorPosition pos)
{
    int column = pos.column;
    int row = pos.row;

    if (column >= 0 && column <= 16)
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

void LcdA::drawMessage(void)
{
    ALLEGRO_COLOR colorBlack = al_map_rgb(0, 0, 0);
    
    al_draw_text(this->font, colorBlack, MSG_X, MSG1_Y, 0, this->messages[0].c_str()); //message 1
    al_draw_text(this->font, colorBlack, MSG_X, MSG2_Y, 0, this->messages[1].c_str()); //message 2



}

void LcdA::drawCursor(void)
{
    ALLEGRO_COLOR colorBlack = al_map_rgb(0, 0, 0);
    al_draw_line(20 + 33 * this->cursorP.column, this->cursorP.row * 100 + 20 - 1, 20 + 33 * this->cursorP.column, this->cursorP.row * 100 + 20 + 45, colorBlack, 1);
}

void LcdA::clearScreen(void)
{
    al_clear_to_color(SCREEN_COLOR);
}
