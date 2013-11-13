#ifndef FABIAN_IINPUT_H_
#define FABIAN_IINPUT_H_

#include "FabianDef.h"
#include "InputDef.h"

//******************************************
// Interface IInput:
// this interface provides a way of getting all
// input stages for the game and for manipulating them.
//******************************************
class IInput
{
public:
	//-------------------------------------
	// Constructor
	IInput() { };
	//-------------------------------------
	// Destructor
	virtual ~IInput() { };
	//-------------------------------------
	
	//-------------------------------------
	// Gets the state of a requested key
	// rv - KeyState, the state of the key
	virtual KeyState GetKeyState(FKey) const = 0;
	//-------------------------------------
	
	//-------------------------------------
	// Gets the current position of the mouse relatieve to the window
	// p1 out - int, X value of the position
	// p2 out - int, Y value of the position
	virtual void GetMousePos(int&, int&) const = 0;
	//-------------------------------------
	// Gets the distance the mouse moved since last frame
	// p1 out - int, X value of the movement
	// p2 out - int, Y value of the movement
	virtual void GetMouseMovement(int&, int&) const = 0;
	//-------------------------------------
	
	//-------------------------------------
	// Locks/unlocks the mouse inside the window
	// p1 in - bool, true to lock the mouse and false to free it
	virtual void LockMouse(bool) = 0;
	//-------------------------------------
	// Locks the mouse inside the window at a specific position
	// p1 in - int, X value of the position
	// p2 in - int, Y value of the position
	virtual void LockMouse(int, int) = 0;
	//-------------------------------------

private:
	DISALLOW_COPY_AND_ASSIGN(IInput);
};

#endif //FABIAN_IINPUT_H_
