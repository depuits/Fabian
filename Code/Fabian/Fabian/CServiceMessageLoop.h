#ifndef FABIAN_CSERVICEMESSAGELOOP_H_
#define FABIAN_CSERVICEMESSAGELOOP_H_

#include "IService.h"

class CServiceMessageLoop : public IService
{
public:
	CServiceMessageLoop(int priorety = 100);
	virtual ~CServiceMessageLoop();
	
	virtual bool Start();
	virtual void Update();
	virtual void Stop();
	
protected:

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceMessageLoop);
};

#endif //FABIAN_CSERVICEMESSAGELOOP_H_
