#ifndef FABIAN_IGAMEOBJECT_H_
#define FABIAN_IGAMEOBJECT_H_

#include "FabianDef.h"
#include "IObject.h"

//******************************************
// Interface IGameObject:
// this is an layer between the IObject and 
// just the GameObjects. This can be used to 
// differ between an object and gameobject.
// All non standard objects should derive from
// IGameObject instead of the IObject.
//******************************************
class IGameObject : public IObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	IGameObject(IObject* = nullptr);
	//-------------------------------------
	// Destructor
	virtual ~IGameObject();	
	//-------------------------------------

private:
	DISALLOW_COPY_AND_ASSIGN(IGameObject);
};

#endif //FABIAN_IGAMEOBJECT_H_
