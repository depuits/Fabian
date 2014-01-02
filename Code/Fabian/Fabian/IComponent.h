#ifndef FABIAN_ICOMPONENT_H_
#define FABIAN_ICOMPONENT_H_

#include "FabianDef.h"

// --forward declarations--
class IShader;
class CGameObject;
// ------------------------

// Log level iddentifiers
enum FCOMP_STATE : unsigned char
{
	FCOMP_STATE_ENABLE      = 0,
	FCOMP_STATE_DISABLE	    = 1,

	FCOMP_STATE_USER     	= 32,
	FCOMP_STATE_MAX     	= 255
};

//******************************************
// Interface IObject:
// the base for all drawable or/and updateable objects
// for the game. This includes a transfrom variable to
// move the object arround.
//******************************************
class IComponent
{
	friend class CGameObject;

public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	IComponent();
	//-------------------------------------
	// Destructor
	virtual ~IComponent();
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
	void Enable();
	//-------------------------------------
	// disables the component in the gameobject
	void Disable();
	//-------------------------------------



protected:
	CGameObject *m_pGameObject;

private:
	void SetParent(CGameObject*);

	DISALLOW_COPY_AND_ASSIGN(IComponent);
};

#endif //FABIAN_ICOMPONENT_H_
