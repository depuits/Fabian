#ifndef FABIAN_CINPUTSDL_H_
#define FABIAN_CINPUTSDL_H_

#include "FabianDef.h"
#include "IInput.h"

class CInputSDL : public IInput
{
public:
	CInputSDL();
	virtual ~CInputSDL();
	
	virtual KeyState GetKeyState(FKey) const;

	virtual void GetMousePos(int&, int&) const;
	virtual void GetMouseMovement(int&, int&) const;

	virtual void LockMouse(bool);
	
	virtual void Update();

protected:
	bool m_bLockMouse;
	int m_iMPosX, 
		m_iMPosY,
		m_iLastMPosX, 
		m_iLastMPosY;

private:
	DISALLOW_COPY_AND_ASSIGN(CInputSDL);
};

#endif //FABIAN_CINPUTSDL_H_
