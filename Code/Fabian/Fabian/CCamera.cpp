#include "CCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include "IShader.h"
#include "CTransform.h"

CCamera::CCamera(IObject *pPar)
	:IObject(pPar)
	,m_fFOV(45.0f)
	,m_fAspectRatio(16.0f/10.0f)
	,m_fNear(0.1f)
	,m_fFar(100.0f)
	,m_bProjectionChanged(true)
{
}
CCamera::~CCamera()
{
}
	
bool CCamera::Init()
{
	return true;
}
void CCamera::Draw(IShader* pShader)
{
	if( m_bProjectionChanged )
	{
		m_mProjection = glm::perspective(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);
		pShader->SetProjection(m_mProjection);
	}

	if( Transform()->IsChanged() )
	{
		Transform()->ResetIsChanged();
		glm::mat4 mView = glm::lookAt(
			Transform()->GetPos(), // Camera is at (4,3,3), in World Space
			Transform()->GetPos() + (Transform()->GetRot() * glm::vec3(-1,0,0)), // and looks at the origin
			Transform()->GetRot() * glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		pShader->SetView( mView );
	}
}

// FOV, AspectRatio, Near, Far
void CCamera::SetProjectionParams(float fFOV, float fAspectRatio, float fNear, float fFar)
{
	m_fFOV = fFOV;
	m_fAspectRatio = fAspectRatio;
	m_fNear = fNear;
	m_fFar = fFar;

	m_bProjectionChanged = true;
}

