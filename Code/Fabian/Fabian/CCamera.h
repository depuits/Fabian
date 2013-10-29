#ifndef FABIAN_CCAMERA_H_
#define FABIAN_CCAMERA_H_

#include "FabianDef.h"
#include "IObject.h"

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <glm/glm.hpp>
#pragma warning( pop )

class CCamera : public IObject
{
public:
	CCamera(IObject* = nullptr);
	virtual ~CCamera();
	
	virtual bool Init();
	virtual void Draw(IShader*);
	
protected:
	float	m_fFOV,
			m_fAspectRatio,
			m_fNear,
			m_fFar;

	glm::mat4 m_mProjection;

private:
	DISALLOW_COPY_AND_ASSIGN(CCamera);
};

#endif //FABIAN_CCAMERA_H_
