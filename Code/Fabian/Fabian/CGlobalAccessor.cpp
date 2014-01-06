#include "CGlobalAccessor.h"


#include "CLog.h"

//******************************************
// Class CGlobalAccessor:
// the GlobalAccessor class is a quick fix for 
// items which should be accesable from multiple 
// places without haing to singleton them.
// Keep in mind that this object will not destroy 
// stored objects at any time.
//******************************************

//-------------------------------------
// Singleton accessor
CGlobalAccessor& CGlobalAccessor::Get()
{
	static CGlobalAccessor globalAccessor;
	return globalAccessor;
}

//-------------------------------------
// Constructor
CGlobalAccessor::CGlobalAccessor()
{
}
//-------------------------------------
// Destructor
CGlobalAccessor::~CGlobalAccessor()
{
}
//-------------------------------------

//-------------------------------------
// Get a stored object from the accessor
// p1 in - name of the object
// rv - if found a pointer to the object else nullptr
void *CGlobalAccessor::GetObject(const std::string& sKey)
{
	FASSERT( m_mpObjects.find(sKey) != m_mpObjects.end() );
	return m_mpObjects[sKey];
}
//-------------------------------------
// Add or update an object stored in the accessor
// p1 in -name for the objct to update or store
// p2 in - a pointer to the object to store
void CGlobalAccessor::AddObject(const std::string& sKey, void* pObject)
{
	FASSERT( m_mpObjects.find(sKey) == m_mpObjects.end() );
	m_mpObjects[sKey] = pObject;
}
//-------------------------------------


