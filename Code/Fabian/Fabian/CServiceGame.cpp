#include "CServiceGame.h"

#include <gl/glew.h>

#include "IShader.h"
#include "CModel.h"
#include "CCamera.h"
#include "CTransform.h"

CCamera *g_Camera;
IShader *g_Shader;
CModel *g_Model;

CServiceGame::CServiceGame(int priorety)
	:IService(priorety)
{
}
CServiceGame::~CServiceGame()
{
}
	
bool CServiceGame::Start()
{
	g_Camera = new CCamera();
	g_Camera->Init();
	g_Camera->Transform()->SetPos( glm::vec3(8,3,0) );
	g_Camera->Transform()->SetRot( glm::vec3(0,0,0.3f) );
	
	g_Model = new CModel();
	g_Model->Init();
	g_Model->Transform()->SetRot( glm::vec3(0, glm::quarter_pi<float>(),0) );

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
	
	g_Model->Transform()->Rotate( glm::vec3(0, 0.001f,0) );

	g_Shader->Apply();
	g_Camera->Draw(g_Shader);
	g_Model->Draw(g_Shader);
}
void CServiceGame::Stop()
{
	delete g_Model;
	delete g_Shader;
	delete g_Camera;
}

void CServiceGame::MsgProc(ServiceMessage sm)
{
}


