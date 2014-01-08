#include "CLoggerToFiles.h"
#include "LogDef.h"

#include <string>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

#include <SDL.h>

//******************************************
// Class CLoggerToFiles:
// ILogger class which writes out the log to 
// files, one file per log id. It uses only the
// default log id's. The user log id get shown a
// messagebox. 
//******************************************

//-------------------------------------
// Constructor
CLoggerToFiles::CLoggerToFiles(bool bAppend) 
	:ILogger()
	,m_bAppend(bAppend)
{
}
//-------------------------------------
// Destructor
CLoggerToFiles::~CLoggerToFiles()
{
	m_osAppLog.close();
	m_osClientLog.close();
	m_osServerLog.close();
}
//------------------------------------
// This function must not be implemented in the header or the
// linker will build the code to call the application delete()
// function instead of the library delete() function.
void CLoggerToFiles::DeleteThis()
{
    delete this;  // called from the right "delete context"
}
//-------------------------------------
	
//-------------------------------------
// Initializes the logger, should be called
//    before using or assigning the logger
// rv - returns false if it failed-
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
//-------------------------------------

//-------------------------------------
// Gets called whenever the logs receives a message
//    and needs it to be actually logged
// p1 in - log level, useally ERROR, WARNING or INFO
// p2 in - log id, the place where to write to
// p3 in - log message
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
//-------------------------------------

