#ifndef FABIAN_IINPUT_H_
#define FABIAN_IINPUT_H_

#include "FabianDef.h"
#include "InputDef.h"

class IInput
{
public:
	IInput() { };
	virtual ~IInput() { };
	
	virtual KeyState GetKeyState(FKey) const = 0;

	virtual void GetMousePos(int&, int&) const = 0;
	virtual void GetMouseMovement(int&, int&) const = 0;
	
	virtual void LockMouse(bool) = 0;
	virtual void LockMouse(int, int) = 0;
	
protected:

private:
	DISALLOW_COPY_AND_ASSIGN(IInput);
};

#endif //FABIAN_IINPUT_H_
