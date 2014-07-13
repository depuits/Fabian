#include "CPBService.h"

#include <Fabian.h>

#include <IInput.h>
#include <IRenderer.h>
#include <IContentManager.h>

#include "GameObjects\CPBCamera.h"
#include "GameObjects\CPBPlayer.h"
#include "GameObjects\CPBRoom.h"

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
float CPBService::s_fDtime = 0;

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CPBService::CPBService()
	:CServiceBase()

	,m_pInput(nullptr)
	,m_pRenderer(nullptr)
	,m_pContent(nullptr)

	,m_pCamera(nullptr)
	,m_pPlayer(nullptr)
	,m_pRoom(nullptr)
{
}
//-------------------------------------
// Destructor
CPBService::~CPBService()
{
}
//-------------------------------------

//-------------------------------------
// !!! temp !!!
// gloabal helper class to send SMsg's
void SendMsg(int id, IService *pServ)
{
	SMsgRequest msg(id, pServ);
	Fab_KernelSendMessage(&msg);
}
//-------------------------------------

//-------------------------------------
// Called when the service is registered in the kernel
// rv - return true on succes,
//         when false is returned then the service gets deleted
bool CPBService::Start()
{
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Starting" );
	SendMsg(SM_INPUT, this);
	SendMsg(SM_RENDERER, this);

	SMsgTimer msg(TimerCallback);
	Fab_KernelSendMessage(&msg);

	// just quit when the renderer or input wasn't filled in
	if(m_pInput == nullptr || m_pRenderer == nullptr)
		return false;

	m_pRenderer->SetVSync(true);

	// make needed object accesable for user
	Fab_GlobalAccessorAddObject("Input", m_pInput);
	
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: creating game objects." );
	m_pCamera = new CPBCamera();
	m_pPlayer = new CPBPlayer( m_pInput );
	m_pRoom = new CPBRoom( glm::vec2(10, 100) );

	
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: start loading content." );
	m_pContent = Fab_ContentCreateManager(m_pRenderer);
	if( !m_pContent->StartLoading() )
	{
		Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Game Service: Starting content loading failed." );
		return false;
	}

	m_pCamera->LoadData(m_pContent, m_pRenderer);
	m_pPlayer->LoadData(m_pContent, m_pRenderer);
	m_pRoom->LoadData(m_pContent, m_pRenderer);
	
	m_pContent->EndLoading();

	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: finished loading content." );
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: initializing game objects." );

	m_pCamera->Init();
	m_pPlayer->Init();
	m_pRoom->Init();
	
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: setting up objects." );

	m_pPlayer->GetTransform()->SetPos( glm::vec3(0, 0, 0) );

	m_pCamera->GetTransform()->SetRot( glm::vec3(glm::radians(-90.0f), 0, 0) );
	m_pCamera->GetTransform()->SetPos( glm::vec3(0, 15, 0) );

	m_pCamera->SetTarget(m_pPlayer);

	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Started" );
	return true;
}

//-------------------------------------
// Called every time the service has to update
void CPBService::Update()
{
	m_pRoom->Update(s_fDtime);
	m_pPlayer->Update(s_fDtime);
	m_pCamera->Update(s_fDtime);
	
	m_pRenderer->Clear(0.01f, 0.1f, 0.1f, 1.0f);
	m_pRenderer->SetActiveCamera(m_pCamera);

	m_pRoom->Draw();
	m_pPlayer->Draw();
	m_pCamera->Draw();
}
//-------------------------------------
// Called when the service will be deleted
void CPBService::Stop()
{
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Stopping" );

	// we don't delete the mesh and image because it was loaded by de contentloader and it will destroy it for use
	delete m_pRoom;
	delete m_pPlayer;
	delete m_pCamera;

    // release the content as last when nothing is using it anymore
	Fab_ContentReleaseManager(m_pContent);
}
//-------------------------------------

//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CPBService::MsgProc(SMsg* sm)
{
	switch( sm->id )
	{
	case SM_INPUT + SM_H_RECEIVE:
		m_pInput = SMsg::Cast<SMsgInput*>(sm)->pInput;
		break;
	case SM_RENDERER + SM_H_RECEIVE:
		m_pRenderer = SMsg::Cast<SMsgRenderer*>(sm)->pRenderer;
		break;

	case SM_INPUT + SM_H_REMOVE:
	case SM_RENDERER + SM_H_REMOVE:
		Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "Game Service: Stopping (Renderer or Input removed)" );
		Fab_KernelRemoveService(this);
		break;
	}
}
//-------------------------------------

//-------------------------------------
// Function used for timer callback
// p1 in - float, delta time
void CPBService::TimerCallback(float fDt)
{
	//if( fDt > 0.000000001f )
		s_fDtime = fDt;
		//__debugbreak();

}
//-------------------------------------


