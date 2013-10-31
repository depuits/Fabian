#ifndef FABIAN_IMESH_H_
#define FABIAN_IMESH_H_

#include "FabianDef.h"
#include <string>

class IMesh
{
public:
	IMesh() { };
	virtual ~IMesh() { };
	
	virtual bool Load(const std::wstring&) = 0;
	virtual void Draw() = 0;

private:
	DISALLOW_COPY_AND_ASSIGN(IMesh);
};

#endif //FABIAN_IMESH_H_
