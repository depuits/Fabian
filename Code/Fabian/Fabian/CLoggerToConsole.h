#ifndef FABIAN_CLOGGERTOCONSOLE_H_
#define FABIAN_CLOGGERTOCONSOLE_H_

#include "ILogger.h"

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************
class CLoggerToConsole : public ILogger
{
public:
	//-------------------------------------
	// Constructor
	CLoggerToConsole(bool = false);
	//-------------------------------------
	// Destructor
	virtual ~CLoggerToConsole();
	//-------------------------------------
	
	bool Init();
	virtual void Write(char, char, const char*);

private:
	bool m_bWaitOnError;

	DISALLOW_COPY_AND_ASSIGN(CLoggerToConsole);
};

#endif //FABIAN_CLOGGERCONSOLE_H_
