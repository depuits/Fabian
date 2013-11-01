#include "CInputSDL.h"

#include <SDL.h>

CInputSDL::CInputSDL()
	:IInput()
	,m_bLockMouse(false)
	,m_iMPosX(0)
	,m_iMPosY(0)
	,m_iMPosXLast(0)
	,m_iMPosYLast(0)
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
void CInputSDL::GetMouseMovement(int& x, int& y) const
{
	x = m_iMPosXLast - m_iMPosX;
	y = m_iMPosYLast - m_iMPosY;

	/*if( m_bLockMouse )
	{
		x = m_iMPosX;
		y = m_iMPosY;
	}*/
}

void CInputSDL::LockMouse(bool bLockMouse)
{
	m_bLockMouse = bLockMouse;

	/*if( m_bLockMouse )
		SDL_SetRelativeMouseMode( SDL_TRUE );
	else
		SDL_SetRelativeMouseMode( SDL_FALSE );*/
}

void CInputSDL::Update()
{	
	SDL_GetMouseState(&m_iMPosX, &m_iMPosY);

	if( m_bLockMouse )
		//SDL_GetRelativeMouseState(&m_iMPosX, &m_iMPosY);
		SDL_WarpMouseInWindow(NULL, m_iMPosXLast, m_iMPosYLast);
	else
	{
		m_iMPosXLast = m_iMPosX;
		m_iMPosYLast = m_iMPosY;
	}
}


