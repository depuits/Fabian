#include "CServiceVideoUpdate.h"

#include <gl/glew.h>

#include "CShader.h"
#include "CModel.h"

CShader *g_Shader;
CModel *g_Model;

CServiceVideoUpdate::CServiceVideoUpdate(int priorety)
	:IService(priorety)

	,m_iScreenWidth(800)
	,m_iScreenHeight(600)

	,m_pWindow(nullptr)
	,m_GLContext(NULL)
{
}
CServiceVideoUpdate::~CServiceVideoUpdate()
{
}
	
bool CServiceVideoUpdate::Start()
{
	if( SDL_InitSubSystem(SDL_INIT_VIDEO) == -1 )
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_GENERIC_SUB_INIT_FAIL, "Video", SDL_GetError() );
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	// request openGL 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	int flags = SDL_WINDOW_OPENGL;
	
	m_pWindow = SDL_CreateWindow("Fabian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iScreenWidth, m_iScreenHeight, flags);
	if( m_pWindow == nullptr )
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, SDL_GetError() );
		return false;
	}

	m_GLContext = SDL_GL_CreateContext(m_pWindow);
	if( m_GLContext == NULL )
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, SDL_GetError() );
		SDL_DestroyWindow(m_pWindow);
		return false;
	}
	
	if (glewInit() != GLEW_OK) 
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, SDL_GetError() );
		SDL_DestroyWindow(m_pWindow);
		return false;
	}

	g_Shader = new CShader();
	g_Shader->Load();

	g_Model = new CModel();
	g_Model->Load();

	//hide the mouse cursor
	//SDL_ShowCursor(SDL_DISABLE);

	return true;
}
void CServiceVideoUpdate::Update()
{
	// temp for clearing window	and drawing object
	glClearColor(1.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	g_Shader->Apply();
	g_Model->Draw();

	// swap the buffers
	SDL_GL_SwapWindow(m_pWindow);
}
void CServiceVideoUpdate::Stop()
{
	delete g_Model;
	delete g_Shader;

    // Close and destroy the window
    SDL_DestroyWindow(m_pWindow);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

