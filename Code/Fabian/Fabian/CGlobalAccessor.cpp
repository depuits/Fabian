#include "CGlobalAccessor.h"


#include "CLog.h"

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************

//-------------------------------------
// Singleton accessor
CGlobalAccessor& CGlobalAccessor::Get()
{
	static CGlobalAccessor globalAccessor;
	return globalAccessor;
}

//-------------------------------------
// Constructor
CGlobalAccessor::CGlobalAccessor()
{
}
//-------------------------------------
// Destructor
CGlobalAccessor::~CGlobalAccessor()
{
}
//-------------------------------------





