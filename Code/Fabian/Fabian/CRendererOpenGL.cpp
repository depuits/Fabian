#include "CRendererOpenGL.h"

#include <algorithm>
#include <GL\glew.h>
#include "CServiceVideoUpdate.h"

#include "IShader.h" // has to change to opengl shader
#include "CMeshOpenGL.h"

CRendererOpenGL::CRendererOpenGL(CServiceVideoUpdate *pServiceParent)
	:m_pServiceParent(pServiceParent)
	,m_bFullScreen(false)
{
}
CRendererOpenGL::~CRendererOpenGL()
{
	for (std::map<std::string, IShader*>::iterator it = m_mShaderMap.begin(); it != m_mShaderMap.end(); ++it)
		delete it->second;
	m_mShaderMap.clear();
	for (std::map<std::string, IMesh*>::iterator it = m_mMeshMap.begin(); it != m_mMeshMap.end(); ++it)
		delete it->second;
	m_mMeshMap.clear();
}
	
//fullscreen
void CRendererOpenGL::SwitchFullScreen()
{
	SetFullScreen( !m_bFullScreen );
}
void CRendererOpenGL::SetFullScreen(bool bFullscreen)
{
	m_bFullScreen = bFullscreen;
	m_pServiceParent->SetFullScreen( m_bFullScreen );
}
//VSync
void CRendererOpenGL::SetVSync(bool bVSync)
{
	if( bVSync )
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);
}
//screen resolution
void CRendererOpenGL::SetScreenResolution(int w, int h)
{
	m_pServiceParent->SetScreenResolution( w, h );
}

void CRendererOpenGL::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}
	
IShader *CRendererOpenGL::LoadShader(const std::string& sName)
{
	if ( !IsShaderPresent(sName))
	{
		IShader *pShader = new IShader();
		pShader->Load(sName);
		
		m_mShaderMap[sName] = pShader;
	}
	return m_mShaderMap[sName];
}
IMesh *CRendererOpenGL::LoadMesh(const std::string& sName, const std::string& sExt)
{
	if ( !IsMeshPresent(sName))
	{
		CMeshOpenGL *pMesh = new CMeshOpenGL();
		pMesh->Load(sName + sExt);
		
		m_mMeshMap[sName] = pMesh;
	}
	return m_mMeshMap[sName];
}

bool CRendererOpenGL::IsShaderPresent(const std::string& sKey) const
{
	return  m_mShaderMap.find(sKey) != m_mShaderMap.end();
}
bool CRendererOpenGL::IsMeshPresent(const std::string& sKey) const
{
	return  m_mMeshMap.find(sKey) != m_mMeshMap.end();
}
