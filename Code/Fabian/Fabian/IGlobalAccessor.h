#ifndef FABIAN_IGLOBALACCESSOR_H_
#define FABIAN_IGLOBALACCESSOR_H_

#include "FabianDef.h"

////////////////////////////////////////////
//! Interface IGlobalAccessor: 
//! the GlobalAccessor class is a quick fix for 
//! items which should be accesable from multiple 
//! places without haing to singleton them. 
//! @warning Keep in mind that this object will not destroy 
//! stored objects at any time.
////////////////////////////////////////////
class IGlobalAccessor
{
public:
	/************************************/
	/*! Constructor */
	IGlobalAccessor() { }
	/************************************/
	/*! Destructor */
	virtual ~IGlobalAccessor() { }
	/************************************/
	
	/************************************/
	/*! Get a stored object from the accessor
	 * @param [in] key - Name/key of the object
	 * @return If found a pointer to the object else nullptr
	 */
	virtual void *GetObject(const char* key) = 0;
	/************************************/
	/*! Add or update an object stored in the accessor
	 * @param [in] key - Name/key for the objct to update or store
	 * @param [in] pObject - Pointer to the object to store
	 */
	virtual void AddObject(const char* key, void* pObject) = 0;
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(IGlobalAccessor);
};

#endif //FABIAN_IGLOBALACCESSOR_H_
