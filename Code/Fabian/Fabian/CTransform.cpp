#include "CTransform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

//******************************************
// Class CTransform:
// class used to move, rotate and scale objects
//******************************************

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the object to be linked to the parent
CTransform::CTransform(CTransform *pPar)
	:m_pParent(pPar)
	,m_bIsChanged(true)

	,m_v3Pos(0)
	,m_v3Scale(1)
	,m_qRot()
{
}
//-------------------------------------
// Destructor
CTransform::~CTransform()
{
}
//-------------------------------------
	
//-------------------------------------
// Move a certain distance from the current position
// p1 in - vec3, distance
void CTransform::Move(const glm::vec3& v3Dist)
{
	m_bIsChanged = true;
	m_v3Pos += v3Dist;
}
//-------------------------------------
// Rotates the object allong its axis
// p1 in - vec3, rotation
void CTransform::Rotate(const glm::vec3& v3Rot)
{
	m_bIsChanged = true;
	m_qRot = glm::quat(v3Rot) * m_qRot;
}
//-------------------------------------
	
//-------------------------------------
// Move a certain distance from the current position
//    relative to its local axis, (so x == forward)
// p1 in - vec3, distance
void CTransform::LocalMove(const glm::vec3& v3Dist)
{
	m_bIsChanged = true;
	glm::vec4 vec(v3Dist, 1.0f);
	m_v3Pos += glm::vec3(glm::toMat4(m_qRot) * vec);
}
//-------------------------------------
// Rotates the object allong its local axis
// !!! - not sure if working correct
// p1 in - vec3, rotation
void CTransform::LocalRotate(const glm::vec3& v3Rot)
{
	m_bIsChanged = true;
	m_qRot = m_qRot * glm::quat(v3Rot);
}
//-------------------------------------
	
//-------------------------------------
// Sets the position
// p1 in - vec3, new position
void CTransform::SetPos(const glm::vec3& v3Pos)
{
	m_bIsChanged = true;
	m_v3Pos = v3Pos;
}
//-------------------------------------
// Sets the scale
// p1 in - float, scale
//       - vec3, scale per axis
void CTransform::SetScale(float fScale)
{
	m_bIsChanged = true;
	m_v3Scale = glm::vec3(fScale);
}
void CTransform::SetScale(const glm::vec3& v3Scale)
{
	m_bIsChanged = true;
	m_v3Scale = v3Scale;
}
//-------------------------------------
// Sets the rotation
// p1 in - vec3, rotation
//       - quat, rotation
void CTransform::SetRot(const glm::vec3& v3Rot)
{
	m_bIsChanged = true;
	m_qRot = glm::quat(v3Rot);
}
void CTransform::SetRot(const glm::quat& qRot)
{
	m_bIsChanged = true;
	m_qRot = qRot;
}
//-------------------------------------
	
//-------------------------------------
// Gets the position
// rv - vec3, position
const glm::vec3& CTransform::GetPos() const
{
	return m_v3Pos;
}
//-------------------------------------
// Gets the scale
// rv - vec3, scale per axis
const glm::vec3& CTransform::GetScale() const
{
	return m_v3Scale;
}
//-------------------------------------
// Gets the rotation
// rv - quat, rotation
const glm::quat& CTransform::GetRot() const
{
	return m_qRot;
}
//-------------------------------------
	
//-------------------------------------
// Gets the world matrix
// rv - mat4, world matrix
const glm::mat4& CTransform::GetWorld()
{
	// to do:
	//		edit this child parent relation because its wrong

	GetWorldNP(); // I don't need the return value because the world is set in this method
	if( m_pParent != nullptr)
	{
		m_mWorld *= m_pParent->GetWorld();
	}

	return m_mWorld;
}
//-------------------------------------
// Gets the world matrix, ignoring the parent
// rv - mat4, world matrix
const glm::mat4& CTransform::GetWorldNP()
{
	if( m_bIsChanged )
	{
		m_mWorld = glm::translate(m_v3Pos) * glm::toMat4(m_qRot) * glm::scale(m_v3Scale);
		m_bIsChanged = false;
	}

	return m_mWorld;
}
//-------------------------------------


