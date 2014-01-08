#include "CServiceInput.h"

#include "Fabian.h"
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
	:CServiceBase(priorety)
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
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Input Service: Starting" );
	m_pInput = new CInputSDL();
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Input Service: Started" );
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
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Input Service: Stopping" );
	SMsgInput msg(m_pInput, SM_H_REMOVE);
	Fab_KernelSendMessage(&msg);
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
		Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Input Service: Input requested" );
		SMsgInput msg(m_pInput, SM_H_RECEIVE);
		SMsg::Cast<SMsgRequest*>(sm)->pService->MsgProc(&msg); // call the caller's msg callback
	}
}
//-------------------------------------

