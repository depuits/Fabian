#ifndef FABIAN_CLOGGERMULTIPLE_H_
#define FABIAN_CLOGGERMULTIPLE_H_

#include "ILogger.h"
#include <vector>

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************
class CLoggerMultiple : public ILogger
{
public:
	//-------------------------------------
	// Constructor
	CLoggerMultiple();
	//-------------------------------------
	// Destructor
	virtual ~CLoggerMultiple();
	//-------------------------------------
	
	void AddLogger(ILogger*);
	virtual void Write(char, char, const char*);

private:
	std::vector<ILogger*> m_vLoggers;

	DISALLOW_COPY_AND_ASSIGN(CLoggerMultiple);
};

#endif //FABIAN_CLOGGERMULTIPLE_H_
