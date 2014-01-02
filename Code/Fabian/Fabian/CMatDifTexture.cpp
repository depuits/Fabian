#include "CMatDifTexture.h"

#include "IShader.h"
#include "CTransform.h"

CMatDifTexture::CMatDifTexture(IShader* pShader, IImage *pTex)
    :IMaterial(pShader)
    ,m_pTexture(pTex)
{
	m_iIdTexture = pShader->GetVarId("TextureSampler");
}

CMatDifTexture::~CMatDifTexture()
{
}

void CMatDifTexture::Apply(CTransform *pTransform)
{
    m_pShader->Apply();
	m_pShader->SetWorld( pTransform->GetWorld() );
	m_pShader->SetVarImage(m_iIdTexture, m_pTexture);
}

