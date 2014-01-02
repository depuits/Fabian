#ifndef FABIAN_ICAMERA_H_
#define FABIAN_ICAMERA_H_

#include "FabianDef.h"

FDISABLE_WARNING_START(4201)
#include <glm/glm.hpp>
FDISABLE_WARNING_END(4201)

//******************************************
// Class CCompCamera:
// A basic camera for drawing scenes, including
// the most simple settings.
//******************************************
class ICamera
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	ICamera() { }
	//-------------------------------------
	// Destructor
	virtual ~ICamera() { }
	//-------------------------------------

	virtual glm::mat4& GetProjection() = 0;
	virtual glm::mat4& GetView() = 0;

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(ICamera);
};

#endif //FABIAN_ICAMERA_H_
