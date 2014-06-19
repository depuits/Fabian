#include "CServicePB.h"

#include <Fabian.h>

#include <IInput.h>
#include <IRenderer.h>
#include <IContentManager.h>

#include <IShader.h>
#include <IMaterial.h>
#include <IImage.h>
#include <IMesh.h>


#include <iostream>
#include <fstream>

IMesh* tmpMesh;

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
float CServicePB::s_fDtime = 0;

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CServicePB::CServicePB()
	:CServiceBase()

	,m_pInput(nullptr)
	,m_pRenderer(nullptr)
	,m_pContent(nullptr)
{
}
//-------------------------------------
// Destructor
CServicePB::~CServicePB()
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
bool CServicePB::Start()
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

	m_pContent = Fab_ContentCreateManager(m_pRenderer);
	if( !m_pContent->StartLoading() )
	{
		Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Game Service: Starting content loading failed." );
		return false;
	}


	IShader *pShader = m_pContent->LoadShader("Shaders/SimpleShader");
	pShader->Apply();
	pShader->SetVarVec3(  pShader->GetVarId("LightPosition_worldspace"),    glm::vec3(0, 100, 0));
	pShader->SetVarF1(    pShader->GetVarId("LightPower"),                  1.0f);
	pShader->SetVarVec4(  pShader->GetVarId("LightColor"),                  glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	IImage  *pImage = m_pContent->LoadImage("Textures/CarDiffuseMap.png"),

            *pImageFloor = m_pContent->LoadImage("Textures/FloorDif.png"),
            *pImageWall = m_pContent->LoadImage("Textures/WallDif.png"),
            *pImageFinish = m_pContent->LoadImage("Textures/FinishDif.png"),
            *pImageWater = m_pContent->LoadImage("Textures/WaterDif.png"),

            *pImagePlayer = m_pContent->LoadImage("Textures/PlayerDif.png"),
            *pImageBug01 = m_pContent->LoadImage("Textures/Bug01Dif.png");

	tmpMesh = m_pContent->LoadMesh("Meshes/Player.obj");

	m_pContent->EndLoading();
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Started" );
	return true;
}

//-------------------------------------
// Called every time the service has to update
void CServicePB::Update()
{
	tmpMesh->Draw();
}
//-------------------------------------
// Called when the service will be deleted
void CServicePB::Stop()
{
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Stopping" );

	// we don't delete the mesh and image because it was loaded by de contentloader and it will destroy it for use

    // release the content as last when nothing is using it anymore
	Fab_ContentReleaseManager(m_pContent);
}
//-------------------------------------

//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CServicePB::MsgProc(SMsg* sm)
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
void CServicePB::TimerCallback(float fDt)
{
	//if( fDt > 0.000000001f )
		s_fDtime = fDt;
		//__debugbreak();

}
//-------------------------------------


