#ifndef FABIAN_ILOGGER_H_
#define FABIAN_ILOGGER_H_

#include "FabianDef.h"

////////////////////////////////////////////
//! Interface ILogger: 
//! ILogger classes are responsible to actually procces 
//! the log messages and print them to the screen or 
//! do other things with it.
////////////////////////////////////////////
class ILogger
{
public:
	/************************************/
	/*! Constructor */
	ILogger() { }
	/************************************/
    /*! This function must not be implemented in the header or the 
     * linker will build the code to call the application delete() 
     * function instead of the library delete() function.
	 */
    virtual void Release() = 0;
	/************************************/
	
	/************************************/
	/*! Gets called whenever the logs receives a message
	 *    and needs it to be actually logged
	 * @param [in] lvl 	- FLOG_LVL, useally ERROR, WARNING or INFO
	 * @param [in] id	- FLOG_ID, the place where to write to
	 * @param [in] msg	- Log message
	 */
	virtual void Write(char lvl, char id, const char* msg) = 0;
	/************************************/

protected:
	/************************************/
	/*! Destructor
	 * @remark private so it can only be called by Release();
	 */
	virtual ~ILogger() { }
	/************************************/
	
private:
	DISALLOW_COPY_AND_ASSIGN(ILogger);
};

#endif //FABIAN_ILOGGER_H_
