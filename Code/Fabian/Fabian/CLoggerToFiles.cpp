#include "CLoggerToFiles.h"
#include "LogDef.h"

#include <string>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

#include <SDL.h>

/************************************/
/*! Constructor
 * @param [in] bAppend - Append to the already existing file
 */
CLoggerToFiles::CLoggerToFiles(bool bAppend) 
	:ILogger()
	,m_bAppend(bAppend)
{
}
/************************************/
/*! Destructor, 
 * private so it can only be called by Release();
 */
CLoggerToFiles::~CLoggerToFiles()
{
	m_osAppLog.close();
	m_osClientLog.close();
	m_osServerLog.close();
}
/************************************/
/*! This function must NOT be implemented in the header or the 
 * linker will build the code to call the application delete() 
 * function instead of the library delete() function.
 */
void CLoggerToFiles::Release()
{
    delete this;  // called from the right "delete context"
}
/************************************/

/************************************/
/*! Initializes the logger, should be called 
 *    before using or assigning the logger
 * @return False if it failed
 */
bool CLoggerToFiles::Init()
{
	std::ios_base::openmode mode = std::ofstream::out;
	if( m_bAppend )
		mode |= std::ofstream::app;

	m_osAppLog.open("logApp.txt", mode);
	m_osClientLog.open("logClnt.txt", mode);
	m_osServerLog.open("logSrvr.txt", mode);

	return (m_osAppLog.good() && m_osClientLog.good() && m_osServerLog.good() );
}
/************************************/

/************************************/
/*! Gets called whenever the logs receives a message 
 *    and needs it to be actually logged
 * @param [in] lvl	- @ref FLOG_LVL, usually ERROR, WARNING or INFO
 * @param [in] id	- @ref FLOG_ID, the place where to write to
 * @param [in] msg	- Log message
 */
void CLoggerToFiles::Write(char lvl, char id, const char* msg)
{
	time_t rawtime;
	tm * timeinfo;
	time(&rawtime);  /* get current time; same as: timer = time(NULL)  */
	timeinfo = localtime(&rawtime);
	
	char buffer [80];
	strftime (buffer, 80, "%Y-%m-%d - %H:%M:%S ", timeinfo);

	std::string sLvl(buffer);
	Uint32 flag = SDL_MESSAGEBOX_ERROR;

	switch (lvl)
	{
	case FLOG_LVL_ERROR:
		sLvl += "-  ERROR  - ";
		flag = SDL_MESSAGEBOX_ERROR;
		break;
	case FLOG_LVL_WARNING:
		sLvl += "- WARNING - ";
		flag = SDL_MESSAGEBOX_WARNING;
		break;
	case FLOG_LVL_INFO:
		sLvl += "-  INFO   - ";
		flag = SDL_MESSAGEBOX_INFORMATION;
		break;
	default:
		sLvl += "- UNKNOWN - ";
		break;
	}

	if( (id & FLOG_ID_APP) != 0 )
	{
		m_osAppLog << sLvl.c_str() << msg << "\n";
		#ifdef _DEBUG
		m_osAppLog.flush();
		#endif
	}
	if( (id & FLOG_ID_CLIENT) != 0 )
	{
		m_osClientLog << sLvl.c_str() << msg << "\n";
		#ifdef _DEBUG
		m_osClientLog.flush();
		#endif
	}
	if( (id & FLOG_ID_SERVER) != 0 )
	{
		m_osServerLog << sLvl.c_str() << msg << "\n";
		#ifdef _DEBUG
		m_osServerLog.flush();
		#endif
	}
	if( (id & FLOG_ID_USER) != 0 )
	{	
		SDL_ShowSimpleMessageBox(flag, sLvl.c_str(), msg, NULL);
	}
}
/************************************/

