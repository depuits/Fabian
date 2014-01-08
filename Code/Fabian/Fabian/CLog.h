#ifndef FABIAN_CLOG_H_
#define FABIAN_CLOG_H_

#include "FabianDef.h"
#include "LogDef.h"

#include <string>
#include <vector>

// --forward declarations--
class ILogger;
// ------------------------

//******************************************
// Class CLog:
// singleton class used for message logging
// and debugging the application
//******************************************
class CLog
{
public:

	//-------------------------------------
	// Singleton accessor
	static CLog& Get();
	//-------------------------------------
	// Destructor
	virtual ~CLog();
	//-------------------------------------

	//-------------------------------------
	// Assign a logger used to do the actual logging
	// p1 in - pointer to ILogger object (takes over ownership)
	// rv - bool, true when succesfully assigned
	bool AssignLogger(ILogger*);
	//-------------------------------------

	//-------------------------------------
	// Registers a message to be re-used for logging
	// p1 in - actuall message
	// rv - int, id of the message
	int RegisterMsg(const std::string&);
	//-------------------------------------

	//-------------------------------------
	// Write an message to the log
	// p1 in - Log Level
	// p2 in - Log id
	// p3 in - Log message, registered id or string message
	// ... - Extra parameters, see sprintf in
	void Write(char, char, unsigned msgId, ...);
	void Write(char, char, const char*, ...);
	//-------------------------------------

private:
	//-------------------------------------
	// Constructor
	CLog();
	//-------------------------------------

	ILogger *m_pLogger;
	std::vector<std::string> m_vLogStrings;

	DISALLOW_COPY_AND_ASSIGN(CLog);
};

#endif //FABIAN_CLOG_H_
