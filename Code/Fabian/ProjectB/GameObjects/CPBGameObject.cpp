#include "CPBGameObject.h"


//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CPBGameObject::CPBGameObject()
		:m_Transform()
{
}
//-------------------------------------
// Destructor
CPBGameObject::~CPBGameObject()
{
}
//-------------------------------------

/************************************/
/*! Gets the transform for this object
	* @return Pointer to the CTransform object
	*/
CTransform *CPBGameObject::GetTransform()
{
	return (&m_Transform);
}
/************************************/