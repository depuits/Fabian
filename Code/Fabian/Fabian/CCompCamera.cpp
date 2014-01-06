#include "CCompCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include "IShader.h"
#include "CGameObject.h"

//******************************************
// Class CCompCamera:
// A basic camera for drawing scenes, including
// the most simple settings.
//******************************************

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the object to be linked to the parent
CCompCamera::CCompCamera()
	:IComponent()
    ,ICamera()
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

glm::mat4& CCompCamera::GetProjection()
{
	if( m_bProjectionChanged ) // recalcutlate the projection when changed
		m_mProjection = glm::perspective(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);

	return m_mProjection;
}
glm::mat4& CCompCamera::GetView()
{
	if( m_pGameObject->Transform()->IsChanged() )
	{
		m_pGameObject->Transform()->GetWorldNP(); // recalculates the world cariable if needed for when there is a mesh to draw on this object

		m_mView = glm::lookAt(
			m_pGameObject->Transform()->GetPos(), // Camera is at (4,3,3), in World Space
			m_pGameObject->Transform()->GetPos() + (m_pGameObject->Transform()->GetRot() * glm::vec3(-1,0,0)), // and looks at the origin
			m_pGameObject->Transform()->GetRot() * glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}

	return m_mView;
}


