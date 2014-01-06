#ifndef FABIAN_CGAMEOBJECT_H_
#define FABIAN_CGAMEOBJECT_H_

#include "FabianDef.h"
#include "CTransform.h"
#include <vector>

// --forward declarations--
class IShader;
class IComponent;
// ------------------------

//******************************************
// Class CGameObject:
// base gameobject with component system
//******************************************
class CGameObject
{
public:
	//-------------------------------------
	// Constructor
	CGameObject();
	//-------------------------------------
	// Destructor
	virtual ~CGameObject();
	//-------------------------------------

	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, return false if something failed
	virtual bool Init();
	//-------------------------------------
	// Updates the object according to dTime
	// p1 in - float, dTime since last update call
	virtual void Update(float);
	//-------------------------------------
	// Draws the object on the screen ussing the given shader
	// p1 in - pointer to the shader the object should draw with
	virtual void Draw();
	//-------------------------------------

	//-------------------------------------
	// Gets the transform for this object
	// rv - pointer to the CTransform object
	CTransform *Transform();
	//-------------------------------------
	
	//-------------------------------------
	// Add a component to the gameobject
	// p1 in - pointer to component (takes over ownership)
	// rv - bool, true if succeeded
	bool AddComponent(IComponent*);
	//-------------------------------------
	// Removes and destroys a component from the gameobject
	// p1 in - pointer to component 
	//            (if its found in the component list it will be destroyed)
	// rv - bool, true if succeeded
	bool RemoveComponent(IComponent*);
	//-------------------------------------
	
	//-------------------------------------
	// Disables or enables a component
	//    this will disable or re-enable the update and draw of the component
	// p1 in - pointer to component 
	//            (if its found in the component list it will be destroyed)
	// rv - bool, true if succeeded
	bool DisableComponent(IComponent*);
	bool EnableComponent(IComponent*);
	//-------------------------------------
	
	//-------------------------------------
	// Find the first component of type T
	// rv - pointer to the component or nullptr if none is found
	template<typename T>
	T *GetComponentOfType();
	//-------------------------------------

protected:
	CTransform m_Transform;

	bool m_bInitialized;

private:
	std::vector<IComponent*> m_vpComponents;
	std::vector<IComponent*> m_vpDisabledComponents;

	DISALLOW_COPY_AND_ASSIGN(CGameObject);
};


// must be in header because of template
template<typename T>
T *CGameObject::GetComponentOfType()
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

#endif //FABIAN_CGAMEOBJECT_H_
