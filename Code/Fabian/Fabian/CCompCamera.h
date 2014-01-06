#ifndef FABIAN_CCOMPCAMERA_H_
#define FABIAN_CCOMPCAMERA_H_

#include "FabianDef.h"
#include "IComponent.h"

#include "ICamera.h"

FDISABLE_WARNING_START(4201)
#include <glm/glm.hpp>
FDISABLE_WARNING_END(4201)

//******************************************
// Class CCompCamera:
// A basic camera for drawing scenes, including
// the most simple settings.
//******************************************
class CCompCamera : public IComponent, public ICamera
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CCompCamera();
	//-------------------------------------
	// Destructor
	virtual ~CCompCamera();
	//-------------------------------------

	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, false if something failed
	virtual bool Start();
	//-------------------------------------

	//-------------------------------------
	// Sets/Creates the projection matrix of the camera
	// p1 in - float, FOV (Filed Of View)
	// p2 in - float, AspectRatio (4/3, 16/9, 16/10)
	// p3 in - float, Near plane
	// p4 in - float, Far plane
	void SetProjectionParams(float, float, float, float);
	//-------------------------------------

	virtual glm::mat4& GetProjection();
	virtual glm::mat4& GetView();

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
