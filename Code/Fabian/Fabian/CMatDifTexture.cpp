#include "CMatDifTexture.h"

#include "IShader.h"
#include "CTransform.h"

//******************************************
// Class CMatDifTexture:
// simple diffusetexture material class
//******************************************
CMatDifTexture::CMatDifTexture(IShader* pShader, IImage *pTex)
    :IMaterial(pShader)
    ,m_pTexture(pTex)
{
	m_iIdTexture = pShader->GetVarId("TextureSampler");
}
//-------------------------------------
// Destructor
CMatDifTexture::~CMatDifTexture()
{
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


