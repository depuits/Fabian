#include "CGameObject.h"
#include "IComponent.h"

#include "CLog.h"

//******************************************
// Class CGameObject:
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
CGameObject::CGameObject()
	:m_Transform()
{
}
//-------------------------------------
// Destructor
CGameObject::~CGameObject()
{
	for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		delete (*it);
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool CGameObject::Init()
{
	return true;
}
//-------------------------------------
// Updates the object according to dTime
// p1 in - float, dTime since last update call
void CGameObject::Update(float fDt)
{
	for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		(*it)->Update(fDt);
}
//-------------------------------------
// Draws the object on the screen ussing the given shader
// p1 in - pointer to the shader the object should draw with
void CGameObject::Draw(IShader *pShader)
{
	for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		(*it)->Draw(pShader);
}
//-------------------------------------

//-------------------------------------
// Gets the transform for this object
// rv - pointer to the CTransform object
CTransform *CGameObject::Transform()
{
	return (&m_Transform);
}
//-------------------------------------

void CGameObject::AddComponent(IComponent* pComp)
{
    //check if component isn't alreay added
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Function not FULLY implemented yet");

    //add component when not added yet
	pComp->SetParent(this);
	pComp->Start();
	m_vpComponents.push_back(pComp);
}
void CGameObject::RemoveComponent(IComponent*)
{
	// not implemented yet
	CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Function not implemented yet");
}




