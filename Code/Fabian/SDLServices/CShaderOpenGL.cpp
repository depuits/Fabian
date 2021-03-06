#include "CShaderOpenGL.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <vector>
#include <Fabian.h>

#include "CImageOpenGL.h"

//******************************************
// Class CShaderOpenGL:
// OpenGL implementation of IShader interface
//******************************************

//-------------------------------------
// Constructor
CShaderOpenGL::CShaderOpenGL()
	:m_uProgramID(0)

	,m_iIdWorld(-1)
	,m_iIdView(-1)
	,m_iIdProjection(-1)
{
}
//-------------------------------------
// Destructor
CShaderOpenGL::~CShaderOpenGL()
{
	glDeleteShader(m_uProgramID);
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

    // these names must be used inside the shaders
    m_iIdWorld = GetVarId("World");
    m_iIdView = GetVarId("View");
    m_iIdProjection = GetVarId("Projection");

    FASSERT( m_iIdWorld != -1 && m_iIdView != -1 && m_iIdProjection != -1 );

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

void CShaderOpenGL::SetVarImage(int id, IImage* pImg)
{
	CImageOpenGL* pOpenGLImg = dynamic_cast<CImageOpenGL*>(pImg);
	if( pOpenGLImg != nullptr)
	{
		glUniform1i(id, pOpenGLImg->GetPos());
		glActiveTexture(GL_TEXTURE0 + pOpenGLImg->GetPos());
		glBindTexture(GL_TEXTURE_2D, pOpenGLImg->GetImageId() );
	}
	else
		glBindTexture(GL_TEXTURE_2D, 0); // unbind
}
//-------------------------------------
// Gets a shader variable id from the name
// p1 in - string, variable name
// rv - int, the id of the variable, -1 when failed
int CShaderOpenGL::GetVarId(const char* sVName)
{
	return glGetUniformLocation(m_uProgramID, sVName);
}
//-------------------------------------

//-------------------------------------
// Sets the shader World, View or Projection
//    variable with the given value
// p1 in - variable value
void CShaderOpenGL::SetWorld(const glm::mat4& m)
{
    FASSERT( m_iIdWorld != -1 );
    SetVarMat4(m_iIdWorld, m);
}
void CShaderOpenGL::SetView(const glm::mat4& m)
{
    FASSERT( m_iIdView != -1 );
    SetVarMat4(m_iIdView, m);
}
void CShaderOpenGL::SetProjection(const glm::mat4& m)
{
    FASSERT( m_iIdProjection != -1 );
    SetVarMat4(m_iIdProjection, m);
}
//-------------------------------------

//-------------------------------------
// The actual loading of the shader
// p1 in - vertex shader file
// p2 in - fragment shader file
GLuint CShaderOpenGL::LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
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
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Compiling vertex shader : %s", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	if( Result == GL_FALSE )
	{
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage.data() );
		Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "%s", VertexShaderErrorMessage.data());
	}

	// Compile Fragment Shader
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Compiling fragment shader : %s", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	if( Result == GL_FALSE )
	{
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage.data() );
		Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "%s", FragmentShaderErrorMessage.data());
	}

	// Link the program
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Linking shader program");
	GLuint ProgramID = glCreateProgram();

	// Define the Vertex attributes in the shader
	glBindAttribLocation(ProgramID, 0, "in_vertexPos");
	glBindAttribLocation(ProgramID, 1, "in_vertexNormal");
	glBindAttribLocation(ProgramID, 2, "in_vertexUV");

	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	if( Result == GL_FALSE )
	{
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage( glm::max(InfoLogLength, int(1)) );
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage.data() );
		Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "%s", ProgramErrorMessage.data());
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
//-------------------------------------

