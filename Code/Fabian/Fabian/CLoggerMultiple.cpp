#include "CLoggerMultiple.h"
#include <algorithm>

/************************************/
/*! Constructor */
CLoggerMultiple::CLoggerMultiple()
	:ILogger()
{
}
/************************************/
/*! Destructor, 
 * private so it can only be called by Release();
 */
CLoggerMultiple::~CLoggerMultiple()
{
	for(std::vector<ILogger*>::iterator it( m_vLoggers.begin() ); it != m_vLoggers.end(); ++it)
		(*it)->Release();
}
/************************************/
/*! This function must NOT be implemented in the header or the 
 * linker will build the code to call the application delete() 
 * function instead of the library delete() function.
 */
void CLoggerMultiple::Release()
{
    delete this;  // called from the right "delete context"
}
/************************************/

/************************************/
/*! Adds an new ILogger to log to
 * @param [in] pLogger - Pointer to ILogger (takes over ownership)
 */
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
/************************************/

/************************************/
/*! Gets called whenever the logs receives a message 
 *    and needs it to be actually logged
 * @param [in] lvl	- @ref FLOG_LVL, useally ERROR, WARNING or INFO
 * @param [in] id	- @ref FLOG_ID, the place where to write to
 * @param [in] msg	- Log message
 */
void CLoggerMultiple::Write(char lvl, char id, const char* msg)
{
	for(std::vector<ILogger*>::iterator it( m_vLoggers.begin() ); it != m_vLoggers.end(); ++it)
		(*it)->Write(lvl, id, msg);
}
/************************************/


