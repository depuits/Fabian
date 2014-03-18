#ifndef FABIAN_CLOGGERTOFILES_H_
#define FABIAN_CLOGGERTOFILES_H_

#include "ILogger.h"
#include <fstream>

////////////////////////////////////////////
//! Class CLoggerToFiles: 
//! ILogger class which writes out the log to 
//! files, one file per log id. It uses only the 
//! default log id's. The user log id get shown a 
//! messagebox. 
////////////////////////////////////////////
class CLoggerToFiles : public ILogger
{
public:
	/************************************/
	/*! Constructor
	 * @param [in] bAppend - Append to the already existing file
	 */
	CLoggerToFiles(bool bAppend = true);
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
	virtual ~CLoggerToFiles();
	/************************************/

private:
	bool m_bAppend;
	
    std::ofstream m_osAppLog;
    std::ofstream m_osClientLog;
    std::ofstream m_osServerLog;

	DISALLOW_COPY_AND_ASSIGN(CLoggerToFiles);
};

#endif //FABIAN_CLOGGERTOFILES_H_
