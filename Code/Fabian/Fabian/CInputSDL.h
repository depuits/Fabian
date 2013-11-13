#ifndef FABIAN_CINPUTSDL_H_
#define FABIAN_CINPUTSDL_H_

#include "FabianDef.h"
#include "IInput.h"
#include <SDL.h>
#include <map>

//******************************************
// Class CInputSDL:
// IInput interface implementation with SDL2
//******************************************
class CInputSDL : public IInput
{
public:
	//-------------------------------------
	// Constructor
	CInputSDL();
	//-------------------------------------
	// Destructor
	virtual ~CInputSDL();
	//-------------------------------------
	
	//-------------------------------------
	// Gets the state of a requested key
	// rv - KeyState, the state of the key
	virtual KeyState GetKeyState(FKey) const;
	//-------------------------------------
	
	//-------------------------------------
	// Gets the current position of the mouse relatieve to the window
	// p1 out - int, X value of the position
	// p2 out - int, Y value of the position
	virtual void GetMousePos(int&, int&) const;
	//-------------------------------------
	// Gets the distance the mouse moved since last frame
	// p1 out - int, X value of the movement
	// p2 out - int, Y value of the movement
	virtual void GetMouseMovement(int&, int&) const;
	//-------------------------------------
	
	//-------------------------------------
	// Locks/unlocks the mouse inside the window
	// p1 in - bool, true to lock the mouse and false to free it
	virtual void LockMouse(bool);
	//-------------------------------------
	// Locks the mouse inside the window at a specific position
	// p1 in - int, X value of the position
	// p2 in - int, Y value of the position
	virtual void LockMouse(int, int);
	//-------------------------------------
	
	//-------------------------------------
	// Update the internal state. This should be 
	//    called each frame, unless the input isn't used
	virtual void Update();
	//-------------------------------------

protected:
	//-------------------------------------
	// Internal method to get the state of a requested key
	//    but only for keyboard buttons
	// rv - KeyState, the state of the key
	virtual KeyState InternalGetKeyState(FKey) const;
	//-------------------------------------
	// Internal method to get the state of a requested key
	//    but only for mouse buttons
	// rv - KeyState, the state of the key
	virtual KeyState InternalGetMouseState(FKey) const;
	//-------------------------------------
	
	std::map<FKey, Uint8> m_mapKeys;
	std::map<FKey, Uint8> m_mapMouse;

	bool m_bLockMouse;
	int m_iMPosX, 
		m_iMPosY,
		m_iMPosXLast, 
		m_iMPosYLast;

	const Uint8	*m_pKeyboardState;
	Uint8		*m_pKeyboardStateOld;
	int m_iKeyCount;

	Uint32	m_uMouseButtons,
			m_uMouseButtonsOld;


private:
	DISALLOW_COPY_AND_ASSIGN(CInputSDL);
};

#endif //FABIAN_CINPUTSDL_H_
