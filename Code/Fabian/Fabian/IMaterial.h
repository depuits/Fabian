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
	// p1 in - pointer to the shader used in this material
	//            Shaders can be shared across materials
	// change from IShader* to nothing so the material can choos what to use
	// ex: ask for renderer and load shader itself
    IMaterial(IShader*);
	//-------------------------------------
	// Destructor
    virtual ~IMaterial();
	//-------------------------------------
	
	//-------------------------------------
	// Apply the material before you draw the mesh
	// p1 in - transform of the object to draw
    virtual void Apply(CTransform&) = 0;
	//-------------------------------------
	
	//-------------------------------------
	// gives the used shader of this material
	// rv - pointer to the shader used in this material
    IShader *GetShader() { return m_pShader; }
	//-------------------------------------

protected:
    IShader *m_pShader;

private:
    DISALLOW_COPY_AND_ASSIGN(IMaterial);
};

#endif // FABIAN_IMATERIAL_H_
