#include "CLibrary.h"

#if defined WIN32 /*windows*/
#include <windows.h>
#elif defined UNIX /*unix*/
#include <dlfcn.h>
#endif

//******************************************
// Class CLibrary:
// object for loading and unloading a dynamic library
//******************************************

//-------------------------------------
// Constructor
CLibrary::CLibrary()
	:m_pLib(nullptr)
{
}
//-------------------------------------
// Destructor
CLibrary::~CLibrary()
{
#if defined WIN32 /*windows*/
	FreeLibrary((HMODULE)m_pLib);
#elif defined UNIX /*unix*/
	dlclose(m_pLib);
#else
#error PLATFORM NOT IMPLENTED
#endif
}
//-------------------------------------

//-------------------------------------
// loads library into memory returning an acces id
// p1 in - name and path of the library to load
// rv - int, returns true if succeeds
bool CLibrary::Load(const std::string& sFile)
{
	m_pLib =
#if defined WIN32 /*windows*/
	LoadLibraryA(sFile.c_str());
#elif defined UNIX /*unix*/
	dlopen(sFile.c_str(), RTLD_LAZY);
#else
#error PLATFORM NOT IMPLENTED
#endif

	if( m_pLib == nullptr )
		return false;
	return true;
}
//-------------------------------------

//-------------------------------------
// gets the pointer to a function from a specific library
// p1 in - id of the library to load from
// p2 in - name of the function
void *CLibrary::GetFunction(const std::string& sFunc)
{
	if( m_pLib == nullptr )
		return nullptr;

	void *ret=
#if defined WIN32 /*windows*/
		(void *)GetProcAddress((HMODULE)m_pLib, sFunc.c_str());
#elif defined UNIX /*unix*/
		dlsym(m_pLib, sFunc.c_str());
#else
#error PLATFORM NOT IMPLENTED
#endif

	return ret;
}
//-------------------------------------

