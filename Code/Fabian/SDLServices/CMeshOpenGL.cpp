#include "CMeshOpenGL.h"

//******************************************
// Class CMeshOpenGL:
// this class is an OpenGL implementation of
// the IMesh interface
//******************************************

//-------------------------------------
// Constructor
CMeshOpenGL::CMeshOpenGL()
	:IMesh()
	,m_VertexArrayID(0)
	,m_VertexBuffer(0)
	,m_IndexBuffer(0)
	,m_iIndicesCount(-1)
{
}
//-------------------------------------
// Destructor
CMeshOpenGL::~CMeshOpenGL()
{
	// release the buffers
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);

	glDeleteVertexArrays(1, &m_VertexArrayID);
}
//-------------------------------------

//-------------------------------------
// Loads and initializes the mesh by loading any needed buffers, etc.
// p1 in - pointer to the meshdata for the mesh
// rv - bool, return false if something failed
//bool CMeshOpenGL::Load(const std::string& file)
bool CMeshOpenGL::Load(MeshData* md)
{
	glGenVertexArrays(1, &m_VertexArrayID);	// create VAO for object

	// ------------------------------------ creater buffers ---------------------------------------------------------------------
	// Generate 1 vertex buffer
	glGenBuffers(1, &m_VertexBuffer);				// create VBO for object
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);	// bind VBO
	glBufferData(GL_ARRAY_BUFFER, md->vCount * sizeof(float), md->vData, GL_STATIC_DRAW); // Give our vertices to OpenGL.

	// Generate a buffer for the indices
	 glGenBuffers(1, &m_IndexBuffer);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, md->iCount * sizeof(unsigned int), md->iData, GL_STATIC_DRAW);
	 m_iIndicesCount = md->iCount;
	// ------------------------------------ creater buffers end ---------------------------------------------------------------------

	glBindVertexArray(m_VertexArrayID);		// bind the VAO

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);	// bind VBO

	int stride = 8 * sizeof(GL_FLOAT);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   stride,             // stride
	   (void*)0            // array buffer offset
	);
	glVertexAttribPointer(
	   1,								// attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,								// size
	   GL_FLOAT,						// type
	   GL_TRUE,							// normalized?
	   stride,							// stride
	   (void*)(3  * sizeof(GL_FLOAT))	// array buffer offset
	);
	glVertexAttribPointer(
	   2,								// attribute 0. No particular reason for 0, but must match the layout in the shader.
	   2,								// size
	   GL_FLOAT,						// type
	   GL_FALSE,						// normalized?
	   stride,							// stride
	   (void*)(6  * sizeof(GL_FLOAT))	// array buffer offset
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBindVertexArray(0); // Disable our Vertex Array Object

	//unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}
//-------------------------------------
// Calls the internal draw methods
void CMeshOpenGL::Draw()
{
	glBindVertexArray(m_VertexArrayID); // Bind VAO
	glDrawElements( GL_LINES /*GL_TRIANGLES*/, m_iIndicesCount, GL_UNSIGNED_INT, (void*)0 ); // Draw
	glBindVertexArray(0); // Unbind VAO
}
//-------------------------------------






