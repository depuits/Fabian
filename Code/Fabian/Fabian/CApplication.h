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
	IService	*m_pServiceVideo,
				*m_pServiceMsgLoop,
				*m_pServiceTimer,
				*m_pServiceGame,
				*m_pServiceInput;

	DISALLOW_COPY_AND_ASSIGN(CApplication);
};

#endif //FABIAN_CAPPLICATION_H_
