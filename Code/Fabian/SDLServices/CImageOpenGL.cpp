#include "CImageOpenGL.h"

//-------------------------------------
// Constructor
CImageOpenGL::CImageOpenGL()
	:m_uImageId(0)
	,m_iPos(0)
{
}
//-------------------------------------
// Destructor
CImageOpenGL::~CImageOpenGL()
{
	glDeleteTextures(1, &m_uImageId);
}
//-------------------------------------
	
//-------------------------------------
// Loads and initializes the mesh by loading any needed buffers, etc.
// p1 in - pointer to the ImageData for the image
// rv - bool, return false if something failed
bool CImageOpenGL::Load(ImageData* id)
{
	glGenTextures(1, &m_uImageId);

	glBindTexture(GL_TEXTURE_2D, m_uImageId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, id->w, id->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, id->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}
//-------------------------------------
	
//-------------------------------------
// returns the opengl id of the image
// rv - GLuint, returns the id of the image
GLuint CImageOpenGL::GetImageId() const
{
	return m_uImageId;
}
//-------------------------------------

