#ifndef FABIAN_CGLOBALACCESSOR_H_
#define FABIAN_CGLOBALACCESSOR_H_

#include "IGlobalAccessor.h"
#include <map>

////////////////////////////////////////////
//! Class CGlobalAccessor: 
//! the GlobalAccessor class is a quick fix for 
//! items which should be accessible from multiple 
//! places without having to singleton them. 
//! @warning Keep in mind that this object will not destroy 
//! stored objects at any time.
////////////////////////////////////////////
class CGlobalAccessor : public IGlobalAccessor
{
public:
	/************************************/
	/*! Singleton accessor 
	 * @return Pointer to CGlobalAccessor singleton object
	 */
	static CGlobalAccessor& Get();
	/************************************/
	/*! Destructor */
	virtual ~CGlobalAccessor();
	/************************************/
	
	/************************************/
	/*! Get a stored object from the accessor
	 * @param [in] key - Name/key of the object
	 * @return If found a pointer to the object else nullptr
	 */
	virtual void *GetObject(const char* key);
	/************************************/
	/*! Add or update an object stored in the accessor
	 * @param [in] key - Name/key for the object to update or store
	 * @param [in] pObject - Pointer to the object to store
	 */
	virtual void AddObject(const char* key, void* pObject);
	/************************************/

private:
	/************************************/
	/*! Constructor */
	CGlobalAccessor();
	/************************************/

	std::map<std::string, void*> m_mpObjects;

	DISALLOW_COPY_AND_ASSIGN(CGlobalAccessor);
};

#endif //FABIAN_CGLOBALACCESSOR_H_
