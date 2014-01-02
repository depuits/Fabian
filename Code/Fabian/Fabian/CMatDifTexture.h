#ifndef FABIAN_CMATDIFTEXTURE_H_
#define FABIAN_CMATDIFTEXTURE_H_

#include "IMaterial.h"
class IImage;

class CMatDifTexture : public IMaterial
{
public:
    CMatDifTexture(IShader*, IImage*);
    virtual ~CMatDifTexture();

    virtual void Apply(CTransform*);


protected:
    int m_iIdTexture;
    IImage* m_pTexture;

private:
    DISALLOW_COPY_AND_ASSIGN(CMatDifTexture);
};

#endif // FABIAN_CMATDIFTEXTURE_H_
