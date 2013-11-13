#include "CInputSDL.h"

#include <SDL.h>
#include <string.h>

//******************************************
// Class CInputSDL:
// IInput interface implementation with SDL2
//******************************************

//-------------------------------------
// Constructor
CInputSDL::CInputSDL()
	:IInput()
	,m_bLockMouse(false)
	,m_iMPosX(0)
	,m_iMPosY(0)
	,m_iMPosXLast(0)
	,m_iMPosYLast(0)
	
	,m_pKeyboardState(nullptr)
	,m_pKeyboardStateOld(nullptr)
	,m_iKeyCount(0)

	,m_uMouseButtons(0)
	,m_uMouseButtonsOld(0)
{
	m_pKeyboardState = SDL_GetKeyboardState(&m_iKeyCount);
	m_pKeyboardStateOld = new Uint8[m_iKeyCount];

	// keyboard keys mapping
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_BACK, SDL_SCANCODE_BACKSPACE) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_TAB, SDL_SCANCODE_TAB) );

	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_CLEAR, SDL_SCANCODE_CLEAR) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_RETURN, SDL_SCANCODE_RETURN) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_SHIFT, SDL_SCANCODE_LSHIFT) );	// ---- Multimap L and R
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_CONTROL, SDL_SCANCODE_LCTRL) );	// ---- Multimap L and R
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_MENU, SDL_SCANCODE_LALT) );		// ---- Multimap L and R
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_PAUSE, SDL_SCANCODE_PAUSE) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_CAPITOL, SDL_SCANCODE_CAPSLOCK) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_ESCAPE, SDL_SCANCODE_ESCAPE) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_SPACE, SDL_SCANCODE_SPACE) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_PAGEUP, SDL_SCANCODE_PAGEUP) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_PAGEDOWN, SDL_SCANCODE_PAGEDOWN) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_END, SDL_SCANCODE_END) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_HOME, SDL_SCANCODE_HOME) );

	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_LEFT, SDL_SCANCODE_LEFT) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_UP, SDL_SCANCODE_UP) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_RIGHT, SDL_SCANCODE_RIGHT) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_DOWN, SDL_SCANCODE_DOWN) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_SNAPSHOT, SDL_SCANCODE_PRINTSCREEN) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_INSERT, SDL_SCANCODE_INSERT) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_DELETE, SDL_SCANCODE_DELETE) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_HELP, SDL_SCANCODE_HELP) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_0, SDL_SCANCODE_0) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_1, SDL_SCANCODE_1) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_2, SDL_SCANCODE_2) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_3, SDL_SCANCODE_3) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_4, SDL_SCANCODE_4) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_5, SDL_SCANCODE_5) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_6, SDL_SCANCODE_6) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_7, SDL_SCANCODE_7) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_8, SDL_SCANCODE_8) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_9, SDL_SCANCODE_9) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_A, SDL_SCANCODE_A) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_B, SDL_SCANCODE_B) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_C, SDL_SCANCODE_C) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_D, SDL_SCANCODE_D) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_E, SDL_SCANCODE_E) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F, SDL_SCANCODE_F) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_G, SDL_SCANCODE_G) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_H, SDL_SCANCODE_H) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_I, SDL_SCANCODE_I) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_J, SDL_SCANCODE_J) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_K, SDL_SCANCODE_K) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_L, SDL_SCANCODE_L) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_M, SDL_SCANCODE_M) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_N, SDL_SCANCODE_N) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_O, SDL_SCANCODE_O) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_P, SDL_SCANCODE_P) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_Q, SDL_SCANCODE_Q) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_R, SDL_SCANCODE_R) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_S, SDL_SCANCODE_S) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_T, SDL_SCANCODE_T) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_U, SDL_SCANCODE_U) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_V, SDL_SCANCODE_V) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_W, SDL_SCANCODE_W) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_X, SDL_SCANCODE_X) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_Y, SDL_SCANCODE_Y) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_Z, SDL_SCANCODE_Z) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_GUI, SDL_SCANCODE_LGUI) );	// ---- Multimap L and R
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_LGUI, SDL_SCANCODE_LGUI) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_RGUI, SDL_SCANCODE_RGUI) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_0, SDL_SCANCODE_KP_0) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_1, SDL_SCANCODE_KP_1) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_2, SDL_SCANCODE_KP_2) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_3, SDL_SCANCODE_KP_3) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_4, SDL_SCANCODE_KP_4) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_5, SDL_SCANCODE_KP_5) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_6, SDL_SCANCODE_KP_6) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_7, SDL_SCANCODE_KP_7) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_8, SDL_SCANCODE_KP_8) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_9, SDL_SCANCODE_KP_9) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_MULTIPLY, SDL_SCANCODE_KP_MULTIPLY) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_ADD, SDL_SCANCODE_KP_PLUS) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_SEPERATOR, SDL_SCANCODE_DECIMALSEPARATOR) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_SUBSTRACT, SDL_SCANCODE_MINUS) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_DECIMAL, SDL_SCANCODE_KP_PERIOD) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NP_DIVIDE, SDL_SCANCODE_KP_DIVIDE) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F1, SDL_SCANCODE_F1) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F2, SDL_SCANCODE_F2) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F3, SDL_SCANCODE_F3) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F4, SDL_SCANCODE_F4) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F5, SDL_SCANCODE_F5) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F6, SDL_SCANCODE_F6) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F7, SDL_SCANCODE_F7) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F8, SDL_SCANCODE_F8) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F9, SDL_SCANCODE_F9) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F10, SDL_SCANCODE_F10) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F11, SDL_SCANCODE_F11) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F12, SDL_SCANCODE_F12) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F13, SDL_SCANCODE_F13) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F14, SDL_SCANCODE_F14) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F15, SDL_SCANCODE_F15) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F16, SDL_SCANCODE_F16) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F17, SDL_SCANCODE_F17) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F18, SDL_SCANCODE_F18) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F19, SDL_SCANCODE_F19) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F20, SDL_SCANCODE_F20) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F21, SDL_SCANCODE_F21) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F22, SDL_SCANCODE_F22) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F23, SDL_SCANCODE_F23) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_F24, SDL_SCANCODE_F24) );
	
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_NUMLOCK, SDL_SCANCODE_NUMLOCKCLEAR) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_SCROLL, SDL_SCANCODE_SCROLLLOCK) );

	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_LSHIFT, SDL_SCANCODE_LSHIFT) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_RSHIFT, SDL_SCANCODE_RSHIFT) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_LCONTROL, SDL_SCANCODE_LCTRL) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_RCONTROL, SDL_SCANCODE_RCTRL) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_LMENU, SDL_SCANCODE_LALT) );
	m_mapKeys.insert( std::pair<FKey, Uint8>(FKEY_RMENU, SDL_SCANCODE_RALT) );
	
	// mouse buttons mapping
	m_mapMouse.insert( std::pair<FKey, Uint8>(FKEY_MLBUTTON, SDL_BUTTON_LEFT) );
	m_mapMouse.insert( std::pair<FKey, Uint8>(FKEY_MRBUTTON, SDL_BUTTON_RIGHT) );
	m_mapMouse.insert( std::pair<FKey, Uint8>(FKEY_MMBUTTON, SDL_BUTTON_MIDDLE) );
	m_mapMouse.insert( std::pair<FKey, Uint8>(FKEY_MXBUTTON1, SDL_BUTTON_X1) );
	m_mapMouse.insert( std::pair<FKey, Uint8>(FKEY_MXBUTTON2, SDL_BUTTON_X2) );
}
//-------------------------------------
// Destructor
CInputSDL::~CInputSDL()
{
	delete m_pKeyboardStateOld;
}
//-------------------------------------
	
