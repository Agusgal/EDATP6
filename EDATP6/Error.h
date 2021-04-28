#ifndef ERROR_H
#define ERROR_H

#include <string>

enum errorClass {AL_CREATE_DISPLAY_ERROR, AL_CREATE_FONT_ERROR, NO_ERROR, ERROR_N};


class lcdError
{
public:
	lcdError();
	
	
	std::string getErrorName();
	std::string getErrorDescription();
	unsigned long getErrorCode();
	
	void setCode(unsigned long code);


private:
	
	std::string description;
	std::string name;
	unsigned long code; 


};


#endif

