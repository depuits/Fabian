#ifndef FABIAN_ILOGGER_H_
#define FABIAN_ILOGGER_H_

#include "FabianDef.h"

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************
class ILogger
{
public:
	//-------------------------------------
	// Constructor
	ILogger() { }
	//-------------------------------------
	// Destructor
	virtual ~ILogger() { }
	//-------------------------------------
	
	virtual void Write(char, char, const char*) = 0;

private:

	DISALLOW_COPY_AND_ASSIGN(ILogger);
};

#endif //FABIAN_ILOGGER_H_
