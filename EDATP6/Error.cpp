#include "Error.h"

lcdError::lcdError()
{
	this->code = NO_ERROR;
	this->name = "Sin Error";
	this->description = "No hay errores";
}


void lcdError::setCode(unsigned long code)
{
	this->code = code; 
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