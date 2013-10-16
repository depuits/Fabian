#ifndef FABIAN_CKERNEL_H_
#define FABIAN_CKERNEL_H_

#include "FabianDef.h"
#include <list>

class IService;
class CKernel
{
public:
	CKernel();
	virtual ~CKernel();
	
	bool AddTask(IService*);
	void SuspendTask(IService*);
	void ResumeTask(IService*);
	void RemoveTask(IService*);

	void KillAllTasks();

private:
	std::list<IService*> m_pTaskList;
	std::list<IService*> m_pPausedTaskList;

	DISALLOW_COPY_AND_ASSIGN(CKernel);
};

#endif //FABIAN_CKERNEL_H_
