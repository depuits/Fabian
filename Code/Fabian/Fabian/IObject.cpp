#include "IObject.h"
#include "CTransform.h"

IObject::IObject(IObject* pPar)
{
	if( pPar != nullptr )
		m_pTransform = new CTransform(pPar->Transform());
	else
		m_pTransform = new CTransform();
}
IObject::~IObject()
{
	delete m_pTransform;
}

CTransform *IObject::Transform()
{
	return m_pTransform;
}


