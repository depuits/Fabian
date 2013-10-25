#ifndef FABIAN_CMODEL_H_
#define FABIAN_CMODEL_H_

#include "FabianDef.h"

class CModel
{
public:
	CModel();
	virtual ~CModel();
	
	virtual void Load();
	virtual void Draw();

private:
	DISALLOW_COPY_AND_ASSIGN(CModel);
};

#endif //FABIAN_CMODEL_H_
