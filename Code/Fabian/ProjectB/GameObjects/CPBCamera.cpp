#include "CPBcamera.h"


//-------------------------------------
// Constructor
CPBCamera::CPBCamera()
		:CPBGameObject()
		,ICamera()
		,m_fFOV(45.0f)
		,m_fAspectRatio(16.0f/10.0f)
		,m_fNear(0.1f)
		,m_fFar(1000.0f)

		,m_bProjectionChanged(true)

		,m_pTarget(nullptr)
		,m_fSpeed(5.0f)
	{
	}
//-------------------------------------
// Destructor
CPBCamera::~CPBCamera()
{
}
//-------------------------------------
	
void CPBCamera::Init()					// used for (re)initializing the object
{
}
void CPBCamera::Update(float dTime)			// called when the onject needs to update
{
	if( m_pTarget == nullptr )
		return;

	glm::vec3 dpos = m_pTarget->GetTransform()->GetPos() - m_Transform.GetPos();
	//dpos = glm::normalize( dpos );
	dpos.y = 0;
	dpos /= 5;

	m_Transform.Move( dpos * dTime * m_fSpeed );
}
	
/************************************/
/*! Sets/Creates the projection matrix of the camera
	* @param [in] fFOV			- FOV (Field Of View)
	* @param [in] fAspectRatio - AspectRatio (4/3, 16/9, 16/10)
	* @param [in] fNear		- Near plane
	* @param [in] fFar			- Far plane
	*/
void CPBCamera::SetProjectionParams(float fFOV, float fAspectRatio, float fNear, float fFar)
{
	m_fFOV = fFOV;
	m_fAspectRatio = fAspectRatio;
	m_fNear = fNear;
	m_fFar = fFar;

	m_bProjectionChanged = true;
}
/************************************/
/// @{
/*! Get the view or projection matrix of this camera
* @return Matrix
*/
glm::mat4& CPBCamera::GetProjection()
{
	if( m_bProjectionChanged ) // recalcutlate the projection when changed
		m_mProjection = glm::perspective(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);

	return m_mProjection;
}
glm::mat4& CPBCamera::GetView()
{
	if( m_Transform.IsChanged() )
	{
		m_Transform.GetWorld(); // recalculates the world variable if needed for when there is a mesh to draw on this object

		m_mView = glm::lookAt(
			m_Transform.GetPos(), // Camera is at (4,3,3), in World Space
			m_Transform.GetPos() + (m_Transform.GetRot() * glm::vec3(0,0,-1)), // and looks at the origin
			m_Transform.GetRot() * glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}

	return m_mView;
}
/************************************/

void CPBCamera::SetTarget(CPBGameObject* pTarget)
{
	m_pTarget = pTarget;
}