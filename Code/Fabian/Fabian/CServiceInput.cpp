#include "CServiceInput.h"

#include "CKernel.h"
#include "CInputSDL.h"

//******************************************
// Class CServiceInput:
// service responsable giving the input object
// and for updating it.
//******************************************

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service 
//            ( the lower the higher the priorety )
CServiceInput::CServiceInput(int priorety)
	:IService(priorety)
	,m_pInput(nullptr)
{
}
//-------------------------------------
// Destructor
CServiceInput::~CServiceInput()
{
}
//-------------------------------------
	
//-------------------------------------
// Called when the service is registered in the kernel
// rv - return true on succes, 
//         when false is returned then the service gets deleted	
bool CServiceInput::Start()
{
	m_pInput = new CInputSDL();
	return true;
}
//-------------------------------------
// Called every time the service has to update
void CServiceInput::Update()
{
	m_pInput->Update();
}
//-------------------------------------
// Called when the service will be deleted
void CServiceInput::Stop()
{
	SMsgInput msg(m_pInput, SM_H_REMOVE);
	CKernel::Get()->SendMessage(&msg);
	delete m_pInput;
}
//-------------------------------------
	
//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CServiceInput::MsgProc(SMsg* sm)
{
	if( sm->id == SM_INPUT + SM_H_REQUEST )
	{
		SMsgInput msg(m_pInput, SM_H_RECEIVE);
		SMsg::Cast<SMsgRequest*>(sm)->pService->MsgProc(&msg);
	}
}
//-------------------------------------

