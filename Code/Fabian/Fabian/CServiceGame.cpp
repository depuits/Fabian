#include "CServiceGame.h"

#include "CKernel.h"

#include "IInput.h"
#include "IRenderer.h"
#include "CContentManager.h"

#include "IShader.h"
#include "IImage.h"

#include "CModel.h"
#include "CCamera.h"
#include "CTransform.h"

#include "CLog.h"

CCamera *g_pCamera;
IShader *g_pShader;

IImage	*g_pImage1,
		*g_pImage2,
		*g_pImage3;

CModel	*g_pModel1,
		*g_pModel2,
		*g_pModel3;

int g_iIdLightPos,
	g_iIdLightPower,
	g_iIdLightColor,
	
	g_iIdTexture;

float	g_fMouseSens = 0.05f,
		g_fCamSpeed = 200.0f;

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
float CServiceGame::s_fDtime = 0;

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service 
//            ( the lower the higher the priorety )
CServiceGame::CServiceGame(int priorety)
	:IService(priorety)

	,m_pInput(nullptr)
	,m_pRenderer(nullptr)
	,m_pContent(nullptr)
	,m_dTimer(0)
{
}
//-------------------------------------
// Destructor
CServiceGame::~CServiceGame()
{
}
//-------------------------------------
	
//-------------------------------------
// !!! temp !!!
// gloabal helper class to send SMsg's
void SendMsg(int id, IService *pServ)
{
	SMsgRequest msg(id, pServ);
	CKernel::Get()->SendMessage(&msg);
}
//-------------------------------------
	
