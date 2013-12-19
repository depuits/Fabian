#include "CGlobalAccessor.h"


#include "CLog.h"

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
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

void *CGlobalAccessor::GetObject(const std::string& sKey)
{
	FASSERT( m_mpObjects.find(sKey) != m_mpObjects.end() );
	return m_mpObjects[sKey];
}
void CGlobalAccessor::AddObject(const std::string& sKey, void* pObject)
{
	FASSERT( m_mpObjects.find(sKey) == m_mpObjects.end() );
	m_mpObjects[sKey] = pObject;
}



