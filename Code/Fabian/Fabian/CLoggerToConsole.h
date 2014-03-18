#ifndef FABIAN_CLOGGERTOCONSOLE_H_
#define FABIAN_CLOGGERTOCONSOLE_H_

#include "ILogger.h"

////////////////////////////////////////////
//! Class CLoggerToConsole: 
//! ILogger class which writes out the log to 
//! a console using color codes
////////////////////////////////////////////
class CLoggerToConsole : public ILogger
{
public:
	/************************************/
	/*! Constructor
	 * @param [in] bWaitOnError - Await user input on error
	 */
	CLoggerToConsole(bool bWaitOnError = false);
	/************************************/
    /*! This function must NOT be implemented in the header or the 
     * linker will build the code to call the application delete() 
     * function instead of the library delete() function.
	 */
    virtual void Release();
	/************************************/
	
	/************************************/
	/*! Initializes the logger, should be called 
	 *    before using or assigning the logger
	 * @return False if it failed
	 */
	bool Init();
	/************************************/

	/************************************/
	/*! Gets called whenever the logs receives a message 
	 *    and needs it to be actually logged
	 * @param [in] lvl	- @ref FLOG_LVL, useally ERROR, WARNING or INFO
	 * @param [in] id	- @ref FLOG_ID, the place where to write to
	 * @param [in] msg	- Log message
	 */
	virtual void Write(char lvl, char id, const char* msg);
	/************************************/
	
protected:
	/************************************/
	/*! Destructor, 
	 * private so it can only be called by Release();
	 */
	virtual ~CLoggerToConsole();
	/************************************/

private:
	bool m_bWaitOnError;

	DISALLOW_COPY_AND_ASSIGN(CLoggerToConsole);
};

#endif //FABIAN_CLOGGERCONSOLE_H_
