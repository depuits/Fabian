#include "IObject.h"
#include "CTransform.h"

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
IObject::IObject(IObject* pPar)
{
	if( pPar != nullptr )
		m_pTransform = new CTransform(pPar->Transform());
	else
		m_pTransform = new CTransform();
}
//-------------------------------------
// Destructor
IObject::~IObject()
{
	delete m_pTransform;
}
//-------------------------------------
	
//-------------------------------------
// Gets the transform for this object
// rv - pointer to the CTransform object
CTransform *IObject::Transform()
{
	return m_pTransform;
}
//-------------------------------------




