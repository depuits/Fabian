#include "CModel.h"

#include "IShader.h"
#include "IMesh.h"
#include "CTransform.h"

CModel::CModel(IMesh* pMesh, IObject* pParent)
	:IObject(pParent)
	,m_pMesh(pMesh)
{
}
CModel::~CModel()
{
}
	
bool CModel::Init()
{	

	return true;
}

void CModel::Draw(IShader* pShader)
{
	pShader->SetWorld( Transform()->GetWorld() );
	m_pMesh->Draw();
}

