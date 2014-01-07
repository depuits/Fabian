#ifndef FABIAN_CSERVICETIMER_H_
#define FABIAN_CSERVICETIMER_H_

#include <CServiceBase.h>
#include <vector>

typedef void (*TimerCallbackFunc)(float);

//******************************************
// Class CServiceTimer:
// service responsable for sending out the dTime
//******************************************
class CServiceTimer : public CServiceBase
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	CServiceTimer(int priorety = 110);
	//-------------------------------------
	// Destructor
	virtual ~CServiceTimer();
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
	unsigned long	m_ulLastFrameIndex,
					m_ulThisFrameIndex;

	double m_dTimer;
	std::vector< TimerCallbackFunc > m_vCallbackFuncs;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceTimer);
};

#endif //FABIAN_CSERVICETIMER_H_
