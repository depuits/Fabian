#include "CLoggerToConsole.h"
#include "CLog.h"

#include <string>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

#include "Console/console.h"

/************************************/
/*! Constructor
 * @param [in] bWaitOnError - Await user input on error
 */
CLoggerToConsole::CLoggerToConsole(bool bWaitOnError)
	:ILogger()
	,m_bWaitOnError(bWaitOnError)
{
}
/************************************/
/*! Destructor, 
 * private so it can only be called by Release();
 */
CLoggerToConsole::~CLoggerToConsole()
{
}
/************************************/
/*! This function must NOT be implemented in the header or the 
 * linker will build the code to call the application delete() 
 * function instead of the library delete() function.
 */
void CLoggerToConsole::Release()
{
    delete this;  // called from the right "delete context"
}
/************************************/

/************************************/
/*! Initializes the logger, should be called 
 *    before using or assigning the logger
 * @return False if it failed
 */
bool CLoggerToConsole::Init()
{
	Console::Open();
	return true;
}
/************************************/

/************************************/
/*! Gets called whenever the logs receives a message 
 *    and needs it to be actually logged
 * @param [in] lvl	- @ref FLOG_LVL, useally ERROR, WARNING or INFO
 * @param [in] id	- @ref FLOG_ID, the place where to write to
 * @param [in] msg	- Log message
 */
void CLoggerToConsole::Write(char lvl, char, const char* msg)
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
/************************************/

