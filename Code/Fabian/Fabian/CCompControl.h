#ifndef FABIAN_CCOMPCONTROL_H_
#define FABIAN_CCOMPCONTROL_H_

#include "IComponent.h"

class IInput;

//******************************************
// Class CCompPlayer:
// test component class
//******************************************
class CCompControl : public IComponent
{
public:
	//-------------------------------------
	// Constructor
	CCompControl();
	//-------------------------------------
	// Destructor
	virtual ~CCompControl();
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
	float	m_fMouseSens,
			m_fCamSpeed;
	IInput* m_pInput;

private:
	DISALLOW_COPY_AND_ASSIGN(CCompControl);
};

#endif //FABIAN_CCOMPCONTROL_H_
