#include "CShaderOpenGL.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
// Sets the shader variable from the id with
//    the given value
// p1 in - int, variable id
// p2 in - int, variable value
// p# in - variable value(s)
void CShaderOpenGL::SetVarI1(int id, int v1)
{
	glUniform1i(id, v1);
}
void CShaderOpenGL::SetVarI2(int id, int v1, int v2)
{
	glUniform2i(id, v1, v2);
}
void CShaderOpenGL::SetVarI3(int id, int v1, int v2, int v3)
{
	glUniform3i(id, v1, v2, v3);
}
void CShaderOpenGL::SetVarI4(int id, int v1, int v2, int v3, int v4)
{
	glUniform4i(id, v1, v2, v3, v4);
}

void CShaderOpenGL::SetVarF1(int id, float v1)
{
	glUniform1f(id, v1);
}
void CShaderOpenGL::SetVarF2(int id, float v1, float v2)
{
	glUniform2f(id, v1, v2);
}
void CShaderOpenGL::SetVarF3(int id, float v1, float v2, float v3)
{
	glUniform3f(id, v1, v2, v3);
}
void CShaderOpenGL::SetVarF4(int id, float v1, float v2, float v3, float v4)
{
	glUniform4f(id, v1, v2, v3, v4);
}

void CShaderOpenGL::SetVarVec2(int id, const glm::vec2& v2)
{
	glUniform2fv(id, 1, glm::value_ptr(v2));
}
void CShaderOpenGL::SetVarVec3(int id, const glm::vec3& v3)
{
	glUniform3fv(id, 1, glm::value_ptr(v3));
}
void CShaderOpenGL::SetVarVec4(int id, const glm::vec4& v4)
{
	glUniform4fv(id, 1, glm::value_ptr(v4));
}

void CShaderOpenGL::SetVarMat2(int id, const glm::mat2& m2)
{
	glUniformMatrix2fv(id, 1, GL_FALSE, glm::value_ptr(m2));
}
void CShaderOpenGL::SetVarMat3(int id, const glm::mat3& m3)
{
	glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(m3));
}
void CShaderOpenGL::SetVarMat4(int id, const glm::mat4& m4)
{
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(m4));
}
//-------------------------------------
// Gets a shader variable id from the name
// p1 in - string, variable name
// rv - int, the id of the variable, -1 when failed
int CShaderOpenGL::GetVarId(const std::string& sVName) 
{ 
	return glGetUniformLocation(m_uProgramID, sVName.c_str());
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

