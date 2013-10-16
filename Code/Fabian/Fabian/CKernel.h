#ifndef FABIAN_CKERNEL_H_
#define FABIAN_CKERNEL_H_

#include "FabianDef.h"
#include <list>

class ITask;
class CKernel
{
public:
	CKernel();
	virtual ~CKernel();
	
	bool AddTask(ITask*);
	void SuspendTask(ITask*);
	void ResumeTask(ITask*);
	void RemoveTask(ITask*);

	void KillAllTasks();

private:
	std::list<ITask*> m_pTaskList;
	std::list<ITask*> m_pPausedTaskList;

	DISALLOW_COPY_AND_ASSIGN(CKernel);
};

#endif //FABIAN_CKERNEL_H_
