#ifndef FABIAN_CLIBRARY_H_
#define FABIAN_CLIBRARY_H_

#include "FabianDef.h"

////////////////////////////////////////////
//! Class CLibrary: 
//! object for loading and unloading a dynamic libraries
////////////////////////////////////////////
class CLibrary
{
public:
	/************************************/
	/*! Constructor */
	CLibrary();
	/************************************/
	/*! Destructor */
	virtual ~CLibrary();
	/************************************/
	
	/************************************/
	/*! Loads a library into memory 
	 * @param [in] sFile - Name and path of the library to load
	 * @return True on success
	 */
	bool Load(const char* sFile);
	/************************************/
	
	/************************************/
	/*! Gets the pointer to a function in the library
	 * @param [in] sFunc - Name of the function
	 * @return Pointer to the function or 
	 *            nullptr if somethign failed
	 */
	void *GetFunction(const char* sFunc);
	/************************************/

private:
	void *m_pLib;

	DISALLOW_COPY_AND_ASSIGN(CLibrary);
};

#endif //FABIAN_CLIBRARY_H_
