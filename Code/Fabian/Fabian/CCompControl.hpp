#ifndef FABIAN_CCOMPCONTROL_H_
#define FABIAN_CCOMPCONTROL_H_

#include "CCompBase.hpp"
#include <IInput.h>

class IInput;

////////////////////////////////////////////
//! Class CCompPlayer: 
//! test component class used for moving with an object
//! @remark Getting the input from global accessor key "Input"
////////////////////////////////////////////
class CCompControl : public CCompBase
{
public:
	/************************************/
	/*! Constructor */
	CCompControl()
		:CCompBase()
		,m_fMouseSens(0.05f)
		,m_fCamSpeed(200.0f)
		,m_pInput(nullptr)
	{
	}
	/************************************/
	/*! Destructor */
	virtual ~CCompControl()
	{
	}
	/************************************/

	/************************************/
	/*! Initializes the object, should be called before any other
	 *    method of the object.
	 * @return False if something failed
	 */
	virtual bool Start()
	{
		m_pInput = static_cast<IInput*>(Fab_GlobalAccessorGetObject("Input"));
		if( m_pInput == nullptr )
			return false;

		return true;
	}
	/************************************/
	/*! Updates the object according to dTime
	 * @param [in] fDt - Time past since last update call
	 */
	virtual void Update(float fDt)
	{
		if ( (m_pInput->GetKeyState(FKEY_MRBUTTON) & DOWN) == DOWN )
		{
			int x(0), y(0);
			m_pInput->LockMouse(true);
			m_pInput->GetMouseMovement(x, y);
			m_pGameObject->Transform()->Rotate( glm::vec3(0,m_fMouseSens * -x * fDt,0) );
			m_pGameObject->Transform()->LocalRotate( glm::vec3(m_fMouseSens * -y * fDt,0,0) ); // change this to locale rotation
		
			//m_pInput->LockMouse(300, 300);
		}
		else
			m_pInput->LockMouse(false);
	
		//move forward and backward
		if ( m_pInput->GetKeyState(FKEY_UP) & DOWN )
			m_pGameObject->Transform()->LocalMove( glm::vec3(0, 0, -m_fCamSpeed * fDt) );
		else if ( m_pInput->GetKeyState(FKEY_DOWN) & DOWN )
			m_pGameObject->Transform()->LocalMove( glm::vec3(0, 0, m_fCamSpeed * fDt) );
		//move left and right
		if ( m_pInput->GetKeyState(FKEY_LEFT) & DOWN )
			m_pGameObject->Transform()->LocalMove( glm::vec3(-m_fCamSpeed * fDt, 0, 0) );
		else if ( m_pInput->GetKeyState(FKEY_RIGHT) & DOWN )
			m_pGameObject->Transform()->LocalMove( glm::vec3(m_fCamSpeed * fDt, 0, 0) );
	}
	/************************************/
	
protected:
	float	m_fMouseSens,
			m_fCamSpeed;
	IInput* m_pInput;

private:
	DISALLOW_COPY_AND_ASSIGN(CCompControl);
};

#endif //FABIAN_CCOMPCONTROL_H_
