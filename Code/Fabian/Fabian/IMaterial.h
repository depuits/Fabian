#ifndef FABIAN_IMATERIAL_H_
#define FABIAN_IMATERIAL_H_

#include "FabianDef.h"

// --forward declarations--
class IShader;
class CTransform;
// ------------------------

////////////////////////////////////////////
//! Interface IMaterial:
//! material classes are used for easy access to 
//! shader variables and remembering them for future 
//! draw calls.
////////////////////////////////////////////
class IMaterial
{
public:
	/************************************/
	/*! Constructor */
	IMaterial() { }
	/************************************/
    /*! @warning This function must NOT be implemented in the header or the
     * linker will build the code to call the application delete()
     * function instead of the library delete() function.
	 */
    virtual void Release() = 0;
	/************************************/
	
	/************************************/
	/*! Apply the material before you draw the mesh
	 * @param [in] trans - Transform of the object to draw
	 */
    virtual void Apply(CTransform& trans) = 0;
	/************************************/

protected:
	/************************************/
	/*! Destructor */
	virtual ~IMaterial() { }
	/************************************/

private:
    DISALLOW_COPY_AND_ASSIGN(IMaterial);
};

#endif // FABIAN_IMATERIAL_H_
