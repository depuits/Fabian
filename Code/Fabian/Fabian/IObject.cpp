#include "IObject.h"
#include "CLog.h"

//******************************************
// Interface IObject:
// the base for all drawable or/and updateable objects
// for the game. This includes a transfrom variable to
// move the object arround.
//******************************************

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the obbject to be linked to the parent
IObject::IObject(IObject*)
{
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Instantiated depricated object: IObject");
}
//-------------------------------------
// Destructor
IObject::~IObject()
{
}
//-------------------------------------
	




