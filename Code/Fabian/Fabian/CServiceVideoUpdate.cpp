#include "CServiceVideoUpdate.h"

#include <GL/glew.h>
#include "CKernel.h"
#include "CRendererOpenGL.h"
#include "CLog.h"

//******************************************
// Class CServiceVideoUpdate:
// service responsable for creating and updating
// the video output
//******************************************

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CServiceVideoUpdate::CServiceVideoUpdate(int priorety)
	:CServiceBase(priorety)

	,m_iScreenWidth(1280)
	,m_iScreenHeight(800)

	,m_pWindow(nullptr)
	,m_GLContext(NULL)

	,m_pRenderer(nullptr)
{
}
//-------------------------------------
// Destructor
CServiceVideoUpdate::~CServiceVideoUpdate()
{
}
//-------------------------------------

//-------------------------------------
// Called when the service is registered in the kernel
// rv - return true on succes,
//         when false is returned then the service gets deleted
bool CServiceVideoUpdate::Start()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Video Service: Starting" );
	if( SDL_InitSubSystem(SDL_INIT_VIDEO) == -1 )
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP | FLOG_ID_USER, "SDL subInit failed (video): %s", SDL_GetError() );
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	int flags = SDL_WINDOW_OPENGL;

	m_pWindow = SDL_CreateWindow("Fabian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iScreenWidth, m_iScreenHeight, flags);
	if( m_pWindow == nullptr )
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP | FLOG_ID_USER, "Failed to create window: (w: %d, h: %d) - %s", m_iScreenWidth, m_iScreenHeight, SDL_GetError() );
		return false;
	}

	m_GLContext = SDL_GL_CreateContext(m_pWindow);
	if( m_GLContext == NULL )
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP | FLOG_ID_USER, "Failed to create opengl context: %s", SDL_GetError() );
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
		return false;
	}

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP | FLOG_ID_USER, "Failed to init GLEW: %s", glewGetErrorString(err) );
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
		return false;
	}

	glEnable(GL_CULL_FACE);
	//glDisable(GL_CULL_FACE);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	m_pRenderer = new CRendererOpenGL(this);

	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Video Service: Started" );
	return true;
}
//-------------------------------------
// Called every time the service has to update
void CServiceVideoUpdate::Update()
{
	// swap the buffers
	SDL_GL_SwapWindow(m_pWindow);

	// check for events like the QUIT
	SDL_Event e;
	while ( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit 
		if( e.type == SDL_QUIT )
		{	
			SMsg msg(SM_QUIT);
			CKernel::Get().SendMessage( &msg );
		}
	}
}
//-------------------------------------
// Called when the service will be deleted
void CServiceVideoUpdate::Stop()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Video Service: Stopping" );
	SMsgRenderer msg(m_pRenderer, SM_H_REMOVE);
	CKernel::Get().SendMessage(&msg);
	delete m_pRenderer;

    // Close and destroy the window
    SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
//-------------------------------------

//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CServiceVideoUpdate::MsgProc(SMsg* sm)
{
	if( sm->id == SM_RENDERER + SM_H_REQUEST )
	{
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Video Service: Renderer requested" );
		SMsgRenderer msg(m_pRenderer, SM_H_RECEIVE);
		SMsg::Cast<SMsgRequest*>(sm)->pService->MsgProc(&msg);
	}
}
//-------------------------------------

//-------------------------------------
// Sets the name of the window
// p1 in - string, name of the window
// rv - bool, true when succeeds
bool CServiceVideoUpdate::SetWindowName(const std::string& sName)
{
	if( m_pWindow == nullptr )
		return false;

	SDL_SetWindowTitle( m_pWindow, sName.c_str() );
	return true;
}
//-------------------------------------
// Sets the visibility of the OS cursor
// p1 in - bool, true to show it, false to hide it
void CServiceVideoUpdate::ShowCursor(bool bShow)
{
	//hide the mouse cursor
	if( bShow )
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);
}
//-------------------------------------

//-------------------------------------
// Helper method for the IRenderer
//-------------------------------------
// Sets the window to fullscreen or back to windowed
// p1 in - bool, goes to fullscreen if true
// rv - bool, true when succeeds
bool CServiceVideoUpdate::SetFullScreen(bool bFullscreen)
{
	if( m_pWindow == nullptr )
		return false;

	if( bFullscreen )
		return ( SDL_SetWindowFullscreen( m_pWindow, SDL_WINDOW_FULLSCREEN) == 0 ); //SDL_WINDOW_FULLSCREEN_DESKTOP
	else
		return ( SDL_SetWindowFullscreen( m_pWindow, 0) == 0 );
}
//-------------------------------------
// Sets the screen resolution of this game
// p1 in - int, screen width
// p2 in - int, screen height
// rv - bool, true when succeeds
bool CServiceVideoUpdate::SetScreenResolution(int w, int h)
{
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "OpenGlVideoService::SetScreenResolution -> Not fully working yet");

	m_iScreenWidth = w;
	m_iScreenHeight = h;

	if( m_pWindow == nullptr )
		return false;

	SDL_DisplayMode target, closest;
	target.w = w;
	target.h = h;
	target.format		= 0; // don't care
	target.refresh_rate	= 0; // don't care
	target.driverdata	= 0; // initialize to 0
	if( SDL_GetClosestDisplayMode(0, &target, &closest) == NULL )
		return false;

	SDL_SetWindowSize( m_pWindow, w, h );
	return ( SDL_SetWindowDisplayMode(m_pWindow, &closest) == 0 );
}
//-------------------------------------


