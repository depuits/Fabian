#ifndef FABIAN_CSERVICEINPUT_H_
#define FABIAN_CSERVICEINPUT_H_

#include "IService.h"

class CInputSDL;

class CServiceInput : public IService
{
public:
	CServiceInput(int priorety = 150);
	virtual ~CServiceInput();
	
	virtual bool Start();
	virtual void Update();
	virtual void Stop();
	
	virtual void MsgProc(SMsg*);

protected:
	CInputSDL *m_pInput;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceInput);
};

#endif //FABIAN_CSERVICEINPUT_H_
