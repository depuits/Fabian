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
    // This function must not be implemented in the header or the
    // linker will build the code to call the application delete()
    // function instead of the library delete() function.
    virtual void Release() = 0;
	//-------------------------------------
	
	//-------------------------------------
	// Gets called whenever the logs receives a message
	//    and needs it to be actually logged
	// p1 in - log level, useally ERROR, WARNING or INFO
	// p2 in - log id, the place where to write to
	// p3 in - log message
	virtual void Write(char, char, const char*) = 0;
	//-------------------------------------

protected:
	//-------------------------------------
	// Destructor
	// private so it can only be called by Release();
	virtual ~ILogger() { }
	//-------------------------------------
	
private:
	DISALLOW_COPY_AND_ASSIGN(ILogger);
};

#endif //FABIAN_ILOGGER_H_
