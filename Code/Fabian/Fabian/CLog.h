#ifndef FABIAN_CLOG_H_
#define FABIAN_CLOG_H_

#include "FabianDef.h"

#include <string>
#include <vector>

// --forward declarations--
class ILogger;
// ------------------------

enum FLOG_LVL : char
{
	FLOG_LVL_UNKNOWN	 = 0,
	FLOG_LVL_INFO		 = 1,
	FLOG_LVL_WARNING	 = 2,
	FLOG_LVL_ERROR		 = 4
};

enum FLOG_ID : char
{
	FLOG_ID_APP			 = 1,
	FLOG_ID_CLIENT		 = 2,
	FLOG_ID_SERVER		 = 4,
	FLOG_ID_USER		 = 8
};

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
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
	// Assign a logger used to do th actual logging
	// p1 in - pointer to ILogger object
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
	// p1 in -
	// p2 in -
	// p3 in - 
	// Extra parameters, see sprintf in 
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
