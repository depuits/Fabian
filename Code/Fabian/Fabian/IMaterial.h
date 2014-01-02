#ifndef FABIAN_IMATERIAL_H_
#define FABIAN_IMATERIAL_H_

#include "FabianDef.h"

class IShader;
class CTransform;

class IMaterial
{
public:
    IMaterial(IShader*);
    virtual ~IMaterial();

    virtual void Apply(CTransform*) = 0;

    IShader *GetShader() { return m_pShader; }

protected:
    IShader *m_pShader;

private:
    DISALLOW_COPY_AND_ASSIGN(IMaterial);
};

#endif // FABIAN_IMATERIAL_H_
