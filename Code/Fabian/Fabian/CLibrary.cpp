#include "CLibrary.h"

#if defined WIN32 /*windows*/
#include <windows.h>
#elif defined UNIX /*unix*/
#include <dlfcn.h>
#endif

/************************************/
/*! Constructor */
CLibrary::CLibrary()
	:m_pLib(nullptr)
{
}
/************************************/
/*! Destructor */
CLibrary::~CLibrary()
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
bool CLibrary::Load(const  char* sFile)
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
void *CLibrary::GetFunction(const  char* sFunc)
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

