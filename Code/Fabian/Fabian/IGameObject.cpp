#include "IGameObject.h"


//******************************************
// Interface IGameObject:
// this is an layer between the IObject and 
// just the GameObjects. This can be used to 
// differ between an object and gameobject.
// All non standard objects should derive from
// IGameObject instead of the IObject.
//******************************************

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the object to be linked to the parent
IGameObject::IGameObject(IObject *pPar)
	:IObject(pPar)
{
}
//-------------------------------------
// Destructor
IGameObject::~IGameObject()
{
}
//-------------------------------------


