#ifndef FABIAN_CINPUTSDL_H_
#define FABIAN_CINPUTSDL_H_

#include "FabianDef.h"
#include "IInput.h"
#include <SDL.h>
#include <map>

class CInputSDL : public IInput
{
public:
	CInputSDL();
	virtual ~CInputSDL();
	
	virtual KeyState GetKeyState(FKey) const;

	virtual void GetMousePos(int&, int&) const;
	virtual void GetMouseMovement(int&, int&) const;

	virtual void LockMouse(bool);
	virtual void LockMouse(int, int);
	
	virtual void Update();

protected:
	virtual KeyState InternalGetKeyState(FKey) const;
	virtual KeyState InternalGetMouseState(FKey) const;
	
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
