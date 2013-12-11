#ifndef FABIAN_CCOMPPLAYER_H_
#define FABIAN_CCOMPPLAYER_H_

#include "IComponent.h"


//******************************************
// Interface IObject:
// the base for all drawable or/and updateable objects
// for the game. This includes a transfrom variable to
// move the object arround.
//******************************************
class CCompPlayer : public IComponent
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CCompPlayer();
	//-------------------------------------
	// Destructor
	virtual ~CCompPlayer();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, return false if something failed
	virtual bool Start();
	//-------------------------------------
	// Updates the object according to dTime
	// p1 in - float, dTime since last update call
	virtual void Update(float);
	//-------------------------------------
	
protected:

private:
	DISALLOW_COPY_AND_ASSIGN(CCompPlayer);
};

#endif //FABIAN_CCOMPPLAYER_H_
