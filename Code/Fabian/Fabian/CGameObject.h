#ifndef FABIAN_CGAMEOBJECT_H_
#define FABIAN_CGAMEOBJECT_H_

#include "FabianDef.h"
#include "IObject.h"

#include <vector>

class IComponent;

//******************************************
// Interface IGameObject:
// this is an layer between the IObject and 
// just the GameObjects. This can be used to 
// differ between an object and gameobject.
// All non standard objects should derive from
// IGameObject instead of the IObject.
//******************************************
class CGameObject : public IObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
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
	virtual void Draw(IShader*);
	//-------------------------------------


	void AddComponent(IComponent*);
	void RemoveComponent(IComponent*);

	// must be in header because of template
	template<typename T>
	T *GetComponentOfType()
	{
		for(std::vector<IComponent*>::iterator it( m_vpComponents.begin() ); it != m_vpComponents.end(); ++it)
		{
			T* val = dynamic_cast<T*>(*it);
			if (val != nullptr)
				return val;
		}

		return nullptr;
	}

private:
	std::vector<IComponent*> m_vpComponents;

	DISALLOW_COPY_AND_ASSIGN(CGameObject);
};

#endif //FABIAN_CGAMEOBJECT_H_
