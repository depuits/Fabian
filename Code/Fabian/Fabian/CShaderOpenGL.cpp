#include "CShaderOpenGL.h"

#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <vector>

//******************************************
// Class CShaderOpenGL:
// OpenGL implementation of IShader interface
//******************************************

//-------------------------------------
// Constructor
CShaderOpenGL::CShaderOpenGL()
	:m_uProgramID(0)
{
}
//-------------------------------------
// Destructor
CShaderOpenGL::~CShaderOpenGL()
{
}
//-------------------------------------
	
//-------------------------------------
// Loads in the shader and set it up for use
// !!! - loads 2 files, 
//          ".vsh" for the vertex shader
//          ".fsh" for the fragment(pixel) shader
// rv - bool, return false if something failed
bool CShaderOpenGL::Load(const std::string& sName)
{
	m_uProgramID = LoadShaders( (sName + ".vsh").c_str(), (sName + ".fsh").c_str() );
	return true;
}
//-------------------------------------
// Activates the shader as the current
void CShaderOpenGL::Apply()
{
	glUseProgram(m_uProgramID); // set the shader to use
}
//-------------------------------------

//-------------------------------------
// Sets the world, view or projection matrix
// !!! - these methods will probebly go when 
//          the VarIds are implemented
// p1 in - mat4, the matrix variable
void CShaderOpenGL::SetProjection(const glm::mat4& mProj)
{
	GLint MIDProj = glGetUniformLocation(m_uProgramID, "Projection");
	glUniformMatrix4fv(MIDProj, 1, GL_FALSE, &mProj[0][0]);
}
void CShaderOpenGL::SetView(const glm::mat4& mView)
{
	GLint MIDView = glGetUniformLocation(m_uProgramID, "View");
	glUniformMatrix4fv(MIDView, 1, GL_FALSE, &mView[0][0]);
}
void CShaderOpenGL::SetWorld(const glm::mat4& mWorld)
{
	GLint MIDModel = glGetUniformLocation(m_uProgramID, "Model");
	glUniformMatrix4fv(MIDModel, 1, GL_FALSE, &mWorld[0][0]);
}
//-------------------------------------

//-------------------------------------
// The actual loading of the shader
// p1 in - vertex shader file
// p2 in - fragment shader file
GLuint CShaderOpenGL::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
 
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
		VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
 
	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
 
	GLint Result = GL_FALSE;
	int InfoLogLength;
 
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
 
	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage.data() );
	fprintf(stdout, "%s\n", VertexShaderErrorMessage.data() );
 
	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
 
	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage.data() );
	fprintf(stdout, "%s\n", FragmentShaderErrorMessage.data() );
 
	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
 
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( glm::max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage.data() );
	fprintf(stdout, "%s\n", ProgramErrorMessage.data() );
 
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
 
	return ProgramID;
}
//-------------------------------------

