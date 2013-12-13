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
	// Destructor
	virtual ~CLoggerMultiple();
	//-------------------------------------
	
	//-------------------------------------
	// Adds an new ILogger to log to
	//    This accepts the same logger multiple times
	// p1 in - pointer to ILogger
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

private:
	std::vector<ILogger*> m_vLoggers;

	DISALLOW_COPY_AND_ASSIGN(CLoggerMultiple);
};

#endif //FABIAN_CLOGGERMULTIPLE_H_
