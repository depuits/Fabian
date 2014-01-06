#ifndef FABIAN_CMATDIFTEXTURE_H_
#define FABIAN_CMATDIFTEXTURE_H_

#include "IMaterial.h"

// --forward declarations--
class IImage;
// ------------------------

//******************************************
// Class CMatDifTexture:
// simple diffusetexture material class
//******************************************
class CMatDifTexture : public IMaterial
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - pointer to the shader used in this material
	//            Shaders can be shared across materials
	// p2 in - pointer to the diffuse image
    CMatDifTexture(IShader*, IImage*);
	//-------------------------------------
	// Destructor
    virtual ~CMatDifTexture();
	//-------------------------------------
	
	//-------------------------------------
	// Apply the material before you draw the mesh
	// p1 in - transform of the object to draw
    virtual void Apply(CTransform&);
	//-------------------------------------


protected:
    int m_iIdTexture;
    IImage* m_pTexture;

private:
    DISALLOW_COPY_AND_ASSIGN(CMatDifTexture);
};

#endif // FABIAN_CMATDIFTEXTURE_H_
