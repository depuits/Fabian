#include "CLoggerMultiple.h"

//******************************************
// Class CLoggerMultiple:
// ILogger class which combines multiple ILoggers
// to allow logging to multiple logs
// (ex. log to files and log to console)
//******************************************

//-------------------------------------
// Constructor
CLoggerMultiple::CLoggerMultiple()
	:ILogger()
{
}
//-------------------------------------
// Destructor
CLoggerMultiple::~CLoggerMultiple()
{
	for(std::vector<ILogger*>::iterator it( m_vLoggers.begin() ); it != m_vLoggers.end(); ++it)
		delete (*it);
}
//-------------------------------------

//-------------------------------------
// Adds an new ILogger to log to
// p1 in - pointer to ILogger
void CLoggerMultiple::AddLogger(ILogger *pLogger)
{
    // check if the logger isn't already added
    //    This is important for when the class deletes them
    //    Can't be this
	if(pLogger == this)
		return;

	if( std::find(m_vLoggers.begin(), m_vLoggers.end(), pLogger) != m_vLoggers.end() )
		return;

	m_vLoggers.push_back(pLogger);
}
//-------------------------------------

//-------------------------------------
// Gets called whenever the logs receives a message
//    and needs it to be actually logged
// p1 in - log level, useally ERROR, WARNING or INFO
// p2 in - log id, the place where to write to
// p3 in - log message
void CLoggerMultiple::Write(char lvl, char id, const char* msg)
{
	for(std::vector<ILogger*>::iterator it( m_vLoggers.begin() ); it != m_vLoggers.end(); ++it)
		(*it)->Write(lvl, id, msg);
}
//-------------------------------------


