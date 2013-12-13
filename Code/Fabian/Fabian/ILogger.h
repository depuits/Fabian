#ifndef FABIAN_ILOGGER_H_
#define FABIAN_ILOGGER_H_

#include "FabianDef.h"

//******************************************
// Interface ILogger:
// ILogger classes are responsible to actually procces
// the log messages and print them to the screen or
// do other things with it.
//******************************************
class ILogger
{
public:
	//-------------------------------------
	// Constructor
	ILogger() { }
	//-------------------------------------
	// Destructor
	virtual ~ILogger() { }
	//-------------------------------------
	
	//-------------------------------------
	// Gets called whenever the logs receives a message
	//    and needs it to be actually logged
	// p1 in - log level, useally ERROR, WARNING or INFO
	// p2 in - log id, the place where to write to
	// p3 in - log message
	virtual void Write(char, char, const char*) = 0;
	//-------------------------------------

private:

	DISALLOW_COPY_AND_ASSIGN(ILogger);
};

#endif //FABIAN_ILOGGER_H_
