#include "CInputSDL.h"

#include <SDL.h>

CInputSDL::CInputSDL()
	:IInput()
	,m_bLockMouse(false)
	,m_iMPosX(0)
	,m_iMPosY(0)
	,m_iLastMPosX(0)
	,m_iLastMPosY(0)
{
}
CInputSDL::~CInputSDL()
{
}
	
KeyState CInputSDL::GetKeyState(FKey k) const
{
	if( k == FKEY_MLBUTTON )
	{
		if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1) )
			return DOWN;
	}
	return UP;
}

void CInputSDL::GetMousePos(int& x, int& y) const
{
	x = m_iMPosX;
	y = m_iMPosY;
}
void CInputSDL::GetMouseMovement(int& x, int& y) const
{
	if( m_bLockMouse )
	{
		x = 300 - m_iMPosX;
		y = 300 - m_iMPosY;
	}
	else
	{
		x = m_iLastMPosX - m_iMPosX;
		y = m_iLastMPosY - m_iMPosY;
	}
}

void CInputSDL::LockMouse(bool bLockMouse)
{
	m_bLockMouse = bLockMouse;
}

void CInputSDL::Update()
{
	m_iLastMPosX = m_iMPosX;
	m_iLastMPosY = m_iMPosY;
	
	SDL_GetMouseState(&m_iMPosX, &m_iMPosY);

	if( m_bLockMouse )
		SDL_WarpMouseInWindow(NULL, 300, 300);
}


