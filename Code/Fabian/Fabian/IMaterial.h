#ifndef FABIAN_IMATERIAL_H_
#define FABIAN_IMATERIAL_H_

#include "FabianDef.h"

// --forward declarations--
class IShader;
class CTransform;
// ------------------------

//******************************************
// Interface IMaterial:
// material classes are used for easy acces to
// shader variables and remembering them for future
// draw calls.
//******************************************
class IMaterial
{
public:
	//-------------------------------------
	// Constructor
	IMaterial() { }
	//-------------------------------------
	// Destructor
	virtual ~IMaterial() { }
	//-------------------------------------
	
	//-------------------------------------
	// Apply the material before you draw the mesh
	// p1 in - transform of the object to draw
    virtual void Apply(CTransform&) = 0;
	//-------------------------------------

private:
    DISALLOW_COPY_AND_ASSIGN(IMaterial);
};

#endif // FABIAN_IMATERIAL_H_
