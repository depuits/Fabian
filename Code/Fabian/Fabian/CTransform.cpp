#include "CTransform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

CTransform::CTransform(CTransform *pPar)
	:m_pParent(pPar)
	,m_bIsChanged(true)

	,m_v3Pos(0)
	,m_v3Scale(1)
	,m_qRot()
{
}
CTransform::~CTransform()
{
}

void CTransform::Move(const glm::vec3& v3Dist)
{
	m_bIsChanged = true;
	m_v3Pos += v3Dist;
}
void CTransform::Rotate(const glm::vec3& v3Rot)
{
	m_bIsChanged = true;
	m_qRot = glm::quat(v3Rot) * m_qRot;
}
	
void CTransform::SetPos(const glm::vec3& v3Pos)
{
	m_bIsChanged = true;
	m_v3Pos = v3Pos;
}
void CTransform::SetScale(const glm::vec3& v3Scale)
{
	m_bIsChanged = true;
	m_v3Scale = v3Scale;
}
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

const glm::vec3& CTransform::GetPos() const
{
	return m_v3Pos;
}
const glm::vec3& CTransform::GetScale() const
{
	return m_v3Scale;
}
const glm::quat& CTransform::GetRot() const
{
	return m_qRot;
}

const glm::mat4& CTransform::GetWorld()
{
	if( m_bIsChanged )
	{
		m_mWorld = glm::translate(m_v3Pos) * glm::toMat4(m_qRot) * glm::scale(m_v3Scale);
		m_bIsChanged = false;
	}

	if( m_pParent != nullptr)
	{
		m_mWorld *= m_pParent->GetWorld();
	}

	return m_mWorld;
}


