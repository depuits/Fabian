#ifndef FABIAN_CGLOBALACCESSOR_H_
#define FABIAN_CGLOBALACCESSOR_H_

#include "FabianDef.h"
#include <map>

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
	
	void *GetObject(const std::string&);
	//overides old values
	void AddObject(const std::string&, void*);

private:
	//-------------------------------------
	// Constructor
	CGlobalAccessor();
	//-------------------------------------

	std::map<std::string, void*> m_mpObjects;

	DISALLOW_COPY_AND_ASSIGN(CGlobalAccessor);
};

#endif //FABIAN_CGLOBALACCESSOR_H_
