#include "CCompModel.h"

#include "IShader.h"
#include "IMesh.h"
#include "CGameObject.h"

//******************************************
// Class CCompModel:
// Wrapper class to draw a meshes with a transform
//******************************************
int CCompModel::s_iIdWorld = -1;

//-------------------------------------
// Constructor
// p1 in - pointer to Mesh object to draw
// p2 in* - pointer to parent object, this causes
//            the object to be linked to the parent
CCompModel::CCompModel(IMesh* pMesh)
	:IComponent()
	,m_pMesh(pMesh)
{
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
	return (m_pMesh != nullptr);
}
//-------------------------------------
// Draws the object on the screen ussing the given shader
// p1 in - pointer to the shader the object should draw with
void CCompModel::Draw(IShader* pShader)
{
	if( s_iIdWorld == -1 )
		s_iIdWorld = pShader->GetVarId("Model");

	pShader->SetVarMat4( s_iIdWorld, m_pGameObject->Transform()->GetWorld() );
	m_pMesh->Draw();
}
//-------------------------------------

