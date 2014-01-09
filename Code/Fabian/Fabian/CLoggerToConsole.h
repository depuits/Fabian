#ifndef FABIAN_CLOGGERTOCONSOLE_H_
#define FABIAN_CLOGGERTOCONSOLE_H_

#include "ILogger.h"

//******************************************
// Class CLoggerToConsole:
// ILogger class which writes out the log to 
// a console using color codes
//******************************************
class CLoggerToConsole : public ILogger
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - bool, await user input on error
	CLoggerToConsole(bool = false);
	//-------------------------------------
    // This function must not be implemented in the header or the
    // linker will build the code to call the application delete()
    // function instead of the library delete() function.
    virtual void Release();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the logger, should be called
	//    before using or assigning the logger
	// rv - returns false if it failed
	bool Init();
	//-------------------------------------

	//-------------------------------------
	// Gets called whenever the logs receives a message
	//    and needs it to be actually logged
	// p1 in - log level, useally ERROR, WARNING or INFO
	// p2 in - log id, the place where to write to
	// p3 in - log message
	virtual void Write(char, char, const char*);
	//-------------------------------------
	
protected:
	//-------------------------------------
	// Destructor
	// private so it can only be called by Release();
	virtual ~CLoggerToConsole();
	//-------------------------------------

private:
	bool m_bWaitOnError;

	DISALLOW_COPY_AND_ASSIGN(CLoggerToConsole);
};

#endif //FABIAN_CLOGGERCONSOLE_H_
