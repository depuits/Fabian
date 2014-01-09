#ifndef FABIAN_CCOMPRINTTRANSFORM_H_
#define FABIAN_CCOMPRINTTRANSFORM_H_

#include "CCompBase.hpp"
#include <IInput.h>

class IInput;

//******************************************
// Class CCompPlayer:
// test component class
//******************************************
class CCompPrintTransform : public CCompBase
{
public:
	//-------------------------------------
	// Constructor
	CCompPrintTransform()
		:CCompBase()
		,m_pInput(nullptr)
	{
	}
	//-------------------------------------
	// Destructor
	virtual ~CCompPrintTransform()
	{
	}
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the component
	// rv - bool, return false if something failed
	virtual bool Start()
	{
		m_pInput = static_cast<IInput*>(Fab_GlobalAccessorGetObject("Input"));
		return true;
	}
	//-------------------------------------
	// Updates the object according to dTime
	// p1 in - float, dTime since last update call
	virtual void Update(float fDt)
	{
		if ( (m_pInput->GetKeyState(FKEY_RETURN) & DOWN_NEW) == DOWN_NEW )
		{
			Fab_LogWrite(FLOG_LVL_UNKNOWN, FLOG_ID_APP, "pos : %f - %f - %f", 
				m_pGameObject->Transform()->GetPos().x,
				m_pGameObject->Transform()->GetPos().y,
				m_pGameObject->Transform()->GetPos().z );

			Fab_LogWrite(FLOG_LVL_UNKNOWN, FLOG_ID_APP, "rot : %f - %f - %f", 
				m_pGameObject->Transform()->GetRot().x,
				m_pGameObject->Transform()->GetRot().y,
				m_pGameObject->Transform()->GetRot().z );
			
			glm::vec3 euler = glm::eulerAngles(m_pGameObject->Transform()->GetRot());
			Fab_LogWrite(FLOG_LVL_UNKNOWN, FLOG_ID_APP, "rot euler : %f - %f - %f", 
				euler.x,
				euler.y,
				euler.z );
		}
	}
	//-------------------------------------
	
protected:
	IInput* m_pInput;

private:
	DISALLOW_COPY_AND_ASSIGN(CCompPrintTransform);
};

#endif //FABIAN_CCOMPRINTTRANSFORM_H_
