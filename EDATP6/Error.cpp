#include "Error.h"

lcdError::lcdError(unsigned long code)
{
	this->code = code;
	
	if (code == NO_ERROR)
	{
		this->name = "No Error";
		this->description = "Sin Errores";
	}
	else if (CLOSE_DISPLAY)
	{
		//adadsdfsadf
	}

}

unsigned long lcdError::getErrorCode(void)
{
	return this->code;
}

std::string lcdError::getErrorDescription(void)
{
	return this->description;
}

std::string lcdError::getErrorName(void)
{
	return this->name;
}