#include "CGameObject.h"
#include "IComponent.h"

#include "CLog.h"
#include <algorithm>

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
	,m_bInitialized(false)
{
}
//-------------------------------------
// Destructor
CGameObject::~CGameObject()
{
	for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		delete (*it);
    // and the suspended list
	for(std::vector<IComponent*>::iterator it( m_vpDisabledComponents.begin() ); it != m_vpDisabledComponents.end(); ++it)
		delete (*it);
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool CGameObject::Init()
{
	m_bInitialized = true;
	// start all components, enabled and disabled
	for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		(*it)->Start();
	for(std::vector<IComponent*>::iterator it( m_vpDisabledComponents.begin() ); it != m_vpDisabledComponents.end(); ++it)
		(*it)->Start();

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
void CGameObject::Draw()
{
	for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		(*it)->Draw();
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

bool CGameObject::AddComponent(IComponent *pComp)
{
    //check if component isn't alreay added
    if(std::find(m_vpComponents.begin(), m_vpComponents.end(), pComp) != m_vpComponents.end()) // first check if the component is in the list, because most change is its could be here
    {
        CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Component already exists in the list, you shouldn't add the same component twice");
        return false;
	}
	else if(std::find(m_vpDisabledComponents.begin(), m_vpDisabledComponents.end(), pComp) != m_vpDisabledComponents.end()) // then check if it isn't in the disabled list
    {
        CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Component already exists in the disabled component list, try enabling the component in stead");
        return false;
	}

    //add component when not added yet
	pComp->SetParent(this);
	if( m_bInitialized )
		pComp->Start();
	pComp->UpdateState(FCOMP_STATE_ENABLE);
	m_vpComponents.push_back(pComp);

	return true;
}
bool CGameObject::RemoveComponent(IComponent *pComp)
{
    //check if component is added
    std::vector<IComponent*>::iterator it( std::find(m_vpComponents.begin(), m_vpComponents.end(), pComp) );

    if(it != m_vpComponents.end())
    {
        pComp->UpdateState(FCOMP_STATE_DISABLE);
        pComp->End();
        m_vpComponents.erase(it);
        delete pComp;
        return true;
    }
    else
    {
        it = std::find(m_vpDisabledComponents.begin(), m_vpDisabledComponents.end(), pComp);
        if(it != m_vpDisabledComponents.end())
        {
            pComp->UpdateState(FCOMP_STATE_DISABLE);
            pComp->End();
            m_vpDisabledComponents.erase(it);
            delete pComp;
            return true;
        }
    }

	// not implemented yet
    CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Could not find Component to remove");
	return false;
}

bool CGameObject::DisableComponent(IComponent *pComp)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "GameObject: Disable Component" );
    //check if component is enabled
    std::vector<IComponent*>::iterator it( std::find(m_vpComponents.begin(), m_vpComponents.end(), pComp) );
	if( it != m_vpComponents.end() )
	{
        pComp->UpdateState(FCOMP_STATE_DISABLE);
		m_vpComponents.erase(it);
		m_vpDisabledComponents.push_back(pComp);

		return true;
	}

    CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Could not find Component to disable");
	return false;
}
bool CGameObject::EnableComponent(IComponent *pComp)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "GameObject: Enable Component" );
    //check if component is enabled
    std::vector<IComponent*>::iterator it( std::find(m_vpDisabledComponents.begin(), m_vpDisabledComponents.end(), pComp) );
	if( it != m_vpDisabledComponents.end() )
	{
        pComp->UpdateState(FCOMP_STATE_ENABLE);
		m_vpDisabledComponents.erase(it);
		m_vpComponents.push_back(pComp);

		return true;
	}

    CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Could not find Component to enable");
	return false;
}



