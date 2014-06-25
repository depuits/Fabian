#ifndef FABIAN_CTRANSFORM_H_
#define FABIAN_CTRANSFORM_H_

#include "FabianDef.h"

FDISABLE_WARNING_START(4201)
//#define GLM_SWIZZLE <- can be used for vec4.xyz() method
#include "glm/glm.hpp"
FDISABLE_WARNING_END(4201)

#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

////////////////////////////////////////////
//! Class CTransform: 
//! class used to move, rotate and scale objects
////////////////////////////////////////////
class CTransform
{
public:
	/************************************/
	/*! Constructor */
	CTransform()
		:m_bIsChanged(true)

		,m_v3Pos(0)
		,m_v3Scale(1)
		,m_qRot()
	{
	}
	/************************************/
	/*! Destructor */
	virtual ~CTransform()
	{
	}
	/************************************/

	/************************************/
	/*! Move a certain distance from the current position
	 * @param [in] v3Dist - Distance
	 */
	void Move(const glm::vec3& v3Dist)
	{
		m_bIsChanged = true;
		m_v3Pos += v3Dist;
	}
	/************************************/
	/*! Rotates the object allong its axis
	 * @param [in] v3Rot - Rotation
	 */
	void Rotate(const glm::vec3& v3Rot)
	{
		m_bIsChanged = true;
		m_qRot = glm::quat(v3Rot) * m_qRot;
	}
	/************************************/

	/************************************/
	/*! Move a certain distance from the current position
	 *    relative to its local axis, (so x == forward)
	 * @param [in] v3Dist - Distance
	 */
	void LocalMove(const glm::vec3& v3Dist)
	{
		m_bIsChanged = true;
		glm::vec4 vec(v3Dist, 1.0f);
		m_v3Pos += glm::vec3(glm::toMat4(m_qRot) * vec);
	}
	/************************************/
	/*! Rotates the object allong its local axis
	 * @param [in] v3Rot - Rotation
	 * @todo Check: not sure if working correct because of axis order
	 */
	void LocalRotate(const glm::vec3& v3Rot)
	{
		m_bIsChanged = true;
		m_qRot = m_qRot * glm::quat(v3Rot);
	}
	/************************************/

	/************************************/
	/*! Sets the position
	 * @param [in] v3Pos - New position
	 */
	void SetPos(const glm::vec3& v3Pos)
	{
		m_bIsChanged = true;
		m_v3Pos = v3Pos;
	}
	/************************************/
	/*! Sets the scale
	 * @param [in] fScale - Scale
	 */
	void SetScale(float fScale)
	{
		m_bIsChanged = true;
		m_v3Scale = glm::vec3(fScale);
	}
	/*! Sets the scale
	 * @param [in] v3Scale - Scale per axis
	 */
	void SetScale(const glm::vec3& v3Scale)
	{
		m_bIsChanged = true;
		m_v3Scale = v3Scale;
	}
	/************************************/
	/*! Sets the rotation
	 * @param [in] v3Rot - Rotation
	 */
	void SetRot(const glm::vec3& v3Rot)
	{
		m_bIsChanged = true;
		m_qRot = glm::quat(v3Rot);
	}
	/*! Sets the rotation
	 * @param [in] qRot - Rotation
	 */
	void SetRot(const glm::quat& qRot)
	{
		m_bIsChanged = true;
		m_qRot = qRot;
	}
	/************************************/

	/************************************/
	/*! Gets the position
	 * @return Position
	 */
	const glm::vec3& GetPos() const
	{
		return m_v3Pos;
	}
	/************************************/
	/*! Gets the scale
	 * @return Scale per axis
	 */
	const glm::vec3& GetScale() const
	{
		return m_v3Scale;
	}
	/************************************/
	/*! Gets the rotation
	 * @return Rotation
	 */
	const glm::quat& GetRot() const
	{
		return m_qRot;
	}
	/************************************/

	/************************************/
	/*! Gets the world matrix
	 * @return World matrix
	 */
	const glm::mat4& GetWorld()
	{
		if( m_bIsChanged )
		{
			m_mWorld = glm::translate(m_v3Pos) * glm::toMat4(m_qRot) * glm::scale(m_v3Scale);
			m_bIsChanged = false;
		}

		return m_mWorld;
	}
	/************************************/

	/************************************/
	/*! Check weither any variables got changed
	 * @return True if something changed
	 */
	bool IsChanged() const { return m_bIsChanged; }
	/************************************/
	/*! Resets the changed param to false */
	void ResetIsChanged() { m_bIsChanged = false; }
	/************************************/

protected:
	bool m_bIsChanged;

	glm::vec3 m_v3Pos;
	glm::vec3 m_v3Scale;
	glm::quat m_qRot;

	glm::mat4 m_mWorld;

private:
	DISALLOW_COPY_AND_ASSIGN(CTransform);
};

#endif //FABIAN_TRANSFORM_H_
