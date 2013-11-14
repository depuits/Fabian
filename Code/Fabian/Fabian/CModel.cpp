#include "CModel.h"

#include "IShader.h"
#include "IMesh.h"
#include "CTransform.h"

//******************************************
// Class CModel:
// Wrapper class to draw a meshes with a transform
//******************************************

//-------------------------------------
// Constructor
// p1 in - pointer to Mesh object to draw
// p2 in* - pointer to parent object, this causes
//            the object to be linked to the parent
CModel::CModel(IMesh* pMesh, IObject* pParent)
	:IObject(pParent)
	,m_pMesh(pMesh)
{
}
//-------------------------------------
// Destructor
CModel::~CModel()
{
}
//-------------------------------------
	
//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, false if something failed	
bool CModel::Init()
{	
	return (m_pMesh != nullptr);
}
//-------------------------------------
// Draws the object on the screen ussing the given shader
// p1 in - pointer to the shader the object should draw with
void CModel::Draw(IShader* pShader)
{
	pShader->SetWorld( Transform()->GetWorld() );
	m_pMesh->Draw();
}
//-------------------------------------

