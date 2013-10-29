#ifndef FABIAN_CTRANSFORM_H_
#define FABIAN_CTRANSFORM_H_

#include "FabianDef.h"

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <glm/glm.hpp>
#pragma warning( pop )

#include <glm/gtx/quaternion.hpp>

class CTransform
{
public:
	CTransform(CTransform* = nullptr);
	virtual ~CTransform();
	
	void Move(const glm::vec3&);
	void Rotate(const glm::vec3&);
	
	void SetPos(const glm::vec3&);
	void SetScale(const glm::vec3&);
	void SetRot(const glm::vec3&);
	void SetRot(const glm::quat&);
	
	const glm::vec3& GetPos() const;
	const glm::vec3& GetScale() const;
	const glm::quat& GetRot() const;

	const glm::mat4& GetWorld();

	bool IsChanged() const { return m_bIsChanged; }

protected:
	CTransform *m_pParent;
	
	glm::vec3 m_v3Pos;
	glm::vec3 m_v3Scale;
	glm::quat m_qRot;

	glm::mat4 m_mWorld;

	bool m_bIsChanged;

private:
	DISALLOW_COPY_AND_ASSIGN(CTransform);
};

#endif //FABIAN_TRANSFORM_H_
