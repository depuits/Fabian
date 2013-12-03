#include "CServiceGame.h"

#include "CKernel.h"

#include "IInput.h"
#include "IRenderer.h"
#include "CContentManager.h"

#include "IShader.h"

#include "CModel.h"
#include "CCamera.h"
#include "CTransform.h"

#include "CLog.h"

CCamera *g_Camera;
IShader *g_Shader;

IMesh* g_Mesh;

CModel *g_Model1;

int g_iIdLightPos,
	g_iIdLightPower,
	g_iIdLightColor;

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
	SendMsg(SM_INPUT, this);
	SendMsg(SM_RENDERER, this);

	SMsgTimer msg(TimerCallback);
	CKernel::Get()->SendMessage(&msg);
	
	// just quit when the renderer or input wasn't filled in
	FASSERTR(m_pInput != nullptr);
	FASSERTR(m_pRenderer != nullptr);
	
	m_pRenderer->SetVSync(true);

	g_Camera = new CCamera();
	g_Camera->Init();
	g_Camera->Transform()->SetPos( glm::vec3(20,10,0) );
	//g_Camera->Transform()->SetRot( glm::vec3(0,0,0.3f) );
	
	g_Shader = m_pRenderer->LoadShader("SimpleShader");
	g_iIdLightPos = g_Shader->GetVarId("LightPosition_worldspace");
	g_iIdLightPower = g_Shader->GetVarId("LightPower");
	g_iIdLightColor = g_Shader->GetVarId("LightColor");
	//g_Mesh = m_pRenderer->LoadMesh("tegels-hi", ".a3d");

	m_pContent = new CContentManager(m_pRenderer);
	g_Mesh = m_pContent->LoadMesh("teapot", ".a3d");

	g_Model1 = new CModel(g_Mesh);
	g_Model1->Init();
	g_Model1->Transform()->SetRot( glm::vec3(0, glm::quarter_pi<float>(),0) );
	g_Model1->Transform()->SetPos( glm::vec3(0,0,0) );
	g_Model1->Transform()->SetScale( 0.1f );
	
	return true;
}
//-------------------------------------
// Called every time the service has to update
void CServiceGame::Update()
{
	// temp for clearing window	and drawing object
	m_pRenderer->Clear(0.01f, 0.1f, 0.4f, 1.0f);
	
	g_Model1->Transform()->Rotate( glm::vec3(0,  0.1f * s_fDtime,0) );

	if ( (m_pInput->GetKeyState(FKEY_MRBUTTON) & DOWN) == DOWN )
	{
		int x(0), y(0);
		m_pInput->LockMouse(true);
		m_pInput->GetMouseMovement(x, y);
		g_Camera->Transform()->Rotate( glm::vec3(0,0.01f * -x * s_fDtime,0) );
		g_Camera->Transform()->LocalRotate( glm::vec3(0,0,0.01f * y * s_fDtime) ); // change this to locale rotation
		
		//m_pInput->LockMouse(300, 300);
	}
	else
		m_pInput->LockMouse(false);
	
	//move forward and backward
	if ( m_pInput->GetKeyState(FKEY_UP) & DOWN )
	{
		g_Camera->Transform()->LocalMove( glm::vec3(-20 * s_fDtime, 0, 0) );
	}
	else if ( m_pInput->GetKeyState(FKEY_DOWN) & DOWN )
	{
		g_Camera->Transform()->LocalMove( glm::vec3(20 * s_fDtime, 0, 0) );
	}
	//move left and right
	if ( m_pInput->GetKeyState(FKEY_LEFT) & DOWN )
	{
		g_Camera->Transform()->LocalMove( glm::vec3(0, 0, 20 * s_fDtime) );
	}
	if ( m_pInput->GetKeyState(FKEY_RIGHT) & DOWN )
	{
		g_Camera->Transform()->LocalMove( glm::vec3(0, 0, -20 * s_fDtime) );
	}
	/*if ( (m_pInput->GetKeyState(FKEY_Z) & DOWN_NEW) == DOWN_NEW )
	{
		g_Camera->Transform()->Move( glm::vec3(200 * m_fDtime, 0, 0) );
	}*/

	g_Shader->Apply();
	g_Shader->SetVarVec3(g_iIdLightPos, glm::vec3(20, 0, 0));
	g_Shader->SetVarF1(g_iIdLightPower, 1.0f);
	g_Shader->SetVarVec4(g_iIdLightColor, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	g_Camera->Draw(g_Shader);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	g_Model1->Draw(g_Shader);
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
	delete g_Model1;
	delete g_Camera;

	delete g_Shader;
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


