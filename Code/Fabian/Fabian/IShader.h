#ifndef FABIAN_ISHADER_H_
#define FABIAN_ISHADER_H_

#include "FabianDef.h"
#include <string>

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <glm/glm.hpp>
#pragma warning( pop )

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
	// p2 in - int, variable value
	virtual void SetVar(int, int) = 0;
	//-------------------------------------
	// Gets a shader variable id from the name
	// p1 in - string, variable name
	// rv - int, the id of the variable, -1 when failed
	virtual int GetVarId(const std::string&) = 0;
	//-------------------------------------
	
	//-------------------------------------
	// Sets the world, view or projection matrix
	// !!! - these methods will probebly go when 
	//          the VarIds are implemented
	// p1 in - mat4, the matrix variable
	virtual void SetProjection(const glm::mat4&) = 0;
	virtual void SetView(const glm::mat4&) = 0;
	virtual void SetWorld(const glm::mat4&) = 0;
	//-------------------------------------

private:
	DISALLOW_COPY_AND_ASSIGN(IShader);
};

#endif //FABIAN_ISHADER_H_
