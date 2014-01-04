#ifndef FABIAN_CLIBRARYLOADER_H_
#define FABIAN_CLIBRARYLOADER_H_

#include "FabianDef.h"
#include <string>
#include <vector>

//******************************************
// Class CLibraryLoader:
// object for loading and unloading dynamic librarys
// when this object get destroyed then all loaded
// librarys get unloaded
//******************************************
class CLibraryLoader
{
public:
	//-------------------------------------
	// Constructor
	CLibraryLoader();
	//-------------------------------------
	// Destructor
	virtual ~CLibraryLoader();
	//-------------------------------------
	
	//-------------------------------------
	// loads library into memory returning an acces id
	// p1 in - name and path of the library to load
	// rv - int, returns the id for the library (-1 on fail)
	int LoadLib(const char*);
	//-------------------------------------
	// unloads a specific library from memory
	// p1 in - id of the library to unload
	// rv - bool, returns false if there was no lib 
	//         linked to the id
	bool UnLoadLib(int);
	//-------------------------------------
	
	//-------------------------------------
	// gets the pointer to a function from a specific library
	// p1 in - id of the library to load from
	// p2 in - name of the function
	void *GetFunction(int, const char*) const;
	//-------------------------------------

private:
	std::vector<void*> m_vLibs;

	DISALLOW_COPY_AND_ASSIGN(CLibraryLoader);
};

#endif //FABIAN_CLIBRARYLOADER_H_
