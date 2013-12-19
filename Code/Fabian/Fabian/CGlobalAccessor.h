#ifndef FABIAN_CGLOBALACCESSOR_H_
#define FABIAN_CGLOBALACCESSOR_H_

#include "FabianDef.h"

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************
class CGlobalAccessor
{
public:
	//-------------------------------------
	// Singleton accessor
	static CGlobalAccessor& Get();
	//-------------------------------------
	// Destructor
	virtual ~CGlobalAccessor();
	//-------------------------------------
	
private:
	//-------------------------------------
	// Constructor
	CGlobalAccessor();
	//-------------------------------------

	pointer to data

	DISALLOW_COPY_AND_ASSIGN(CGlobalAccessor);
};

#endif //FABIAN_CGLOBALACCESSOR_H_
