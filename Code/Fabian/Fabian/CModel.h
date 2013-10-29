#ifndef FABIAN_CMODEL_H_
#define FABIAN_CMODEL_H_

#include "FabianDef.h"
#include "IObject.h"

class CModel : public IObject
{
public:
	CModel();
	virtual ~CModel();
	
	virtual bool Init();
	virtual void Draw(IShader*);

private:
	DISALLOW_COPY_AND_ASSIGN(CModel);
};

#endif //FABIAN_CMODEL_H_
