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
	static CLog* Get();
	//-------------------------------------
	// Destructor
	virtual ~CLog();
	//-------------------------------------
	
	bool AssignLogger(ILogger*);
	
	int RegisterMsg(const std::string&);

	void Write(char, char, unsigned msgId, ...);
	void Write(char, char, const char*, ...);

private:
	//-------------------------------------
	// Constructor
	CLog();
	//-------------------------------------
	// Singleton variable
	static CLog *m_pInstance;
	//-------------------------------------

	ILogger *m_pLogger;
	std::vector<std::string> m_vLogStrings;

	DISALLOW_COPY_AND_ASSIGN(CLog);
};

#endif //FABIAN_CLOG_H_
