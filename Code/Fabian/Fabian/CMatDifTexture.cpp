#include "CMatDifTexture.h"

#include "IShader.h"
#include "CTransform.hpp"

//******************************************
// Class CMatDifTexture:
// simple diffuse texture material class
//******************************************
CMatDifTexture::CMatDifTexture(IShader* pShader, IImage *pTex)
    :m_pShader(pShader)
    ,m_pTexture(pTex)
{
    FASSERT(m_pShader != nullptr);
	m_iIdTexture = pShader->GetVarId("TextureSampler");
}
//-------------------------------------
// Destructor
CMatDifTexture::~CMatDifTexture()
{
}
//-------------------------------------
// This function must NOT be implemented in the header or the
// linker will build the code to call the application delete()
// function instead of the library delete() function.
void CMatDifTexture::Release()
{
	delete this;
}
//-------------------------------------
	
//-------------------------------------
// Apply the material before you draw the mesh
// p1 in - transform of the object to draw
void CMatDifTexture::Apply(CTransform &pTransform)
{
    m_pShader->Apply();
	m_pShader->SetWorld( pTransform.GetWorld() );
	m_pShader->SetVarImage(m_iIdTexture, m_pTexture);
}
//-------------------------------------


