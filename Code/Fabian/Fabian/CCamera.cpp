#include "CCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include "IShader.h"
#include "CTransform.h"

//******************************************
// Class CCamera:
// A basic camera for drawing scenes, including
// the most simple settings.
//******************************************
int CCamera::s_iIdView = -1;
int CCamera::s_iIdProj = -1;

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the object to be linked to the parent
CCamera::CCamera(IObject *pPar)
	:IObject(pPar)
	,m_fFOV(45.0f)
	,m_fAspectRatio(16.0f/10.0f)
	,m_fNear(0.1f)
	,m_fFar(1000.0f)

	,m_bProjectionChanged(true)
{
}
//-------------------------------------
// Destructor
CCamera::~CCamera()
{
}
//-------------------------------------
	
//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, false if something failed	
bool CCamera::Init()
{
	return true;
}
//-------------------------------------
// Sets this camera to the current one
// p1 in - pointer to the shader the object should "draw" with
void CCamera::Draw(IShader* pShader)
{
	if( s_iIdView == -1 || s_iIdProj == -1 )
	{
		s_iIdView = pShader->GetVarId("View");
		s_iIdProj = pShader->GetVarId("Projection");
	}

	if( m_bProjectionChanged )
	{
		m_mProjection = glm::perspective(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);
		pShader->SetVarMat4(s_iIdProj, m_mProjection);
	}

	if( Transform()->IsChanged() )
	{
		Transform()->ResetIsChanged();
		glm::mat4 mView = glm::lookAt(
			Transform()->GetPos(), // Camera is at (4,3,3), in World Space
			Transform()->GetPos() + (Transform()->GetRot() * glm::vec3(-1,0,0)), // and looks at the origin
			Transform()->GetRot() * glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		
		pShader->SetVarMat4(s_iIdView, mView);
	}
}
//-------------------------------------
	
//-------------------------------------
// Sets/Creates the projection matrix of the camera
// p1 in - float, FOV (Filed Of View)
// p2 in - float, AspectRatio (4/3, 16/9, 16/10)
// p3 in - float, Near plane
// p4 in - float, Far plane
void CCamera::SetProjectionParams(float fFOV, float fAspectRatio, float fNear, float fFar)
{
	m_fFOV = fFOV;
	m_fAspectRatio = fAspectRatio;
	m_fNear = fNear;
	m_fFar = fFar;

	m_bProjectionChanged = true;
}
//-------------------------------------

