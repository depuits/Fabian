#ifndef FABIAN_IIMAGE_H_
#define FABIAN_IIMAGE_H_

#include "FabianDef.h"
#include "DataStructures.h"

////////////////////////////////////////////
//! Interface IImage: 
//! the image object is responsible for loading 
//! the image data in the render interface
////////////////////////////////////////////
class IImage
{
public:
	/************************************/
	/*! Constructor */
	IImage() { };
	/************************************/
	/*! Destructor */
	virtual ~IImage() { };
	/************************************/
	
	/************************************/
	/*! Loads and initializes the mesh by loading any needed buffers, etc.
	 * @param [in] id - Pointer to the ImageData for the image
	 * @return False if something failed
	 */
	virtual bool Load(ImageData* id) = 0;
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(IImage);
};

#endif //FABIAN_IIMAGE_H_
