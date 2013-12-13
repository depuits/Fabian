#include "CCompCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include "IShader.h"
#include "CGameObject.h"

//******************************************
// Class CCompCamera:
// A basic camera for drawing scenes, including
// the most simple settings.
//******************************************
int CCompCamera::s_iIdView = -1;
int CCompCamera::s_iIdProj = -1;

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the object to be linked to the parent
CCompCamera::CCompCamera()
	:IComponent()
	,m_fFOV(45.0f)
	,m_fAspectRatio(16.0f/10.0f)
	,m_fNear(0.1f)
	,m_fFar(1000.0f)

	,m_bProjectionChanged(true)
{
}
//-------------------------------------
// Destructor
CCompCamera::~CCompCamera()
{
}
//-------------------------------------
	
//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, false if something failed	
bool CCompCamera::Start()
{
	return true;
}
//-------------------------------------
// Sets this camera to the current one
// p1 in - pointer to the shader the object should "draw" with
void CCompCamera::Draw(IShader* pShader)
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

	if( m_pGameObject->Transform()->IsChanged() )
	{
		//m_pGameObject->Transform()->ResetIsChanged();
		glm::mat4 mView = glm::lookAt(
			m_pGameObject->Transform()->GetPos(), // Camera is at (4,3,3), in World Space
			m_pGameObject->Transform()->GetPos() + (m_pGameObject->Transform()->GetRot() * glm::vec3(-1,0,0)), // and looks at the origin
			m_pGameObject->Transform()->GetRot() * glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
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
void CCompCamera::SetProjectionParams(float fFOV, float fAspectRatio, float fNear, float fFar)
{
	m_fFOV = fFOV;
	m_fAspectRatio = fAspectRatio;
	m_fNear = fNear;
	m_fFar = fFar;

	m_bProjectionChanged = true;
}
//-------------------------------------

