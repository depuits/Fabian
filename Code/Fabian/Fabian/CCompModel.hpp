#ifndef FABIAN_CCOMPMODEL_H_
#define FABIAN_CCOMPMODEL_H_

#include "FabianDef.h"
#include "CCompBase.hpp"

#include "IMesh.h"
#include "IShader.h"
#include "IMaterial.h"


//******************************************
// Class CCompModel:
// Wrapper class to draw a meshes with a transform
//******************************************
class CCompModel : public CCompBase
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - pointer to Mesh object to draw
	// p2 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CCompModel(IMesh *pMesh, IMaterial *m_pMat)
		:CCompBase()
		,m_pMesh(pMesh)
		,m_pMaterial(m_pMat)
	{
		FASSERT(m_pMesh != nullptr && m_pMaterial != nullptr);
	}
	//-------------------------------------
	// Destructor
	virtual ~CCompModel()
	{
	}
	//-------------------------------------

	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, false if something failed
	virtual bool Start()
	{
		return true;
	}
	//-------------------------------------
	// Draws the object on the screen ussing the given shader
	// p1 in - pointer to the shader the object should draw with
	virtual void Draw()
	{
		m_pMaterial->Apply(*m_pGameObject->Transform());
		m_pMesh->Draw();
	}
	//-------------------------------------

protected:
	IMesh* m_pMesh;
	IMaterial *m_pMaterial;

private:
	DISALLOW_COPY_AND_ASSIGN(CCompModel);
};

#endif //FABIAN_CCOMPMODEL_H_
