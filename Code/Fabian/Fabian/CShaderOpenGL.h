#ifndef FABIAN_CSHADEROPENGL_H_
#define FABIAN_CSHADEROPENGL_H_

#include "FabianDef.h"
#include "IShader.h"
#include <gl/glew.h>

//******************************************
// Class CShaderOpenGL:
// OpenGL implementation of IShader interface
//******************************************
class CShaderOpenGL : public IShader
{
public:
	//-------------------------------------
	// Constructor
	CShaderOpenGL();
	//-------------------------------------
	// Destructor
	virtual ~CShaderOpenGL();
	//-------------------------------------
	
	//-------------------------------------
	// Loads in the shader and set it up for use
	// !!! - loads 2 files, 
	//          ".vsh" for the vertex shader
	//          ".fsh" for the fragment(pixel) shader
	// rv - bool, return false if something failed
	virtual bool Load(const std::string&);
	//-------------------------------------
	// Activates the shader as the current
	virtual void Apply();
	//-------------------------------------
	
	//-------------------------------------
	// Sets the shader variable from the id with
	//    the given value
	// p1 in - int, variable id
	// p2 in - int, variable value
	virtual void SetVar(int, int) { };
	//-------------------------------------
	// Gets a shader variable id from the name
	// p1 in - string, variable name
	// rv - int, the id of the variable, -1 when failed
	virtual int GetVarId(const std::string&) { return -1; };
	//-------------------------------------
	
	//-------------------------------------
	// Sets the world, view or projection matrix
	// !!! - these methods will probebly go when 
	//          the VarIds are implemented
	// p1 in - mat4, the matrix variable
	virtual void SetProjection(const glm::mat4&);
	virtual void SetView(const glm::mat4&);
	virtual void SetWorld(const glm::mat4&);
	//-------------------------------------


protected:
	//-------------------------------------
	// The actual loading of the shader
	// p1 in - vertex shader file
	// p2 in - fragment shader file
	GLuint LoadShaders(const char *,const char *);
	//-------------------------------------

	GLuint m_uProgramID;

private:
	DISALLOW_COPY_AND_ASSIGN(CShaderOpenGL);
};

#endif //FABIAN_CSHADEROPENGL_H_
