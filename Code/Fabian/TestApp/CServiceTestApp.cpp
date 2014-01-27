#include "CServiceTestApp.h"

#include <Fabian.h>

#include <IInput.h>
#include <IRenderer.h>
#include <IContentManager.h>

#include <IShader.h>
#include <IMaterial.h>
#include <IImage.h>

#include "CCompModel.hpp"
#include "CCompCamera.hpp"
#include "CCompControl.hpp"
#include "CCompPrintTransform.hpp"

#include <CGameObject.hpp>

#include <iostream>
#include <fstream>

std::vector<CGameObject*> g_vpGameObjects;

IMaterial   *g_pMatDefault,
            *g_pMatGround,
            *g_pMatWall,
            *g_pMatFinish,
            *g_pMatWater,
            *g_pMatPlayer,
            *g_pMatBug01;

ICamera *g_pCam;

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
float CServiceTestApp::s_fDtime = 0;

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CServiceTestApp::CServiceTestApp()
	:CServiceBase()

	,m_pInput(nullptr)
	,m_pRenderer(nullptr)
	,m_pContent(nullptr)
{
}
//-------------------------------------
// Destructor
CServiceTestApp::~CServiceTestApp()
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
bool CServiceTestApp::Start()
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

    g_pMatDefault = Fab_MatCreateDifTexture(pShader, pImage);
    g_pMatGround = Fab_MatCreateDifTexture(pShader, pImageFloor);
    g_pMatWall = Fab_MatCreateDifTexture(pShader, pImageWall);
    g_pMatFinish = Fab_MatCreateDifTexture(pShader, pImageFinish);
    g_pMatWater = Fab_MatCreateDifTexture(pShader, pImageWater);

	g_pMatPlayer = Fab_MatCreateDifTexture(pShader, pImagePlayer);
	g_pMatBug01 = Fab_MatCreateDifTexture(pShader, pImageBug01);

	CGameObject *pGo = new CGameObject();
	pGo->Init();
	CCompCamera* pCam = new CCompCamera();
	pGo->AddComponent( pCam );
	pGo->AddComponent( new CCompControl() );
	pGo->AddComponent( new CCompPrintTransform() );
	pGo->Transform()->SetPos( glm::vec3(77, 52, 198) );
	pGo->Transform()->SetRot( glm::vec3( glm::radians(-20.0f), glm::radians(-60.0f), glm::radians(24.0f)) );
	g_vpGameObjects.push_back(pGo);
	g_pCam = pCam;
	
	pGo = new CGameObject();
	pGo->AddComponent( new CCompModel(m_pContent->LoadMesh("Meshes/car.obj"), g_pMatDefault) );
	pGo->Transform()->SetPos( glm::vec3(0, 0, 0) );
	pGo->Transform()->SetRot( glm::vec3(0, 0, 0) );
	g_vpGameObjects.push_back(pGo);
	
	pGo = new CGameObject();
	pGo->AddComponent( new CCompModel(m_pContent->LoadMesh("Meshes/Bug01.obj"), g_pMatBug01) );
	pGo->Transform()->SetPos( glm::vec3(0, 0, 100) );
	pGo->Transform()->SetRot( glm::vec3(0, 0, 0) );
	g_vpGameObjects.push_back(pGo);

	pGo = new CGameObject();
	pGo->AddComponent( new CCompModel(m_pContent->LoadMesh("Meshes/Player.obj"), g_pMatPlayer) );
	pGo->Transform()->SetPos( glm::vec3(0, 0, -100) );
	pGo->Transform()->SetRot( glm::vec3(0, 0, 0) );
	g_vpGameObjects.push_back(pGo);




	for (unsigned i(0); i < g_vpGameObjects.size(); ++i)
		g_vpGameObjects[i]->Init();

	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Started" );
	return true;
}

//-------------------------------------
// Called every time the service has to update
void CServiceTestApp::Update()
{
	// update
	for (unsigned i(0); i < g_vpGameObjects.size(); ++i)
		g_vpGameObjects[i]->Update(s_fDtime);

	//draw
	m_pRenderer->Clear(0.01f, 0.1f, 0.1f, 1.0f);
	m_pRenderer->SetActiveCamera(g_pCam);
	for (unsigned i(0); i < g_vpGameObjects.size(); ++i)
		g_vpGameObjects[i]->Draw();
}
//-------------------------------------
// Called when the service will be deleted
void CServiceTestApp::Stop()
{
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Stopping" );
	// we don't delete the mesh and image because it was loaded by de contentloader and it will destroy it for use
	
	for (unsigned i(0); i < g_vpGameObjects.size(); ++i)
		delete g_vpGameObjects[i];
	g_vpGameObjects.clear();

	Fab_ContentReleaseManager(m_pContent);

    g_pMatDefault->Release();
    g_pMatGround->Release();
    g_pMatWall->Release();
    g_pMatFinish->Release();
    g_pMatWater->Release();
    g_pMatPlayer->Release();
    g_pMatBug01->Release();
}
//-------------------------------------

//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CServiceTestApp::MsgProc(SMsg* sm)
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
void CServiceTestApp::TimerCallback(float fDt)
{
	//if( fDt > 0.000000001f )
		s_fDtime = fDt;
		//__debugbreak();

}
//-------------------------------------


