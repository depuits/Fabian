#ifndef FABIAN_CCOMPCAMERA_H_
#define FABIAN_CCOMPCAMERA_H_

#include "FabianDef.h"
#include "CCompBase.hpp"

#include "ICamera.h"
#include "IShader.h"

////////////////////////////////////////////
//! Class CCompCamera: 
//! A basic camera for drawing scenes, including 
//! the most simple settings.
////////////////////////////////////////////
class CCompCamera : public CCompBase, public ICamera
{
public:
	/************************************/
	/*! Constructor */
	CCompCamera()
		:CCompBase()
		,ICamera()
		,m_fFOV(45.0f)
		,m_fAspectRatio(16.0f/10.0f)
		,m_fNear(0.1f)
		,m_fFar(1000.0f)

		,m_bProjectionChanged(true)
	{
	}
	/************************************/
	/*! Destructor */
	virtual ~CCompCamera()
	{
	}
	/************************************/
	
	/************************************/
	/*! Initializes the object, should be called before any other
	 *    method of the object.
	 * @return False if something failed
	 */
	virtual bool Start()
	{
		return true;
	}
	/************************************/
		
	/************************************/
	/*! Sets/Creates the projection matrix of the camera
	 * @param [in] fFOV			- FOV (Field Of View)
	 * @param [in] fAspectRatio - AspectRatio (4/3, 16/9, 16/10)
	 * @param [in] fNear		- Near plane
	 * @param [in] fFar			- Far plane
	 */
	void SetProjectionParams(float fFOV, float fAspectRatio, float fNear, float fFar)
	{
		m_fFOV = fFOV;
		m_fAspectRatio = fAspectRatio;
		m_fNear = fNear;
		m_fFar = fFar;

		m_bProjectionChanged = true;
	}
	/************************************/
	
	/************************************/
	/// @{
	/*! Get the view or projection matrix of this camera
	 * @return Matrix
	 */
	virtual glm::mat4& GetProjection()
	{
		if( m_bProjectionChanged ) // recalcutlate the projection when changed
			m_mProjection = glm::perspective(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);

		return m_mProjection;
	}
	virtual glm::mat4& GetView()
	{
		if( m_pGameObject->Transform()->IsChanged() )
		{
			m_pGameObject->Transform()->GetWorld(); // recalculates the world variable if needed for when there is a mesh to draw on this object

			m_mView = glm::lookAt(
				m_pGameObject->Transform()->GetPos(), // Camera is at (4,3,3), in World Space
				m_pGameObject->Transform()->GetPos() + (m_pGameObject->Transform()->GetRot() * glm::vec3(0,0,-1)), // and looks at the origin
				m_pGameObject->Transform()->GetRot() * glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		}

		return m_mView;
	}
	/// @}
	/************************************/

protected:
	float	m_fFOV,
			m_fAspectRatio,
			m_fNear,
			m_fFar;

	bool m_bProjectionChanged;

	glm::mat4   m_mProjection,
                m_mView;

private:
	DISALLOW_COPY_AND_ASSIGN(CCompCamera);
};

#endif //FABIAN_CCOMPCAMERA_H_
