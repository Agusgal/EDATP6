#include "BasicLCD.h"
#include "LCDA.h"
#include "Config.h"

int main(void) {

	if (!initAllegro())
	{
		return -1;
	}
	


	//Todo lo de abajo se deberia hacer con arreglo de lcds
	basicLCD* lcd = new LCDA();
	

	if (lcd->lcdInitOk())
	{
		//Everything allright
	}
	else
	{
		using namespace std;
		string str;
		cin >> str; 
		*lcd << str.c_str() << "\n"; //Todo check this
	}




	return 0;
}