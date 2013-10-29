#ifndef FABIAN_CSERVICEGAME_H_
#define FABIAN_CSERVICEGAME_H_

#include "IService.h"

class CServiceGame : public IService
{
public:
	CServiceGame(int priorety = 500);
	virtual ~CServiceGame();
	
	virtual bool Start();
	virtual void Update();
	virtual void Stop();
	
	virtual void MsgProc(ServiceMessage);

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceGame);
};

#endif //FABIAN_CSERVICEGAME_H_
