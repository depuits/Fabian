#include "CServiceInput.h"

#include "CKernel.h"
#include "CInputSDL.h"


CServiceInput::CServiceInput(int priorety)
	:IService(priorety)
	,m_pInput(nullptr)
{
}
CServiceInput::~CServiceInput()
{
}
	
bool CServiceInput::Start()
{
	m_pInput = new CInputSDL();
	return true;
}
void CServiceInput::Update()
{
	m_pInput->Update();
}
void CServiceInput::Stop()
{
	SMsgInput msg(m_pInput, SM_H_REMOVE);
	CKernel::Get()->SendMessage(&msg);
	delete m_pInput;
}
void CServiceInput::MsgProc(SMsg* sm)
{
	if( sm->id == SM_INPUT + SM_H_REQUEST )
	{
		SMsgInput msg(m_pInput, SM_H_RECEIVE);
		CKernel::Get()->SendMessage(&msg);
	}
}

