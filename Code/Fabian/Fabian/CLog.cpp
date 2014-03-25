#include "CLog.h"
#include "ILogger.h"
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

/************************************/
/*! Singleton accessor 
 * @return Pointer to CLog singleton object
 */
CLog& CLog::Get()
{
	static CLog log;
	return log;
}

/************************************/
/*! Constructor */
CLog::CLog()
	:m_pLogger(nullptr)
{
}
/************************************/
/*! Destructor */
CLog::~CLog()
{
	m_pLogger->Release();
}
/************************************/

/************************************/
/*! Assign a ILogger used to do the actual logging
 * @param [in] pLogger - Pointer to ILogger object (takes over ownership)
 * @return True when successfully assigned
 */
bool CLog::AssignLogger(ILogger* pLogger)
{
	if( m_pLogger != nullptr )
		m_pLogger->Release();

	m_pLogger = pLogger;
	return true;
}
/************************************/

/************************************/
/*! Registers a message to be re-used for logging
 * @param [in] sMsg - actual message
 * @return Id of the message
 */
int CLog::RegisterMsg(const std::string& sMsg)
{
	m_vLogStrings.push_back(sMsg);
	return ( m_vLogStrings.size() - 1 );
}
/************************************/

/************************************/
/// @{
/*! Write an message to the log
 * @param [in] lvl	- @ref FLOG_LVL, usually ERROR, WARNING or INFO
 * @param [in] id	- @ref FLOG_ID, the place where to write to
 * @param [in] msg	- Log message, registered id or string message
 * @param [in] ...	- Extra parameters, see sprintf
 */
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
/// @}
/************************************/



