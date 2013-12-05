#ifndef FABIAN_CIMAGEOPENGL_H_
#define FABIAN_CIMAGEOPENGL_H_

#include "FabianDef.h"
#include "IImage.h"
#include <gl/glew.h>

//******************************************
// Class CImageOpenGL:
// this class is an OpenGL implementation of 
// the IImage interface
//******************************************
class CImageOpenGL : public IImage
{
public:
	//-------------------------------------
	// Constructor
	CImageOpenGL();
	//-------------------------------------
	// Destructor
	virtual ~CImageOpenGL();
	//-------------------------------------
	
	//-------------------------------------
	// Loads and initializes the mesh by loading any needed buffers, etc.
	// p1 in - pointer to the ImageData for the image
	// rv - bool, return false if something failed
	virtual bool Load(ImageData*);
	//-------------------------------------
	
	//-------------------------------------
	// returns the opengl id of the image
	// rv - GLuint, returns the id of the image
	GLuint GetImageId() const;
	//-------------------------------------

private:
	GLuint m_uImageId;

	DISALLOW_COPY_AND_ASSIGN(CImageOpenGL);
};

#endif //FABIAN_CIMAGEOPENGL_H_
