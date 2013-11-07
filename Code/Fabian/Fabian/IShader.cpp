#include "IShader.h"

#include <gl/glew.h>

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <glm/glm.hpp>
#pragma warning( pop )
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <vector>

IShader::IShader()
	:m_uProgramID(0)
{
}
IShader::~IShader()
{
}
	
void IShader::Load(const std::string& sName)
{
	m_uProgramID = LoadShaders( (sName + ".vsh").c_str(), (sName + ".fsh").c_str() );
}

void IShader::Apply()
{
	glUseProgram(m_uProgramID); // set the shader to use
}

void IShader::SetProjection(const glm::mat4& mProj)
{
	GLint MIDProj = glGetUniformLocation(m_uProgramID, "Projection");
	glUniformMatrix4fv(MIDProj, 1, GL_FALSE, &mProj[0][0]);
}
void IShader::SetView(const glm::mat4& mView)
{
	GLint MIDView = glGetUniformLocation(m_uProgramID, "View");
	glUniformMatrix4fv(MIDView, 1, GL_FALSE, &mView[0][0]);
}
void IShader::SetWorld(const glm::mat4& mWorld)
{
	GLint MIDModel = glGetUniformLocation(m_uProgramID, "Model");
	glUniformMatrix4fv(MIDModel, 1, GL_FALSE, &mWorld[0][0]);
}

GLuint IShader::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
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