#ifndef FABIAN_IOBJECT_H_
#define FABIAN_IOBJECT_H_

#include "FabianDef.h"

class IShader;
class CTransform;

class IObject
{
public:
	IObject(IObject* = nullptr);
	virtual ~IObject();
	
	virtual bool Init() = 0;
	virtual void Update(float) {}
	virtual void Draw(IShader*) {}

	CTransform *Transform();

protected:
	CTransform *m_pTransform;

private:
	DISALLOW_COPY_AND_ASSIGN(IObject);
};

#endif //FABIAN_IOBJECT_H_
