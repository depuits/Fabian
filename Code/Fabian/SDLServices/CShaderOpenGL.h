#ifndef FABIAN_CSHADEROPENGL_H_
#define FABIAN_CSHADEROPENGL_H_

#include "FabianDef.h"
#include "IShader.h"
#include <GL/glew.h>
#include <string>

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
	// p1 in - shader file name without any extensions
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
	// p# in - variable value(s)
	virtual void SetVarI1(int, int);
	virtual void SetVarI2(int, int, int);
	virtual void SetVarI3(int, int, int, int);
	virtual void SetVarI4(int, int, int, int, int);

	virtual void SetVarF1(int, float);
	virtual void SetVarF2(int, float, float);
	virtual void SetVarF3(int, float, float, float);
	virtual void SetVarF4(int, float, float, float, float);

	virtual void SetVarVec2(int, const glm::vec2&);
	virtual void SetVarVec3(int, const glm::vec3&);
	virtual void SetVarVec4(int, const glm::vec4&);

	virtual void SetVarMat2(int, const glm::mat2&);
	virtual void SetVarMat3(int, const glm::mat3&);
	virtual void SetVarMat4(int, const glm::mat4&);

	virtual void SetVarImage(int, IImage*);
	//-------------------------------------
	// Gets a shader variable id from the name
	// p1 in - string, variable name
	// rv - int, the id of the variable, -1 when failed
	virtual int GetVarId(const char*);
	//-------------------------------------

	//-------------------------------------
	// Sets the shader World, View or Projection
	//    variable with the given value
	// p1 in - variable value
	virtual void SetWorld(const glm::mat4&);
	virtual void SetView(const glm::mat4&);
	virtual void SetProjection(const glm::mat4&);
	//-------------------------------------

protected:
	//-------------------------------------
	// The actual loading of the shader
	// p1 in - vertex shader file
	// p2 in - fragment shader file
	// rv - uint, program id
	GLuint LoadShaders(const char *,const char *);
	//-------------------------------------

	GLuint m_uProgramID;

	int m_iIdWorld, m_iIdView, m_iIdProjection;

private:
	DISALLOW_COPY_AND_ASSIGN(CShaderOpenGL);
};

#endif //FABIAN_CSHADEROPENGL_H_
