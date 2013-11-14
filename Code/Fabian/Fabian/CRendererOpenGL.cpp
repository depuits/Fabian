#include "CRendererOpenGL.h"

#include <algorithm>
#include <GL\glew.h>
#include "CServiceVideoUpdate.h"

#include "CShaderOpenGL.h" // has to change to opengl shader
#include "CMeshOpenGL.h"

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
	for (std::map<std::string, IShader*>::iterator it = m_mShaderMap.begin(); it != m_mShaderMap.end(); ++it)
		delete it->second;
	m_mShaderMap.clear();
	for (std::map<std::string, IMesh*>::iterator it = m_mMeshMap.begin(); it != m_mMeshMap.end(); ++it)
		delete it->second;
	m_mMeshMap.clear();
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
	if ( !IsShaderPresent(sName))
	{
		IShader *pShader = new CShaderOpenGL();
		if( !pShader->Load(sName) )
		{
			delete pShader;
			return nullptr;
		}
		
		m_mShaderMap[sName] = pShader;
	}
	return m_mShaderMap[sName];
}
//-------------------------------------
// Loads in a mesh from a file and returns it 
// p1 in - string, name of the mesh file (without extension)
// p2 in - string, extension of the file
// rv - pointer IMesh object and nullptr if failed
IMesh *CRendererOpenGL::LoadMesh(const std::string& sName, const std::string& sExt)
{
	if ( !IsMeshPresent(sName))
	{
		CMeshOpenGL *pMesh = new CMeshOpenGL();
		if( !pMesh->Load(sName + sExt) )
		{
			delete pMesh;
			return nullptr;
		}
		
		m_mMeshMap[sName] = pMesh;
	}
	return m_mMeshMap[sName];
}
//-------------------------------------

//-------------------------------------
// Checks weither or not the shader or mesh has already been loaded.
// p1 in - string, name of the object file (without extension)
// rv - bool, true if the object is already loaded
bool CRendererOpenGL::IsShaderPresent(const std::string& sKey) const
{
	return  m_mShaderMap.find(sKey) != m_mShaderMap.end();
}
bool CRendererOpenGL::IsMeshPresent(const std::string& sKey) const
{
	return  m_mMeshMap.find(sKey) != m_mMeshMap.end();
}
//-------------------------------------
