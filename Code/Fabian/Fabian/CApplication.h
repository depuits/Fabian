#ifndef FABIAN_CAPPLICATION_H_
#define FABIAN_CAPPLICATION_H_

#include "FabianDef.h"

class CKernel;
class IService;

class CApplication
{
public:
	CApplication();
	virtual ~CApplication();
	
	int Run(int argc, char *argv[]);

private:
	DISALLOW_COPY_AND_ASSIGN(CApplication);
};

#endif //FABIAN_CAPPLICATION_H_
