#ifndef FABIAN_CCOMPMODEL_H_
#define FABIAN_CCOMPMODEL_H_

#include "FabianDef.h"
#include "CCompBase.hpp"

#include "IMesh.h"
#include "IShader.h"
#include "IMaterial.h"


////////////////////////////////////////////
//! Class CCompModel: 
//! Wrapper class to draw a meshes with a transform
////////////////////////////////////////////
class CCompModel : public CCompBase
{
public:
	/************************************/
	/*! Constructor
	 * @param [in] pMesh - Pointer to IMesh object to draw
	 * @param [in] pMat	 - pointer to IMaterial to draw the IMesh with
	 */
	CCompModel(IMesh *pMesh, IMaterial *pMat)
		:CCompBase()
		,m_pMesh(pMesh)
		,m_pMaterial(pMat)
	{
		FASSERT(m_pMesh != nullptr && m_pMaterial != nullptr);
	}
	/************************************/
	/*! Destructor */
	virtual ~CCompModel()
	{
	}
	/************************************/

	/************************************/
	/*! Initializes the object, should be called before any other
	 *    method of the object.
	 * @return False if something failed
	 */
	virtual bool Start()
	{
		return true;
	}
	/************************************/
	/*! Draws the object on the screen */
	virtual void Draw()
	{
		m_pMaterial->Apply(*m_pGameObject->Transform());
		m_pMesh->Draw();
	}
	/************************************/

protected:
	IMesh* m_pMesh;
	IMaterial *m_pMaterial;

private:
	DISALLOW_COPY_AND_ASSIGN(CCompModel);
};

#endif //FABIAN_CCOMPMODEL_H_
