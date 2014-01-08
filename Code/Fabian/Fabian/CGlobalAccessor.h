#ifndef FABIAN_CGLOBALACCESSOR_H_
#define FABIAN_CGLOBALACCESSOR_H_

#include "IGlobalAccessor.h"
#include <map>

//******************************************
// Class CGlobalAccessor:
// the GlobalAccessor class is a quick fix for 
// items which should be accesable from multiple 
// places without haing to singleton them.
// Keep in mind that this object will not destroy 
// stored objects at any time.
//******************************************
class CGlobalAccessor : public IGlobalAccessor
{
public:
	//-------------------------------------
	// Singleton accessor
	static CGlobalAccessor& Get();
	//-------------------------------------
	// Destructor
	virtual ~CGlobalAccessor();
	//-------------------------------------
	
	//-------------------------------------
	// Get a stored object from the accessor
	// p1 in - name of the object
	// rv - if found a pointer to the object else nullptr
	virtual void *GetObject(const char*);
	//-------------------------------------
	// Add or update an object stored in the accessor
	// p1 in -name for the objct to update or store
	// p2 in - a pointer to the object to store
	virtual void AddObject(const char*, void*);
	//-------------------------------------

private:
	//-------------------------------------
	// Constructor
	CGlobalAccessor();
	//-------------------------------------

	std::map<std::string, void*> m_mpObjects;

	DISALLOW_COPY_AND_ASSIGN(CGlobalAccessor);
};

#endif //FABIAN_CGLOBALACCESSOR_H_
