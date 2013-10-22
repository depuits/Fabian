#ifndef FABIAN_CKERNEL_H_
#define FABIAN_CKERNEL_H_

#include "FabianDef.h"
#include <list>

class IService;
class CKernel
{
public:
	static CKernel* Get();
	virtual ~CKernel();
	
	int Execute();

	bool AddService(IService*);
	void SuspendService(IService*);
	void ResumeService(IService*);
	void RemoveService(IService*);

	void KillAllServices();

	void SendMessage(ServiceMessage);

private:
	CKernel();
	static CKernel *m_pInstance;

	std::list<IService*> m_pServiceList;
	std::list<IService*> m_pPausedServiceList;

	DISALLOW_COPY_AND_ASSIGN(CKernel);
};

#endif //FABIAN_CKERNEL_H_
