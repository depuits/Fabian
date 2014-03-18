#include "CMatDifTexture.h"

#include "IShader.h"
#include "CTransform.hpp"

/************************************/
/*! Constructor
 * @param [in] pShader 	- Pointer to the IShader used in this material. 
 *            Shaders can be shared across materials
 * @param [in] pTex 	- Pointer to the diffuse image
 */
CMatDifTexture::CMatDifTexture(IShader* pShader, IImage *pTex)
    :m_pShader(pShader)
    ,m_pTexture(pTex)
{
    FASSERT(m_pShader != nullptr);
	m_iIdTexture = pShader->GetVarId("TextureSampler");
}
/************************************/
/*! Destructor */
CMatDifTexture::~CMatDifTexture()
{
}
/************************************/
/*! @warning This function must NOT be implemented in the header or the
 * linker will build the code to call the application delete()
 * function instead of the library delete() function.
 */
void CMatDifTexture::Release()
{
	delete this;
}
/************************************/
	
/************************************/
/*! Apply the material before you draw the mesh
 * @param [in] trans - Transform of the object to draw
 */
void CMatDifTexture::Apply(CTransform &trans)
{
    m_pShader->Apply();
	m_pShader->SetWorld( trans.GetWorld() );
	m_pShader->SetVarImage(m_iIdTexture, m_pTexture);
}
/************************************/


