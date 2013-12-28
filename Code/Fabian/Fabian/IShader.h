#ifndef FABIAN_ISHADER_H_
#define FABIAN_ISHADER_H_

#include "FabianDef.h"
#include <string>

FDISABLE_WARNING_START(4201)
#include <glm/glm.hpp>
FDISABLE_WARNING_END(4201)

// --forward declarations--
class IImage;
// ------------------------

//******************************************
// Interface IShader:
// interface for applying shaders and setting
// their values
//******************************************
class IShader
{
public:
	//-------------------------------------
	// Constructor
	IShader() { };
	//-------------------------------------
	// Destructor
	virtual ~IShader() { };
	//-------------------------------------

	//-------------------------------------
	// Loads in the shader and set it up for use
	// rv - bool, return false if something failed
	virtual bool Load(const std::string&) = 0;
	//-------------------------------------
	// Activates the shader as the current
	virtual void Apply() = 0;
	//-------------------------------------

	//-------------------------------------
	// Sets the shader variable from the id with
	//    the given value
	// p1 in - int, variable id
	// p# in - variable value(s)
	virtual void SetVarI1(int, int) = 0;
	virtual void SetVarI2(int, int, int) = 0;
	virtual void SetVarI3(int, int, int, int) = 0;
	virtual void SetVarI4(int, int, int, int, int) = 0;

	virtual void SetVarF1(int, float) = 0;
	virtual void SetVarF2(int, float, float) = 0;
	virtual void SetVarF3(int, float, float, float) = 0;
	virtual void SetVarF4(int, float, float, float, float) = 0;

	virtual void SetVarVec2(int, const glm::vec2&) = 0;
	virtual void SetVarVec3(int, const glm::vec3&) = 0;
	virtual void SetVarVec4(int, const glm::vec4&) = 0;

	virtual void SetVarMat2(int, const glm::mat2&) = 0;
	virtual void SetVarMat3(int, const glm::mat3&) = 0;
	virtual void SetVarMat4(int, const glm::mat4&) = 0;

	virtual void SetVarImage(int, IImage*) = 0;
	//-------------------------------------
	// Gets a shader variable id from the name
	// p1 in - string, variable name
	// rv - int, the id of the variable, -1 when failed
	virtual int GetVarId(const std::string&) = 0;
	//-------------------------------------

private:
	DISALLOW_COPY_AND_ASSIGN(IShader);
};

#endif //FABIAN_ISHADER_H_
