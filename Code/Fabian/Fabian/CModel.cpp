#include "CModel.h"

#include <gl/glew.h>
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning( pop )

#include "IShader.h"
#include "CTransform.h"

// This will identify our vertex buffer
GLuint g_vertexbuffer;
GLuint g_VertexArrayID;

CModel::CModel()
{
}
CModel::~CModel()
{
}
	
bool CModel::Init()
{	
	GLfloat vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
	
	glGenVertexArrays(1, &g_VertexArrayID);	// create VAO for object
	glBindVertexArray(g_VertexArrayID);		// bind the VAO
 
	// Generate 1 vertex buffer
	glGenBuffers(1, &g_vertexbuffer);				// create VBO for object
	glBindBuffer(GL_ARRAY_BUFFER, g_vertexbuffer);	// bind VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW); // Give our vertices to OpenGL.

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	
	glBindVertexArray(0); // Disable our Vertex Buffer Object

	return true;
}

void CModel::Draw(IShader* pShader)
{
	pShader->SetWorld( Transform()->GetWorld() );
	//pShader->SetWorld( glm::mat4(1.0f) );

	glBindVertexArray(g_VertexArrayID); // Bind VAO
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Draw
	glBindVertexArray(0); // Unbind VAO
}

