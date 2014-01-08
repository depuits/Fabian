#ifndef FABIAN_CLIBRARY_H_
#define FABIAN_CLIBRARY_H_

#include "FabianDef.h"

//******************************************
// Class CLibrary:
// object for loading and unloading a dynamic library
//******************************************
class CLibrary
{
public:
	//-------------------------------------
	// Constructor
	CLibrary();
	//-------------------------------------
	// Destructor
	virtual ~CLibrary();
	//-------------------------------------
	
	//-------------------------------------
	// loads library into memory returning an acces id
	// p1 in - name and path of the library to load
	// rv - int, returns true if succeeds
	bool Load(const char*);
	//-------------------------------------
	
	//-------------------------------------
	// gets the pointer to a function 
	// p1 in - name of the function
	void *GetFunction(const char*);
	//-------------------------------------

private:
	void *m_pLib;

	DISALLOW_COPY_AND_ASSIGN(CLibrary);
};

#endif //FABIAN_CLIBRARY_H_
