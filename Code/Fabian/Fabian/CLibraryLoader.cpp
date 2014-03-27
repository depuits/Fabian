#include "CLibraryLoader.h"

#if defined WIN32 /*windows*/
#include <windows.h>
#elif defined UNIX /*unix*/
#include <dlfcn.h>
#endif

/************************************/
/*! Constructor */
CLibraryLoader::CLibraryLoader()
{
}
/************************************/
/*! Destructor */
CLibraryLoader::~CLibraryLoader()
{
	UnLoadAll();
}
/************************************/
	
/************************************/
/*! Loads library into memory returning an acces id
 * @param [in] sFile - Name and path of the library to load
 * @return The id for the library (-1 on fail)
 */
int CLibraryLoader::LoadLib(const char* sFile)
{
	void *pLib =
#if defined WIN32 /*windows*/
	LoadLibraryA(sFile);
#elif defined UNIX /*unix*/
	dlopen(sFile, RTLD_LAZY);
#else
#error PLATFORM NOT IMPLEMENTED
#endif

	if( pLib == nullptr )
		return -1;

	// check if the dll is already loaded and check for an empty spot
	int fn(-1);
	for (unsigned i(0); i < m_vLibs.size(); ++i)
	{
		if( m_vLibs[i] == pLib )
			return i;

		if( m_vLibs[i] == nullptr && fn == -1 )
			fn = i;
	}

	if( fn != -1 )
	{
		m_vLibs[fn] = pLib;
		return fn;
	}

	m_vLibs.push_back(pLib);
	return m_vLibs.size() - 1;
}
/************************************/
/*! Unloads a specific library from memory
 * @param [in] id - Id of the library to unload
 * @return False if there was no lib linked to the id
 */
bool CLibraryLoader::UnLoadLib(int id)
{
	if( id < 0 || id >= (int)m_vLibs.size() )
		return false;

	if( m_vLibs[id] == nullptr )
		return false;

#if defined WIN32 /*windows*/
	FreeLibrary((HMODULE)m_vLibs[id]);
#elif defined UNIX /*unix*/
	dlclose(m_vLibs[id]);
#else
#error PLATFORM NOT IMPLEMENTED
#endif

	m_vLibs[id] = nullptr;

	return true;
}
/************************************/
/*! Unloads all libraries from memory */
void CLibraryLoader::UnLoadAll()
{
	//unload all the libs when the objects get deleted
	for (unsigned i(0); i < m_vLibs.size(); ++i)
		UnLoadLib(i);
}
/************************************/
	
/************************************/
/*! Gets the pointer to a function from a specific library
 * @param [in] id - Id of the library to load from
 * @param [in] sFunc - Name of the function
 */
void *CLibraryLoader::GetFunction(int id, const char* sFunc) const
{
	if( id < 0 || id >= (int)m_vLibs.size() )
		return nullptr;

	if( m_vLibs[id] == nullptr )
		return nullptr;

	void *ret=
#if defined WIN32 /*windows*/
		(void *)GetProcAddress((HMODULE)m_vLibs[id], sFunc);
#elif defined UNIX /*unix*/
		dlsym(m_vLibs[id], sFunc);
#else
#error PLATFORM NOT IMPLEMENTED
#endif

	return ret;
}
/************************************/

