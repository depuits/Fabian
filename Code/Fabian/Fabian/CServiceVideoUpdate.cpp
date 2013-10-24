#include "CServiceVideoUpdate.h"

#include <gl/glew.h>
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#pragma warning( push )
#pragma warning( disable: 4201 )
 //code with ThatWarning here
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning( pop )

GLuint g_programID;

#include <string>
#include <fstream>
#include <vector>
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
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



CServiceVideoUpdate::CServiceVideoUpdate(int priorety)
	:IService(priorety)

	,m_iScreenWidth(800)
	,m_iScreenHeight(600)

	,m_pWindow(nullptr)
	,m_GLContext(NULL)
{
}
CServiceVideoUpdate::~CServiceVideoUpdate()
{
}
	
bool CServiceVideoUpdate::Start()
{
	if( SDL_InitSubSystem(SDL_INIT_VIDEO) == -1 )
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_GENERIC_SUB_INIT_FAIL, "Video", SDL_GetError() );
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	int flags = SDL_WINDOW_OPENGL;
	
	m_pWindow = SDL_CreateWindow("Fabian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iScreenWidth, m_iScreenHeight, flags);
	if( m_pWindow == nullptr )
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, SDL_GetError() );
		return false;
	}

	m_GLContext = SDL_GL_CreateContext(m_pWindow);
	if( m_GLContext == NULL )
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, SDL_GetError() );
		SDL_DestroyWindow(m_pWindow);
		return false;
	}
	
	if (glewInit() != GLEW_OK) 
	{
		//CLog::Get().Write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, SDL_GetError() );
		SDL_DestroyWindow(m_pWindow);
		return false;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//hide the mouse cursor
	//SDL_ShowCursor(SDL_DISABLE);
	
	g_programID = LoadShaders( "SimpleVertexShader.vsh", "SimpleFragmentShader.fsh" );

	return true;
}
void CServiceVideoUpdate::Update()
{
	// temp for clearing window	
	glClearColor(1.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	
	glUseProgram(g_programID);
	// -------------------------------------------------------------------------------------------------
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
	// -------------------------------------------------------------------------------------------------

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	GLuint MatrixID = glGetUniformLocation(g_programID, "MVP");
 
	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	// -------------------------------------------------------------------------------------------------




	const GLfloat g_vertex_buffer_data[] = {
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

	// This will identify our vertex buffer
	GLuint vertexbuffer;
 
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
 
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
 
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
 
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
 
	glDisableVertexAttribArray(0);

	SDL_GL_SwapWindow(m_pWindow);
}
void CServiceVideoUpdate::Stop()
{
    // Close and destroy the window
    SDL_DestroyWindow(m_pWindow);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

