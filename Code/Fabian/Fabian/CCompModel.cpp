#include "CCompModel.h"

#include "IMesh.h"
#include "IShader.h"
#include "IMaterial.h"
#include "CGameObject.h"

//******************************************
// Class CCompModel:
// Wrapper class to draw a meshes with a transform
//******************************************

//-------------------------------------
// Constructor
// p1 in - pointer to Mesh object to draw
// p2 in* - pointer to parent object, this causes
//            the object to be linked to the parent
CCompModel::CCompModel(IMesh *pMesh, IMaterial *m_pMat)
	:IComponent()
	,m_pMesh(pMesh)
	,m_pMaterial(m_pMat)
{
    FASSERT(m_pMesh != nullptr && m_pMaterial != nullptr);
}
//-------------------------------------
// Destructor
CCompModel::~CCompModel()
{
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, false if something failed
bool CCompModel::Start()
{
	return true;
}
//-------------------------------------
// Draws the object on the screen ussing the given shader
// p1 in - pointer to the shader the object should draw with
void CCompModel::Draw()
{
    m_pMaterial->Apply(*m_pGameObject->Transform());
	m_pMesh->Draw();
}
//-------------------------------------

