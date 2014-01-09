#ifndef FABIAN_CCOMPBASE_H_
#define FABIAN_CCOMPBASE_H_

#include "IComponent.h"
#include "CGameObject.hpp"

//******************************************
// Class CCompBase:
// the base implementation of IComponent
//******************************************
class CCompBase : public IComponent
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CCompBase()
		:IComponent()
		,m_pGameObject(nullptr)
	{
	}
	//-------------------------------------
	// Destructor
	virtual ~CCompBase() { }
	//-------------------------------------

	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, return false if something failed
	virtual bool Start() = 0;
	//-------------------------------------
	// Method called when the component gets removed
	virtual void End() {};
	//-------------------------------------
	// Updates the object according to dTime
	// p1 in - float, dTime since last update call
	virtual void Update(float) {}
	//-------------------------------------
	// Draws the object on the screen ussing the given shader
	// p1 in - pointer to the shader the object should draw with
	virtual void Draw() {}
	//-------------------------------------

	//-------------------------------------
	// This method is called when the component states changed
	//    You can also use this method to send custom messages or states
	// p1 in - FCOMP_STATE, state identifier
	virtual void UpdateState(unsigned char) {};
	//-------------------------------------



	//-------------------------------------
	// Enables the component in the gameobject
	void Enable()
	{
		m_pGameObject->EnableComponent(this);
	}
	//-------------------------------------
	// disables the component in the gameobject
	void Disable()
	{
		m_pGameObject->DisableComponent(this);
	}
	//-------------------------------------



protected:
	CGameObject *m_pGameObject;

private:
	void SetParent(CGameObject* pPar)
	{
		FASSERT( pPar != nullptr && m_pGameObject == nullptr );
		m_pGameObject = pPar;
	}

	DISALLOW_COPY_AND_ASSIGN(CCompBase);
};

#endif //FABIAN_CCOMPBASE_H_
