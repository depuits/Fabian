#ifndef FABIAN_CGAMEOBJECT_H_
#define FABIAN_CGAMEOBJECT_H_

#include <Fabian.h>

#include "CTransform.hpp"
#include "IComponent.h"

#include <vector>
#include <algorithm>

////////////////////////////////////////////
//! Class CGameObject: 
//! base gameobject with component system
////////////////////////////////////////////
class CGameObject
{
public:
	/************************************/
	/*! Constructor */
	CGameObject()
		:m_Transform()
		,m_bInitialized(false)
	{
	}
	/************************************/
	/*! Destructor */
	virtual ~CGameObject()
	{
		for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
			delete (*it);
		// and the suspended list
		for(std::vector<IComponent*>::iterator it( m_vpDisabledComponents.begin() ); it != m_vpDisabledComponents.end(); ++it)
			delete (*it);
	}
	/************************************/
	
	/************************************/
	/*! Initializes the object, should be called before any other 
	 *    method of the object.
	 * @return False if something failed
	 */
	virtual bool Init()
	{
		m_bInitialized = true;
		// start all components, enabled and disabled
		for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
			(*it)->Start();
		for(std::vector<IComponent*>::iterator it( m_vpDisabledComponents.begin() ); it != m_vpDisabledComponents.end(); ++it)
			(*it)->Start();

		return true;
	}
	/************************************/
	/*! Updates the object according to dTime
	 * @param [in] fDt - Delta time since last update call
	 */
	virtual void Update(float fDt)
	{
		for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
			(*it)->Update(fDt);
	}
	/************************************/
	/*! Draws the object on the screen */
	virtual void Draw()
	{
		for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
			(*it)->Draw();
	}
	/************************************/
	
	/************************************/
	/*! Gets the transform for this object
	 * @return Pointer to the CTransform object
	 */
	CTransform *Transform()
	{
		return (&m_Transform);
	}
	/************************************/
	
	/************************************/
	/*! Add a component to the gameobject
	 * @param [in] pComp - Pointer to IComponent (takes over ownership)
	 * @return True on success
	 */
	bool AddComponent(IComponent *pComp)
	{
		//check if component isn't alreay added
		if(std::find(m_vpComponents.begin(), m_vpComponents.end(), pComp) != m_vpComponents.end()) // first check if the component is in the list, because most change is its could be here
		{
			Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Component already exists in the list, you shouldn't add the same component twice");
			return false;
		}
		else if(std::find(m_vpDisabledComponents.begin(), m_vpDisabledComponents.end(), pComp) != m_vpDisabledComponents.end()) // then check if it isn't in the disabled list
		{
			Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Component already exists in the disabled component list, try enabling the component in stead");
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
	/************************************/
	/*! Removes and destroys a component from the gameobject
	 * @param [in] pComp - Pointer to IComponent to remove
	 *            (if its found in the component list it will be destroyed)
	 * @return True on success
	 */
	bool RemoveComponent(IComponent *pComp)
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
		Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Could not find Component to remove");
		return false;
	}
	/************************************/
	
	/************************************/
	/// @{
	/*! Disables or enables a component 
	 *    this will disable or re-enable the update and draw of the component
	 * @param [in] pComp - Pointer to IComponent
	 * @return True on success
	 */
	bool DisableComponent(IComponent *pComp)
	{
		Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "GameObject: Disable Component" );
		//check if component is enabled
		std::vector<IComponent*>::iterator it( std::find(m_vpComponents.begin(), m_vpComponents.end(), pComp) );
		if( it != m_vpComponents.end() )
		{
			pComp->UpdateState(FCOMP_STATE_DISABLE);
			m_vpComponents.erase(it);
			m_vpDisabledComponents.push_back(pComp);

			return true;
		}

		Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Could not find Component to disable");
		return false;
	}
	bool EnableComponent(IComponent *pComp)
	{
		Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "GameObject: Enable Component" );
		//check if component is enabled
		std::vector<IComponent*>::iterator it( std::find(m_vpDisabledComponents.begin(), m_vpDisabledComponents.end(), pComp) );
		if( it != m_vpDisabledComponents.end() )
		{
			pComp->UpdateState(FCOMP_STATE_ENABLE);
			m_vpDisabledComponents.erase(it);
			m_vpComponents.push_back(pComp);

			return true;
		}

		Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "GameObject: Could not find Component to enable");
		return false;
	}
	/// @}
	/************************************/
	
	/************************************/
	/*! Find the first component of type T
	 * @return Pointer to the component or nullptr if none is found
	 * @internal Must be in header because of template
	 */
	template<typename T>
	T *GetComponentOfType()
	{
		// check for activated components
		for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		{
			T* val = dynamic_cast<T*>(*it);
			if (val != nullptr)
				return val;
		}

		// check for deactivated components
		for(std::vector<IComponent*>::iterator it( m_vpDisabledComponents.begin() ); it != m_vpDisabledComponents.end(); ++it)
		{
			T* val = dynamic_cast<T*>(*it);
			if (val != nullptr)
				return val;
		}

		return nullptr;
	}
	/************************************/

protected:
	CTransform m_Transform;

	bool m_bInitialized;

private:
	std::vector<IComponent*> m_vpComponents;
	std::vector<IComponent*> m_vpDisabledComponents;

	DISALLOW_COPY_AND_ASSIGN(CGameObject);
};


#endif //FABIAN_CGAMEOBJECT_H_
