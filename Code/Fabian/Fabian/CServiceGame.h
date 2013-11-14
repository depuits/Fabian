#ifndef FABIAN_CSERVICEGAME_H_
#define FABIAN_CSERVICEGAME_H_

#include "IService.h"

// --forward declarations--
class IInput;
class IRenderer;
// ------------------------

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CServiceGame : public IService
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	CServiceGame(int priorety = 500);
	//-------------------------------------
	// Destructor
	virtual ~CServiceGame();
	//-------------------------------------
	
	//-------------------------------------
	// Called when the service is registered in the kernel
	// rv - return true on succes, 
	//         when false is returned then the service gets deleted	
	virtual bool Start();
	//-------------------------------------
	// Called every time the service has to update
	virtual void Update();
	//-------------------------------------
	// Called when the service will be deleted
	virtual void Stop();
	//-------------------------------------
	
	//-------------------------------------
	// Called when there are messages send somewhere
	// p1 in - pointer to SMsg object
	virtual void MsgProc(SMsg*);
	//-------------------------------------

protected:
	IInput *m_pInput;
	IRenderer *m_pRenderer;
	float m_fDtime;

	double m_dTimer;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceGame);
};

#endif //FABIAN_CSERVICEGAME_H_
