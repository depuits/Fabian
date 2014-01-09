#include "CLog.h"
#include "ILogger.h"
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

//******************************************
// Class CLog:
// singleton class used for message logging
// and debugging the application
//******************************************

//-------------------------------------
// Singleton accessor
CLog& CLog::Get()
{
	static CLog log;
	return log;
}

//-------------------------------------
// Constructor
CLog::CLog()
	:m_pLogger(nullptr)
{
}
//-------------------------------------
// Destructor
CLog::~CLog()
{
	m_pLogger->Release();
}
//-------------------------------------

//-------------------------------------
// Assign a logger used to do the actual logging
// p1 in - pointer to ILogger object
// rv - bool, true when succesfully assigned
bool CLog::AssignLogger(ILogger* pLogger)
{
	if( m_pLogger != nullptr )
		m_pLogger->Release();

	m_pLogger = pLogger;
	return true;
}
//-------------------------------------
	
//-------------------------------------
// Registers a message to be re-used for logging
// p1 in - actuall message
// rv - int, id of the message
int CLog::RegisterMsg(const std::string& sMsg)
{
	m_vLogStrings.push_back(sMsg);
	return ( m_vLogStrings.size() - 1 );
}
//-------------------------------------
	
//-------------------------------------
// Write an message to the log
// p1 in - Log Level
// p2 in - Log id
// p3 in - Log message, registered id or string message
// ... - Extra parameters, see sprintf in 
void CLog::Write(char lvl, char id, unsigned msgId, ...)
{
	va_list args; 
	va_start(args, msgId);
	char szBuf[1024];
	vsprintf(szBuf, m_vLogStrings.at(msgId).c_str(), args);
	va_end(args);

	Write(lvl, id, szBuf);
}
void CLog::Write(char lvl, char id, const char* msg, ...)
{
	FASSERT(m_pLogger != nullptr);
	
	va_list args;
	va_start(args, msg);
	char szBuf[1024];
	vsprintf(szBuf, msg, args);
	va_end(args);

	m_pLogger->Write(lvl, id, szBuf);
}
//-------------------------------------



