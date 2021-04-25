#ifndef ERROR_H
#define ERROR_H

#include <string>

class lcdError
{
public:
	std::string getErrorName();
	std::string getErrorDescription();
	unsigned long getErrorCode();
};


#endif