//-------------------------------------
// Gets the state of a requested key
// rv - KeyState, the state of the key
KeyState CInputSDL::GetKeyState(FKey k) const
{
	if ( k <= FKEY_H_VMOUSEMAX )
		return InternalGetMouseState(k);

	return InternalGetKeyState(k);
}
//-------------------------------------
	
//-------------------------------------
// Gets the current position of the mouse relatieve to the window
// p1 out - int, X value of the position
// p2 out - int, Y value of the position
void CInputSDL::GetMousePos(int& x, int& y) const
{
	if( m_bLockMouse )
	{
		x = m_iMPosXLast;
		y = m_iMPosYLast;
	}
	else
	{
		x = m_iMPosX;
		y = m_iMPosY;
	}
}
//-------------------------------------
// Gets the distance the mouse moved since last frame
// p1 out - int, X value of the movement
// p2 out - int, Y value of the movement
void CInputSDL::GetMouseMovement(int& x, int& y) const
{
	x = m_iMPosX - m_iMPosXLast;
	y = m_iMPosY - m_iMPosYLast;
}
//-------------------------------------
	
//-------------------------------------
// Locks/unlocks the mouse inside the window
// p1 in - bool, true to lock the mouse and false to free it
void CInputSDL::LockMouse(bool bLockMouse)
{
	m_bLockMouse = bLockMouse;
	if( bLockMouse )
		SDL_SetWindowGrab( SDL_GL_GetCurrentWindow(), SDL_TRUE);
	else 
		SDL_SetWindowGrab( SDL_GL_GetCurrentWindow(), SDL_FALSE);
}
//-------------------------------------
// Locks the mouse inside the window at a specific position
// p1 in - int, X value of the position
// p2 in - int, Y value of the position
void CInputSDL::LockMouse(int x, int y)
{
	LockMouse(true);

	m_iMPosXLast = x;
	m_iMPosYLast = y;
}
//-------------------------------------
	
//-------------------------------------
// Update the internal state. This should be 
//    called each frame, unless the input isn't used
void CInputSDL::Update()
{	
	//update keyboard
	memcpy( m_pKeyboardStateOld, m_pKeyboardState, sizeof(Uint8)*m_iKeyCount );

	//update mouse
	SDL_PumpEvents(); // update needed for mouse
	if( m_bLockMouse )
		SDL_WarpMouseInWindow(NULL, m_iMPosXLast, m_iMPosYLast);
	else
	{
		m_iMPosXLast = m_iMPosX;
		m_iMPosYLast = m_iMPosY;
	}

	m_uMouseButtonsOld = m_uMouseButtons,
	m_uMouseButtons = SDL_GetMouseState(&m_iMPosX, &m_iMPosY);
}
//-------------------------------------

//-------------------------------------
// Internal method to get the state of a requested key
//    but only for keyboard buttons
// rv - KeyState, the state of the key
KeyState CInputSDL::InternalGetKeyState(FKey k) const
{
	Uint8 sdlK( m_mapKeys.at(k) );
	if( m_pKeyboardState[sdlK] )
	{
		if( m_pKeyboardStateOld[sdlK] )
			return DOWN;
		return DOWN_NEW;
	}

	return UP;
}
//-------------------------------------
// Internal method to get the state of a requested key
//    but only for mouse buttons
// rv - KeyState, the state of the key
KeyState CInputSDL::InternalGetMouseState(FKey k) const
{
	Uint8 sdlK( m_mapMouse.at(k) );
	if( m_uMouseButtons & SDL_BUTTON( sdlK ) )
	{
		if( m_uMouseButtonsOld & SDL_BUTTON( sdlK ) )
			return DOWN;
		return DOWN_NEW;
	}
	
	return UP;
}
//-------------------------------------


