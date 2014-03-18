#ifndef FABIAN_ISHADER_H_
#define FABIAN_ISHADER_H_

#include "FabianDef.h"

FDISABLE_WARNING_START(4201)
#include "glm/glm.hpp"
FDISABLE_WARNING_END(4201)

// --forward declarations--
class IImage;
// ------------------------

////////////////////////////////////////////
//! Interface IShader: 
//! interface for applying shaders and setting 
//! their values
////////////////////////////////////////////
class IShader
{
public:
	/************************************/
	/*! Constructor */
	IShader() { };
	/************************************/
	/*! Destructor */
	virtual ~IShader() { };
	/************************************/

	/************************************/
	/*! Activates the shader as the current */
	virtual void Apply() = 0;
	/************************************/

	/************************************/
	/// @{ 
	/*! Sets the shader variable from the id with
	 *    the given value
	 * @param [in] id - Variable id
	 * @param [in] v1, v2, v3, v4, m2, m3, m4, pImg - Variable value(s)
	 */
	virtual void SetVarI1(int id, int v1) = 0;
	virtual void SetVarI2(int id, int v1, int v2) = 0;
	virtual void SetVarI3(int id, int v1, int v2, int v3) = 0;
	virtual void SetVarI4(int id, int v1, int v2, int v3, int v4) = 0;

	virtual void SetVarF1(int id, float v1) = 0;
	virtual void SetVarF2(int id, float v1, float v2) = 0;
	virtual void SetVarF3(int id, float v1, float v2, float v3) = 0;
	virtual void SetVarF4(int id, float v1, float v2, float v3, float v4) = 0;

	virtual void SetVarVec2(int id, const glm::vec2& v2) = 0;
	virtual void SetVarVec3(int id, const glm::vec3& v3) = 0;
	virtual void SetVarVec4(int id, const glm::vec4& v4) = 0;

	virtual void SetVarMat2(int id, const glm::mat2& m2) = 0;
	virtual void SetVarMat3(int id, const glm::mat3& m3) = 0;
	virtual void SetVarMat4(int id, const glm::mat4& m4) = 0;

	virtual void SetVarImage(int id, IImage* pImg) = 0;
	/// @}
	/************************************/
	/*! Gets a shader variable id from the name
	 * @param [in] sVName - Variable name
	 * @return The id of the variable, -1 when failed
	 */
	virtual int GetVarId(const char* sVName) = 0;
	/************************************/

	/************************************/
	/// @{
	/*! Sets the shader World, View or Projection
	 *    variable with the given value
	 * @param [in] m - Variable value
	 */
	virtual void SetWorld(const glm::mat4& m) = 0;
	virtual void SetView(const glm::mat4& m) = 0;
	virtual void SetProjection(const glm::mat4& m) = 0;
	/// @}
	/************************************/


private:
	DISALLOW_COPY_AND_ASSIGN(IShader);
};

#endif //FABIAN_ISHADER_H_
