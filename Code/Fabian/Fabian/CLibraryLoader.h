#ifndef FABIAN_CLIBRARYLOADER_H_
#define FABIAN_CLIBRARYLOADER_H_

#include "FabianDef.h"
#include <vector>

////////////////////////////////////////////
//! Class CLibraryLoader: 
//! object for loading and unloading dynamic libraries. 
//! When this object get destroyed then all loaded 
//! libraries get unloaded
////////////////////////////////////////////
class CLibraryLoader
{
public:
	/************************************/
	/*! Constructor */
	CLibraryLoader();
	/************************************/
	/*! Destructor */
	virtual ~CLibraryLoader();
	/************************************/
	
	/************************************/
	/*! Loads library into memory returning an acces id
	 * @param [in] sFile - Name and path of the library to load
	 * @return The id for the library (-1 on fail)
	 */
	int LoadLib(const char* sFile);
	/************************************/
	/*! Unloads a specific library from memory
	 * @param [in] id - Id of the library to unload
	 * @return False if there was no lib linked to the id
	 */
	bool UnLoadLib(int id);
	/************************************/
	/*! Unloads all libraries from memory */
	void UnLoadAll();
	/************************************/
	
	/************************************/
	/*! Gets the pointer to a function from a specific library
	 * @param [in] id - Id of the library to load from
	 * @param [in] sFunc - Name of the function
	 */
	void *GetFunction(int id, const char* sFunc) const;
	/************************************/

private:
	std::vector<void*> m_vLibs;

	DISALLOW_COPY_AND_ASSIGN(CLibraryLoader);
};

#endif //FABIAN_CLIBRARYLOADER_H_
