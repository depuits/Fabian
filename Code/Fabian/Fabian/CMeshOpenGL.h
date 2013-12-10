#ifndef FABIAN_CMESHOPENGL_H_
#define FABIAN_CMESHOPENGL_H_

#include "FabianDef.h"
#include "IMesh.h"

#include <gl/glew.h>

//******************************************
// Class CMeshOpenGL:
// this class is an OpenGL implementation of 
// the IMesh interface
//******************************************
class CMeshOpenGL : public IMesh
{
public:
	//-------------------------------------
	// Constructor
	CMeshOpenGL();
	//-------------------------------------
	// Destructor
	virtual ~CMeshOpenGL();
	//-------------------------------------
	
	//-------------------------------------
	// Loads and initializes the mesh by loading any needed buffers, etc.
	// p1 in - pointer to the meshdata for the mesh
	// rv - bool, return false if something failed
	virtual bool Load(MeshData*);
	//-------------------------------------
	// Calls the internal draw methods
	virtual void Draw();
	//-------------------------------------

private:
	GLuint m_VertexArrayID,
			m_VertexBuffer,
			m_IndexBuffer;
	int m_iIndicesCount;

	DISALLOW_COPY_AND_ASSIGN(CMeshOpenGL);
};

#endif //FABIAN_CMESHOPENGL_H_
