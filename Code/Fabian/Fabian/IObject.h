#ifndef FABIAN_IOBJECT_H_
#define FABIAN_IOBJECT_H_

#include "FabianDef.h"

// --forward declarations--
class IShader;
class CTransform;
// ------------------------

//******************************************
// !!!! DEPRICATED !!!!
// Interface IObject:
// the base for all drawable or/and updateable objects
// for the game. This includes a transfrom variable to
// move the object arround.
//******************************************
class IObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	IObject(IObject* = nullptr);
	//-------------------------------------
	// Destructor
	virtual ~IObject();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, return false if something failed
	virtual bool Init() = 0;
	//-------------------------------------
	// Updates the object according to dTime
	// p1 in - float, dTime since last update call
	virtual void Update(float) {}
	//-------------------------------------
	// Draws the object on the screen ussing the given shader
	// p1 in - pointer to the shader the object should draw with
	virtual void Draw(IShader*) {}
	//-------------------------------------
	


private:
	DISALLOW_COPY_AND_ASSIGN(IObject);
};

#endif //FABIAN_IOBJECT_H_
