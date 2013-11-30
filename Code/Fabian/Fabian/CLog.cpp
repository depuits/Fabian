#include "CLog.h"
#include "ILogger.h"
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************

//-------------------------------------
// Singleton variable
CLog* CLog::m_pInstance = nullptr;
//------------------------------------

//-------------------------------------
// Singleton accessor
CLog* CLog::Get()
{
	if( m_pInstance == nullptr ) m_pInstance = new CLog();
	return m_pInstance;
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
	delete m_pLogger;
	m_pInstance = nullptr;
}
//-------------------------------------

bool CLog::AssignLogger(ILogger* pLogger)
{
	m_pLogger = pLogger;
	return true;
}
	
int CLog::RegisterMsg(const std::string& sMsg)
{
	m_vLogStrings.push_back(sMsg);
	return ( m_vLogStrings.size() - 1 );
}

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



