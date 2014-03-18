#ifndef FABIAN_CLOGGERMULTIPLE_H_
#define FABIAN_CLOGGERMULTIPLE_H_

#include "ILogger.h"
#include <vector>

////////////////////////////////////////////
//! Class CLoggerMultiple: 
//! ILogger class which combines multiple ILoggers 
//! to allow logging to multiple logs 
//! (ex. log to files and log to console)
////////////////////////////////////////////
class CLoggerMultiple : public ILogger
{
public:
	/************************************/
	/*! Constructor */
	CLoggerMultiple();
	/************************************/
    /*! This function must NOT be implemented in the header or the 
     * linker will build the code to call the application delete() 
     * function instead of the library delete() function.
	 */
    virtual void Release();
	/************************************/

	/************************************/
	/*! Adds an new ILogger to log to
	 * @param [in] pLogger - Pointer to ILogger (takes over ownership)
	 */
	void AddLogger(ILogger* pLogger);
	/************************************/

	/************************************/
	/*! Gets called whenever the logs receives a message 
	 *    and needs it to be actually logged
	 * @param [in] lvl	- FLOG_LVL, useally ERROR, WARNING or INFO
	 * @param [in] id	- FLOG_ID, the place where to write to
	 * @param [in] msg	- Log message
	 */
	virtual void Write(char lvl, char id, const char* msg);
	/************************************/
	
protected:
	/************************************/
	/*! Destructor, 
	 * private so it can only be called by Release();
	 */
	virtual ~CLoggerMultiple();
	/************************************/

private:
	std::vector<ILogger*> m_vLoggers;

	DISALLOW_COPY_AND_ASSIGN(CLoggerMultiple);
};

#endif //FABIAN_CLOGGERMULTIPLE_H_
