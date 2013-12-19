#include "CCompControl.h"

#include "CGameObject.h"
#include "CGlobalAccessor.h"
#include "IInput.h"

//******************************************
// Interface IObject:
// the base for all drawable or/and updateable objects
// for the game. This includes a transfrom variable to
// move the object arround.
//******************************************

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the obbject to be linked to the parent
CCompControl::CCompControl()
	:IComponent()
	,m_fMouseSens(0.05f)
	,m_fCamSpeed(200.0f)
{
}
//-------------------------------------
// Destructor
CCompControl::~CCompControl()
{
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool CCompControl::Start()
{
	m_pInput = static_cast<IInput*>(CGlobalAccessor::Get().GetObject("Input"));
	return true;
}
//-------------------------------------
// Updates the object according to dTime
// p1 in - float, dTime since last update call
void CCompControl::Update(float fDt)
{
	if ( (m_pInput->GetKeyState(FKEY_MRBUTTON) & DOWN) == DOWN )
	{
		int x(0), y(0);
		m_pInput->LockMouse(true);
		m_pInput->GetMouseMovement(x, y);
		m_pGameObject->Transform()->Rotate( glm::vec3(0,m_fMouseSens * -x * fDt,0) );
		m_pGameObject->Transform()->LocalRotate( glm::vec3(0,0,m_fMouseSens * y * fDt) ); // change this to locale rotation
		
		//m_pInput->LockMouse(300, 300);
	}
	else
		m_pInput->LockMouse(false);
	
	//move forward and backward
	if ( m_pInput->GetKeyState(FKEY_UP) & DOWN )
		m_pGameObject->Transform()->LocalMove( glm::vec3(-m_fCamSpeed * fDt, 0, 0) );
	else if ( m_pInput->GetKeyState(FKEY_DOWN) & DOWN )
		m_pGameObject->Transform()->LocalMove( glm::vec3(m_fCamSpeed * fDt, 0, 0) );
	//move left and right
	if ( m_pInput->GetKeyState(FKEY_LEFT) & DOWN )
		m_pGameObject->Transform()->LocalMove( glm::vec3(0, 0, m_fCamSpeed * fDt) );
	else if ( m_pInput->GetKeyState(FKEY_RIGHT) & DOWN )
		m_pGameObject->Transform()->LocalMove( glm::vec3(0, 0, -m_fCamSpeed * fDt) );
}
//-------------------------------------




