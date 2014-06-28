#ifndef PROJECTB_CPBCAMERA_H_
#define PROJECTB_CPBCAMERA_H_

#include "CPBGameObject.h"
#include <ICamera.h>


//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CPBCamera : public CPBGameObject, public ICamera
{
public:
	//-------------------------------------
	// Constructor
	CPBCamera();
	//-------------------------------------
	// Destructor
	virtual ~CPBCamera();
	//-------------------------------------
	
	virtual void Init();						// used for (re)initializing the object
	virtual void Update(float);					// called when the onject needs to update
	
	/************************************/
	/*! Sets/Creates the projection matrix of the camera
	 * @param [in] fFOV			- FOV (Field Of View)
	 * @param [in] fAspectRatio - AspectRatio (4/3, 16/9, 16/10)
	 * @param [in] fNear		- Near plane
	 * @param [in] fFar			- Far plane
	 */
	void SetProjectionParams(float fFOV, float fAspectRatio, float fNear, float fFar);	
	/************************************/
	/// @{
	/*! Get the view or projection matrix of this camera
	 * @return Matrix
	 */
	virtual glm::mat4& GetProjection();
	virtual glm::mat4& GetView();
	/************************************/

	void SetTarget(CPBGameObject* pTarget);

protected:
	float	m_fFOV,
			m_fAspectRatio,
			m_fNear,
			m_fFar;

	bool m_bProjectionChanged;

	glm::mat4   m_mProjection,
                m_mView;

	CPBGameObject* m_pTarget;
	float m_fSpeed;

private:
	DISALLOW_COPY_AND_ASSIGN(CPBCamera);
};

#endif //PROJECTB_CPBCAMERA_H_
