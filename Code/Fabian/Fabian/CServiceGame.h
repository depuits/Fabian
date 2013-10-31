#ifndef FABIAN_CSERVICEGAME_H_
#define FABIAN_CSERVICEGAME_H_

#include "IService.h"

class IInput;
class CServiceGame : public IService
{
public:
	CServiceGame(int priorety = 500);
	virtual ~CServiceGame();
	
	virtual bool Start();
	virtual void Update();
	virtual void Stop();
	
	virtual void MsgProc(SMsg*);

protected:
	IInput *m_pInput;
	float m_fDtime;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceGame);
};

#endif //FABIAN_CSERVICEGAME_H_
