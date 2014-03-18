#ifndef FABIAN_CLOG_H_
#define FABIAN_CLOG_H_

#include "FabianDef.h"
#include "LogDef.h"

#include <string>
#include <vector>

// --forward declarations--
class ILogger;
// ------------------------

////////////////////////////////////////////
//! Class CLog: 
//! singleton class used for message logging 
//! and debugging the application
////////////////////////////////////////////
class CLog
{
public:
	/************************************/
	/*! Singleton accessor 
	 * @return Pointer to CLog singleton object
	 */
	static CLog& Get();
	/************************************/
	/*! Destructor */
	virtual ~CLog();
	/************************************/

	/************************************/
	/*! Assign a ILogger used to do the actual logging
	 * @param [in] pLogger - Pointer to ILogger object (takes over ownership)
	 * @return True when succesfully assigned
	 */
	bool AssignLogger(ILogger* pLogger);
	/************************************/

	/************************************/
	/*! Registers a message to be re-used for logging
	 * @param [in] sMsg - actuall message
	 * @return Id of the message
	 */
	int RegisterMsg(const std::string& sMsg);
	/************************************/

	/************************************/
	/// @{
	/*! Write an message to the log
	 * @param [in] lvl	- FLOG_LVL, useally ERROR, WARNING or INFO
	 * @param [in] id	- FLOG_ID, the place where to write to
	 * @param [in] msg	- Log message, registered id or string message
	 * @param [in] ...	- Extra parameters, see sprintf
	 */
	void Write(char, char, unsigned msgId, ...);
	void Write(char, char, const char*, ...);
	/// @}
	/************************************/

private:
	/************************************/
	/*! Constructor */
	CLog();
	/************************************/

	ILogger *m_pLogger;
	std::vector<std::string> m_vLogStrings;

	DISALLOW_COPY_AND_ASSIGN(CLog);
};

#endif //FABIAN_CLOG_H_
