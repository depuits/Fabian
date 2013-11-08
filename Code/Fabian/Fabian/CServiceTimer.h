#ifndef FABIAN_CSERVICETIMER_H_
#define FABIAN_CSERVICETIMER_H_

#include "IService.h"

//******************************************
// Class CServiceTimer:
// service responsable for sending out the dTime
//******************************************
class CServiceTimer : public IService
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
	
protected:
	unsigned long	m_ulLastFrameIndex,
					m_ulThisFrameIndex;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceTimer);
};

#endif //FABIAN_CSERVICETIMER_H_
