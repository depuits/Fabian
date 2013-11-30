#ifndef FABIAN_CLOGGERTOFILES_H_
#define FABIAN_CLOGGERTOFILES_H_

#include "ILogger.h"
#include <fstream>

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************
class CLoggerToFiles : public ILogger
{
public:
	//-------------------------------------
	// Constructor
	CLoggerToFiles();
	//-------------------------------------
	// Destructor
	virtual ~CLoggerToFiles();
	//-------------------------------------
	
	bool Init();

	virtual void Write(char, char, const char*);

private:
    std::ofstream m_osAppLog;
    std::ofstream m_osClientLog;
    std::ofstream m_osServerLog;

	DISALLOW_COPY_AND_ASSIGN(CLoggerToFiles);
};

#endif //FABIAN_CLOGGERTOFILES_H_
