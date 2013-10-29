#ifndef FABIAN_IGAMEOBJECT_H_
#define FABIAN_IGAMEOBJECT_H_

#include "FabianDef.h"
#include "IObject.h"

class IGameObject : public IObject
{
public:
	IGameObject(IObject* = nullptr);
	virtual ~IGameObject();	

private:
	DISALLOW_COPY_AND_ASSIGN(IGameObject);
};

#endif //FABIAN_IGAMEOBJECT_H_
