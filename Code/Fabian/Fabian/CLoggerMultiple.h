#ifndef FABIAN_CLOGGERMULTIPLE_H_
#define FABIAN_CLOGGERMULTIPLE_H_

#include "ILogger.h"
#include <vector>

//******************************************
// Class CLoggerMultiple:
// ILogger class which combines multiple ILoggers
// to allow logging to multiple logs
// (ex. log to files and log to console)
//******************************************
class CLoggerMultiple : public ILogger
{
public:
	//-------------------------------------
	// Constructor
	CLoggerMultiple();
	//-------------------------------------
    // This function must not be implemented in the header or the
    // linker will build the code to call the application delete()
    // function instead of the library delete() function.
    virtual void DeleteThis();
	//-------------------------------------

	//-------------------------------------
	// Adds an new ILogger to log to
	// p1 in - pointer to ILogger (takes over ownership)
	void AddLogger(ILogger*);
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
	virtual ~CLoggerMultiple();
	//-------------------------------------

private:
	std::vector<ILogger*> m_vLoggers;

	DISALLOW_COPY_AND_ASSIGN(CLoggerMultiple);
};

#endif //FABIAN_CLOGGERMULTIPLE_H_
