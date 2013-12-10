#ifndef FABIAN_CAPPLICATION_H_
#define FABIAN_CAPPLICATION_H_

#include "FabianDef.h"

//******************************************
// Class CApplication:
// the entry point where the OO starts and where
//    the services get added to the kernel
//******************************************
class CApplication
{
public:
	//-------------------------------------
	// Constructor
	CApplication();
	//-------------------------------------
	// Destructor
	virtual ~CApplication();
	//-------------------------------------
	
	//-------------------------------------
	// Called when the service is registered in the kernel
	// p1 in - int, number of arguments past
	// p2 in - char*, array of the past arguments
	// rv - return value of te app	
	int Run(int argc, char *argv[]);
	//-------------------------------------

private:
	DISALLOW_COPY_AND_ASSIGN(CApplication);
};

#endif //FABIAN_CAPPLICATION_H_
