#ifndef FABIAN_CCAMERA_H_
#define FABIAN_CCAMERA_H_

#include "FabianDef.h"
#include "IObject.h"

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <glm/glm.hpp>
#pragma warning( pop )

//******************************************
// Class CCamera:
// A basic camera for drawing scenes, including
// the most simple settings.
//******************************************
class CCamera : public IObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CCamera(IObject* = nullptr);
	//-------------------------------------
	// Destructor
	virtual ~CCamera();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, false if something failed
	virtual bool Init();
	//-------------------------------------
	// Sets this camera to the current one
	// p1 in - pointer to the shader the object should "draw" with
	virtual void Draw(IShader*);
	//-------------------------------------
	
	//-------------------------------------
	// Sets/Creates the projection matrix of the camera
	// p1 in - float, FOV (Filed Of View)
	// p2 in - float, AspectRatio (4/3, 16/9, 16/10)
	// p3 in - float, Near plane
	// p4 in - float, Far plane
	void SetProjectionParams(float, float, float, float);
	//-------------------------------------

protected:
	float	m_fFOV,
			m_fAspectRatio,
			m_fNear,
			m_fFar;

	bool m_bProjectionChanged;

	glm::mat4 m_mProjection;
	static int s_iIdView, s_iIdProj;

private:
	DISALLOW_COPY_AND_ASSIGN(CCamera);
};

#endif //FABIAN_CCAMERA_H_
