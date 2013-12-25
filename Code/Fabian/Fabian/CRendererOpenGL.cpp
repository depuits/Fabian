#include "CRendererOpenGL.h"

#include <algorithm>
#include <GL/glew.h>
#include "CServiceVideoUpdate.h"

#include "CShaderOpenGL.h"
#include "CMeshOpenGL.h"
#include "CImageOpenGL.h"

//******************************************
// Class CRendererOpenGL:
// IRenderer implementation for OpenGL.
//******************************************

//-------------------------------------
// Constructor
// p1 in - pointer to the VideoUpdate service
//            which created this renderer
CRendererOpenGL::CRendererOpenGL(CServiceVideoUpdate *pServiceParent)
	:m_pServiceParent(pServiceParent)
	,m_bFullScreen(false)
{
}
//-------------------------------------
// Destructor
CRendererOpenGL::~CRendererOpenGL()
{
}
//-------------------------------------

//-------------------------------------
// Switches the window to fullscreen and back
// rv - bool, true if in fullscreen
bool CRendererOpenGL::SwitchFullScreen()
{
	SetFullScreen( !m_bFullScreen );
	return m_bFullScreen;
}
//-------------------------------------
// Sets the window to fullscreen or windowed
// p1 in - bool, goes to fullscreen if true
void CRendererOpenGL::SetFullScreen(bool bFullscreen)
{
	m_bFullScreen = bFullscreen;
	m_pServiceParent->SetFullScreen( m_bFullScreen );
}
//-------------------------------------

//-------------------------------------
// Enable or disable VSync
// p1 in - bool, sets VSync on if true
void CRendererOpenGL::SetVSync(bool bVSync)
{
	if( bVSync )
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);
}
//-------------------------------------

//-------------------------------------
// Sets the screen resolution of this game
// p1 in - int, screen width
// p2 in - int, screen height
void CRendererOpenGL::SetScreenResolution(int w, int h)
{
	m_pServiceParent->SetScreenResolution( w, h );
}
//-------------------------------------

//-------------------------------------
// Clears the backbuffers to 1 color
// p1 in - float, R value
// p2 in - float, G value
// p3 in - float, B value
// p4 in - float, A value
void CRendererOpenGL::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//-------------------------------------

//-------------------------------------
// Loads in a shader from a file and returns it
// p1 in - string, name of the shader file (without extension)
// rv - pointer IShader object and nullptr if failed
IShader *CRendererOpenGL::LoadShader(const std::string& sName)
{
	IShader *pShader = new CShaderOpenGL();
	if( !pShader->Load(sName) )
	{
		delete pShader;
		return nullptr;
	}

	return pShader;
}
//-------------------------------------
// Loads in a mesh from a file and returns it
// p1 in - string, name of the mesh file (without extension)
// p2 in - string, extension of the file
// rv - pointer IMesh object and nullptr if failed
IMesh *CRendererOpenGL::LoadMesh(MeshData* md)
{
	IMesh *pMesh = new CMeshOpenGL();
	if( !pMesh->Load(md) )
	{
		delete pMesh;
		return nullptr;
	}

	return pMesh;
}
//-------------------------------------
// Loads in a image from a file and returns it
// p1 in - pointer to the imagedata for the mesh
// rv - pointer IImage object and nullptr if failed
IImage *CRendererOpenGL::LoadImage(ImageData* id)
{
	IImage *pImage = new CImageOpenGL();
	if( !pImage->Load(id) )
	{
		delete pImage;
		return nullptr;
	}

	return pImage;
}
//-------------------------------------

