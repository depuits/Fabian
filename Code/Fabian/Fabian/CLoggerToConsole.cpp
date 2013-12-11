#include "CLoggerToConsole.h"
#include "CLog.h"

#include <string>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

#include "Console\console.h"

//-------------------------------------
// Constructor
CLoggerToConsole::CLoggerToConsole() 
	:ILogger()
{
}
//-------------------------------------
// Destructor
CLoggerToConsole::~CLoggerToConsole()
{
}
//-------------------------------------
	
bool CLoggerToConsole::Init()
{
	Console::Open();
	return true;
}

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
}

