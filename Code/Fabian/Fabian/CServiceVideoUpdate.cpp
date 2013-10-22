#include "CServiceVideoUpdate.h"

// temp test include ( windows need to be removed,  header for opengl 4 should be added, now its v1.1)
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#pragma comment(lib, "opengl32.lib")

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

	//hide the mouse cursor
	//SDL_ShowCursor(SDL_DISABLE);

	return true;
}
void CServiceVideoUpdate::Update()
{
	// temp for clearing window	
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	SDL_GL_SwapWindow(m_pWindow);
}
void CServiceVideoUpdate::Stop()
{
    // Close and destroy the window
    SDL_DestroyWindow(m_pWindow);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

