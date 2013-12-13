#ifndef FABIAN_CCOMPPLAYER_H_
#define FABIAN_CCOMPPLAYER_H_

#include "IComponent.h"


//******************************************
// Class CCompPlayer:
// test component class
//******************************************
class CCompPlayer : public IComponent
{
public:
	//-------------------------------------
	// Constructor
	CCompPlayer();
	//-------------------------------------
	// Destructor
	virtual ~CCompPlayer();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the component
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
