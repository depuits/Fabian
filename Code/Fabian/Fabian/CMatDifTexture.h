#ifndef FABIAN_CMATDIFTEXTURE_H_
#define FABIAN_CMATDIFTEXTURE_H_

#include "IMaterial.h"

// --forward declarations--
class IShader;
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
    // This function must not be implemented in the header or the
    // linker will build the code to call the application delete()
    // function instead of the library delete() function.
    virtual void Release();
	//-------------------------------------
	
	//-------------------------------------
	// Apply the material before you draw the mesh
	// p1 in - transform of the object to draw
    virtual void Apply(CTransform&);
	//-------------------------------------

	//-------------------------------------
	// gives the used shader of this material
	// rv - pointer to the shader used in this material
    IShader *GetShader() { return m_pShader; }
	//-------------------------------------


protected:
	//-------------------------------------
	// Destructor
    virtual ~CMatDifTexture();
	//-------------------------------------

    IShader *m_pShader;

    int m_iIdTexture;
    IImage* m_pTexture;

private:
    DISALLOW_COPY_AND_ASSIGN(CMatDifTexture);
};

#endif // FABIAN_CMATDIFTEXTURE_H_
