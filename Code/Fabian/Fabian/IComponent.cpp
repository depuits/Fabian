#include "IComponent.h"
#include "CGameObject.h"

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
IComponent::IComponent()
	:m_pGameObject(nullptr)
{
}
//-------------------------------------
// Destructor
IComponent::~IComponent()
{
}
//-------------------------------------


//-------------------------------------
// Enables the component in the gameobject
void IComponent::Enable()
{
    m_pGameObject->EnableComponent(this);
}
//-------------------------------------
// disables the component in the gameobject
void IComponent::Disable()
{
    m_pGameObject->DisableComponent(this);
}
//-------------------------------------

void IComponent::SetParent(CGameObject *pPar)
{
	FASSERT( pPar != nullptr && m_pGameObject == nullptr );
	m_pGameObject = pPar;
}






