#include "CServiceGame.h"

#include <gl/glew.h>

#include "CKernel.h"

#include "IInput.h"

#include "IShader.h"
#include "CMeshOpenGL.h"
#include "CModel.h"
#include "CCamera.h"
#include "CTransform.h"

CCamera *g_Camera;
IShader *g_Shader;

IMesh* g_Mesh;

CModel *g_Model1;
CModel *g_Model2;

CServiceGame::CServiceGame(int priorety)
	:IService(priorety)

	,m_pInput(nullptr)
	,m_fDtime(0)
{
}
CServiceGame::~CServiceGame()
{
}
	
bool CServiceGame::Start()
{
	SMsg msg(SM_INPUT_REQUEST);
	CKernel::Get()->SendMessage(&msg);
	//m_pInput->LockMouse(true);

	g_Camera = new CCamera();
	g_Camera->Init();
	g_Camera->Transform()->SetPos( glm::vec3(8,3,0) );
	//g_Camera->Transform()->SetRot( glm::vec3(0,0,0.3f) );
	
	g_Mesh = new CMeshOpenGL();
	g_Mesh->Load(L"tegels-hi.a3d");

	g_Model1 = new CModel(g_Mesh);
	g_Model1->Init();
	g_Model1->Transform()->SetRot( glm::vec3(0, glm::quarter_pi<float>(),0) );
	g_Model1->Transform()->SetPos( glm::vec3(0,5,0) );
	g_Model1->Transform()->SetScale( 2 );

	g_Model2 = new CModel(g_Mesh);
	g_Model2->Init();
	g_Model2->Transform()->SetRot( glm::vec3(0, -glm::quarter_pi<float>(),0) );
	g_Model2->Transform()->SetPos( glm::vec3(0,-10,0) );
	g_Model2->Transform()->SetScale( 2 );

	g_Shader = new IShader();
	g_Shader->Load();

	//hide the mouse cursor
	//SDL_ShowCursor(SDL_DISABLE);

	return true;
}
void CServiceGame::Update()
{

	// temp for clearing window	and drawing object
	glClearColor(0.0f, 0.0f, 0.4f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	g_Model1->Transform()->Rotate( glm::vec3(0,  0.1f * m_fDtime,0) );
	g_Model2->Transform()->Rotate( glm::vec3(0, -0.1f * m_fDtime,0) );

	if ( m_pInput->GetKeyState(FKEY_MLBUTTON) & DOWN )
	{
		m_pInput->LockMouse(true);
		int x(0), y(0);
		m_pInput->GetMouseMovement(x, y);
		g_Camera->Transform()->Rotate( glm::vec3(0,0.1f * -x * m_fDtime,0) );
		g_Camera->Transform()->Rotate( glm::vec3(0,0,0.1f * y * m_fDtime) ); // change this to locale rotation
	}
	else
		m_pInput->LockMouse(false);

	g_Shader->Apply();
	g_Camera->Draw(g_Shader);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	g_Model1->Draw(g_Shader);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	g_Model2->Draw(g_Shader);
}
void CServiceGame::Stop()
{
	delete g_Model1;
	delete g_Model2;
	delete g_Mesh;
	delete g_Shader;
	delete g_Camera;
}

void CServiceGame::MsgProc(SMsg* sm)
{
	switch( sm->id )
	{
	case SM_TIMER_DT:
		m_fDtime = SMsg::Cast<SMsgTimerDT*>(sm)->dt;
		break;
	case SM_INPUT:
		m_pInput = SMsg::Cast<SMsgInput*>(sm)->pInput;
		break;
	}
}


