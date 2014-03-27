#ifndef FABIAN_CLIBRARY_H_
#define FABIAN_CLIBRARY_H_

#include "FabianDef.h"

#if defined WIN32 /*windows*/
#include <windows.h>
#elif defined UNIX /*unix*/
#include <dlfcn.h>
#endif

////////////////////////////////////////////
//! Class CLibrary: 
//! object for loading and unloading a dynamic libraries
////////////////////////////////////////////
class CLibrary
{
public:
	/************************************/
	/*! Constructor */
	CLibrary()
		:m_pLib(nullptr)
	{
	}
	/************************************/
	/*! Destructor */
	virtual ~CLibrary()
	{
	#if defined WIN32 /*windows*/
		FreeLibrary((HMODULE)m_pLib);
	#elif defined UNIX /*unix*/
		dlclose(m_pLib);
	#else
	#error PLATFORM NOT IMPLEMENTED
	#endif
	}
	/************************************/
	
	/************************************/
	/*! Loads a library into memory 
	 * @param [in] sFile - Name and path of the library to load
	 * @return True on success
	 */
	bool Load(const char* sFile)
	{
		if( m_pLib != nullptr )
			return false;

		m_pLib =
	#if defined WIN32 /*windows*/
		LoadLibraryA(sFile);
	#elif defined UNIX /*unix*/
		dlopen(sFile, RTLD_LAZY);
	#else
	#error PLATFORM NOT IMPLEMENTED
	#endif

		if( m_pLib == nullptr )
			return false;
		return true;
	}
	/************************************/
	
	/************************************/
	/*! Gets the pointer to a function in the library
	 * @param [in] sFunc - Name of the function
	 * @return Pointer to the function or 
	 *            nullptr if somethign failed
	 */
	void *GetFunction(const char* sFunc)
	{
		if( m_pLib == nullptr )
			return nullptr;

		void *ret=
	#if defined WIN32 /*windows*/
			(void *)GetProcAddress((HMODULE)m_pLib, sFunc);
	#elif defined UNIX /*unix*/
			dlsym(m_pLib, sFunc);
	#else
	#error PLATFORM NOT IMPLEMENTED
	#endif

		return ret;
	}
	/************************************/

private:
	void *m_pLib;

	DISALLOW_COPY_AND_ASSIGN(CLibrary);
};

#endif //FABIAN_CLIBRARY_H_
