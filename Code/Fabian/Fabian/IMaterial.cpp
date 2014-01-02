#include "IMaterial.h"

IMaterial::IMaterial(IShader* pShader)
    :m_pShader(pShader)
{
    FASSERT(m_pShader != nullptr);
}

IMaterial::~IMaterial()
{
}

