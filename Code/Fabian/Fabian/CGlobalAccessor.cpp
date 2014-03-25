#include "CGlobalAccessor.h"
#include <string>

/************************************/
/*! Singleton accessor 
 * @return Pointer to CGlobalAccessor singleton object
 */
CGlobalAccessor& CGlobalAccessor::Get()
{
	static CGlobalAccessor globalAccessor;
	return globalAccessor;
}
/************************************/
/*! Constructor */
CGlobalAccessor::CGlobalAccessor()
	:IGlobalAccessor()
{
}
/************************************/
/*! Destructor */
CGlobalAccessor::~CGlobalAccessor()
{
}
/************************************/

/************************************/
/*! Get a stored object from the accessor
 * @param [in] key - Name/key of the object
 * @return If found a pointer to the object else nullptr
 */
void *CGlobalAccessor::GetObject(const char* key)
{
	std::string sKey(key);
	FASSERT( m_mpObjects.find(sKey) != m_mpObjects.end() );
	return m_mpObjects[sKey];
}
/************************************/
/*! Add or update an object stored in the accessor
 * @param [in] key - Name/key for the object to update or store
 * @param [in] pObject - Pointer to the object to store
 */
void CGlobalAccessor::AddObject(const char* key, void* pObject)
{
	std::string sKey(key);
	FASSERT( m_mpObjects.find(sKey) == m_mpObjects.end() );
	m_mpObjects[sKey] = pObject;
}
/************************************/


