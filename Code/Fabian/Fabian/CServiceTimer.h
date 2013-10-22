#ifndef FABIAN_CSERVICETIMER_H_
#define FABIAN_CSERVICETIMER_H_

#include "IService.h"

class CServiceTimer : public IService
{
public:
	CServiceTimer(int priorety = 110);
	virtual ~CServiceTimer();
	
	virtual bool Start();
	virtual void Update();
	virtual void Stop();
	
protected:
	unsigned long	m_ulLastFrameIndex,
					m_ulThisFrameIndex;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceTimer);
};

#endif //FABIAN_CSERVICETIMER_H_
