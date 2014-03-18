#ifndef FABIAN_ICAMERA_H_
#define FABIAN_ICAMERA_H_

#include "FabianDef.h"

FDISABLE_WARNING_START(4201)
#include "glm/glm.hpp"
FDISABLE_WARNING_END(4201)

////////////////////////////////////////////
//! Interface ICamera: 
//! interface for getting default camera patameters
////////////////////////////////////////////
class ICamera
{
public:
	/************************************/
	/*! Constructor */
	ICamera() { }
	/************************************/
	/*! Destructor */
	virtual ~ICamera() { }
	/************************************/
	
	/************************************/
	/// @{
	/*! Get the view or projection matrix of this camera
	 * @return Matrix
	 */
	virtual glm::mat4& GetProjection() = 0;
	virtual glm::mat4& GetView() = 0;
	/// @}
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(ICamera);
};

#endif //FABIAN_ICAMERA_H_