//-------------------------------------
// Called when the service is registered in the kernel
// rv - return true on succes, 
//         when false is returned then the service gets deleted	
bool CServiceGame::Start()
{
	CLog::Get()->Write(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Starting" );
	SendMsg(SM_INPUT, this);
	SendMsg(SM_RENDERER, this);

	SMsgTimer msg(TimerCallback);
	CKernel::Get()->SendMessage(&msg);
	
	// just quit when the renderer or input wasn't filled in
	FASSERTR(m_pInput != nullptr);
	FASSERTR(m_pRenderer != nullptr);
	
	m_pRenderer->SetVSync(true); // using fix time in timer vs only vSync because movement feels smoother

	g_pCamera = new CCamera();
	g_pCamera->Init();
	g_pCamera->Transform()->SetPos( glm::vec3(20,10,0) );
	//g_pCamera->Transform()->SetRot( glm::vec3(0,0,0.3f) );
	
	g_pShader = m_pRenderer->LoadShader("Shaders/SimpleShader");
	g_iIdLightPos = g_pShader->GetVarId("LightPosition_worldspace");
	g_iIdLightPower = g_pShader->GetVarId("LightPower");
	g_iIdLightColor = g_pShader->GetVarId("LightColor");

	g_iIdTexture = g_pShader->GetVarId("TextureSampler");
	//g_Mesh = m_pRenderer->LoadMesh("tegels-hi", ".a3d");
	m_pContent = new CContentManager(m_pRenderer);
	g_pImage1 = m_pContent->LoadImage("Textures/img_test.png");
	g_pImage2 = m_pContent->LoadImage("Textures/img_cheryl.jpg");
	g_pImage3 = m_pContent->LoadImage("Textures/CarDiffuseMap.png");

	g_pModel1 = new CModel( m_pContent->LoadMesh("Meshes/teapot.a3d") );
	g_pModel1->Init();
	g_pModel1->Transform()->SetRot( glm::vec3(0, glm::quarter_pi<float>(),0) );
	g_pModel1->Transform()->SetPos( glm::vec3(0,0,2.5f) );
	g_pModel1->Transform()->SetScale( 0.1f );
	
	g_pModel2 = new CModel( m_pContent->LoadMesh("Meshes/cube.a3d") );
	g_pModel2->Init();
	g_pModel2->Transform()->SetPos( glm::vec3(0,0,-2.5f) );
	g_pModel2->Transform()->SetScale( 0.1f );

	g_pModel3 = new CModel( m_pContent->LoadMesh("Meshes/car.a3d") );
	g_pModel3->Init();
	g_pModel3->Transform()->SetRot( glm::vec3(0, glm::quarter_pi<float>(),0) );
	g_pModel3->Transform()->SetPos( glm::vec3(-30,0,0) );
	g_pModel3->Transform()->SetScale( 0.5f );
	
	CLog::Get()->Write(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Started" );
	return true;
}
//-------------------------------------
// Called every time the service has to update
void CServiceGame::Update()
{
	// temp for clearing window	and drawing object
	m_pRenderer->Clear(0.01f, 0.1f, 0.4f, 1.0f);
	
	g_pModel1->Transform()->Rotate( glm::vec3(0,  0.1f * s_fDtime,0) );

	if ( (m_pInput->GetKeyState(FKEY_MRBUTTON) & DOWN) == DOWN )
	{
		int x(0), y(0);
		m_pInput->LockMouse(true);
		m_pInput->GetMouseMovement(x, y);
		g_pCamera->Transform()->Rotate( glm::vec3(0,g_fMouseSens * -x * s_fDtime,0) );
		g_pCamera->Transform()->LocalRotate( glm::vec3(0,0,g_fMouseSens * y * s_fDtime) ); // change this to locale rotation
		
		//m_pInput->LockMouse(300, 300);
	}
	else
		m_pInput->LockMouse(false);
	
	//move forward and backward
	if ( m_pInput->GetKeyState(FKEY_UP) & DOWN )
		g_pCamera->Transform()->LocalMove( glm::vec3(-g_fCamSpeed * s_fDtime, 0, 0) );
	else if ( m_pInput->GetKeyState(FKEY_DOWN) & DOWN )
		g_pCamera->Transform()->LocalMove( glm::vec3(g_fCamSpeed * s_fDtime, 0, 0) );
	//move left and right
	if ( m_pInput->GetKeyState(FKEY_LEFT) & DOWN )
		g_pCamera->Transform()->LocalMove( glm::vec3(0, 0, g_fCamSpeed * s_fDtime) );
	else if ( m_pInput->GetKeyState(FKEY_RIGHT) & DOWN )
		g_pCamera->Transform()->LocalMove( glm::vec3(0, 0, -g_fCamSpeed * s_fDtime) );

	g_pShader->Apply();

	g_pShader->SetVarVec3(g_iIdLightPos, glm::vec3(20, 0, 0));
	g_pShader->SetVarF1(g_iIdLightPower, 1.0f);
	g_pShader->SetVarVec4(g_iIdLightColor, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	g_pCamera->Draw(g_pShader);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); Sorting and camera culling
	g_pShader->SetVarImage(g_iIdTexture, g_pImage1);
	g_pModel1->Draw(g_pShader);
	g_pShader->SetVarImage(g_iIdTexture, g_pImage2);
	g_pModel2->Draw(g_pShader);
	g_pShader->SetVarImage(g_iIdTexture, g_pImage3);
	g_pModel3->Draw(g_pShader);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	m_dTimer += s_fDtime;
	if( (int)m_dTimer % 10 == 0 )
	{
		//m_pRenderer->SetVSync(true);
		//m_pRenderer->SetScreenResolution(800, 600);
		//m_pRenderer->SwitchFullScreen();
	}
}
//-------------------------------------
// Called when the service will be deleted
void CServiceGame::Stop()
{
	CLog::Get()->Write(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Stopping" );
	// we don't delete the mesh and image because it was loaded by de contentloader and it will destroy it for use

	delete g_pModel1;
	delete g_pModel2;
	delete g_pModel3;

	delete g_pCamera;

	delete g_pShader;
	delete m_pContent;
}
//-------------------------------------
	
//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CServiceGame::MsgProc(SMsg* sm)
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
		CLog::Get()->Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Game Service: Stopping (Renderer or Input removed)" );
		this->SetCanKill(true);
		break;
	}
}
//-------------------------------------

//-------------------------------------
// Function used for timer callback
// p1 in - float, delta time
void CServiceGame::TimerCallback(float fDt)
{
	//if( fDt > 0.000000001f )
		s_fDtime = fDt;
		//__debugbreak();

}
//-------------------------------------


