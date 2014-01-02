#ifndef FABIAN_CTRANSFORM_H_
#define FABIAN_CTRANSFORM_H_

#include "FabianDef.h"

FDISABLE_WARNING_START(4201)
//#define GLM_SWIZZLE <- can be used for vec4.xyz() method
#include <glm/glm.hpp>
FDISABLE_WARNING_END(4201)

#include <glm/gtx/quaternion.hpp>

//******************************************
// Class CTransform:
// class used to move, rotate and scale objects
//******************************************
class CTransform
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CTransform(CTransform* = nullptr);
	//-------------------------------------
	// Destructor
	virtual ~CTransform();
	//-------------------------------------

	//-------------------------------------
	// Move a certain distance from the current position
	// p1 in - vec3, distance
	void Move(const glm::vec3&);
	//-------------------------------------
	// Rotates the object allong its axis
	// p1 in - vec3, rotation
	void Rotate(const glm::vec3&);
	//-------------------------------------

	//-------------------------------------
	// Move a certain distance from the current position
	//    relative to its local axis, (so x == forward)
	// p1 in - vec3, distance
	void LocalMove(const glm::vec3&);
	//-------------------------------------
	// Rotates the object allong its local axis
	// !!! - not sure if working correct
	// p1 in - vec3, rotation
	void LocalRotate(const glm::vec3&);
	//-------------------------------------

	//-------------------------------------
	// Sets the position
	// p1 in - vec3, new position
	void SetPos(const glm::vec3&);
	//-------------------------------------
	// Sets the scale
	// p1 in - float, scale
	//       - vec3, scale per axis
	void SetScale(float);
	void SetScale(const glm::vec3&);
	//-------------------------------------
	// Sets the rotation
	// p1 in - vec3, rotation
	//       - quat, rotation
	void SetRot(const glm::vec3&);
	void SetRot(const glm::quat&);
	//-------------------------------------

	//-------------------------------------
	// Gets the position
	// rv - vec3, position
	const glm::vec3& GetPos() const;
	//-------------------------------------
	// Gets the scale
	// rv - vec3, scale per axis
	const glm::vec3& GetScale() const;
	//-------------------------------------
	// Gets the rotation
	// rv - quat, rotation
	const glm::quat& GetRot() const;
	//-------------------------------------

	//-------------------------------------
	// Gets the world matrix
	// rv - mat4, world matrix
	const glm::mat4& GetWorld();
	//-------------------------------------
	// Gets the world matrix, ignoring the parent
	// rv - mat4, world matrix
	const glm::mat4& GetWorldNP();
	//-------------------------------------

	//-------------------------------------
	// Check weither any variables got changed
	// rv - bool, return true if something changed
	bool IsChanged() const { return m_bIsChanged; }
	//-------------------------------------
	// Resets the changed param to false
	void ResetIsChanged() { m_bIsChanged = false; }
	//-------------------------------------

protected:
	CTransform *m_pParent;

	bool m_bIsChanged;

	glm::vec3 m_v3Pos;
	glm::vec3 m_v3Scale;
	glm::quat m_qRot;

	glm::mat4 m_mWorld;

private:
	DISALLOW_COPY_AND_ASSIGN(CTransform);
};

#endif //FABIAN_TRANSFORM_H_
