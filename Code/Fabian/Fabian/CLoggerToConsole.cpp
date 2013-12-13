#include "CLoggerToConsole.h"
#include "CLog.h"

#include <string>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

#include "Console\console.h"

//******************************************
// Class CLoggerToConsole:
// ILogger class which writes out the log to 
// a console using color codes
//******************************************

//-------------------------------------
// Constructor
// p1 in - bool, await user input on error
CLoggerToConsole::CLoggerToConsole(bool bWaitOnError) 
	:ILogger()
	,m_bWaitOnError(bWaitOnError)
{
}
//-------------------------------------
// Destructor
CLoggerToConsole::~CLoggerToConsole()
{
}
//-------------------------------------
	
//-------------------------------------
// Initializes the logger, should be called
//    before using or assigning the logger
// rv - returns false if it failed
bool CLoggerToConsole::Init()
{
	Console::Open();
	return true;
}
//-------------------------------------

//-------------------------------------
// Gets called whenever the logs receives a message
//    and needs it to be actually logged
// p1 in - log level, useally ERROR, WARNING or INFO
// p2 in - log id, the place where to write to
// p3 in - log message
void CLoggerToConsole::Write(char lvl, char id, const char* msg)
{
	time_t rawtime;
	tm * timeinfo;
	time(&rawtime);  /* get current time; same as: timer = time(NULL)  */
	timeinfo = localtime(&rawtime);
	
	char buffer [80];
	strftime (buffer, 80, "%Y-%m-%d - %H:%M:%S ", timeinfo);

	std::string sLvl(buffer);

	switch (lvl)
	{
	case FLOG_LVL_ERROR:
		sLvl += "-  ERROR  - ";
		Console::SetFGColor(ColorRed);
		break;
	case FLOG_LVL_WARNING:
		sLvl += "- WARNING - ";
		Console::SetFGColor(ColorYellow);
		break;
	case FLOG_LVL_INFO:
		sLvl += "-  INFO   - ";
		Console::SetFGColor(ColorWhite);
		break;
	default:
		sLvl += "- UNKNOWN - ";
		Console::SetFGColor(ColorMagenta);
		break;
	}

	sLvl += msg;
	Console::WriteLine( sLvl );
	
	if( lvl == FLOG_LVL_ERROR && m_bWaitOnError )
		Console::ReadKey();
}
//-------------------------------------

