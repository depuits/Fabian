#ifndef FABIAN_CSERVICEMESSAGELOOP_H_
#define FABIAN_CSERVICEMESSAGELOOP_H_

#include "IService.h"

//******************************************
// Class CServiceMessageLoop:
// service responsable for handling message from the system
// this is needed for moving and closing the window
// !!! this seric should merge with the video update service
//        because this is handling the messages from the created
//        window from that service
//******************************************
class CServiceMessageLoop : public IService
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	CServiceMessageLoop(int priorety = 100);
	//-------------------------------------
	// Destructor
	virtual ~CServiceMessageLoop();
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

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceMessageLoop);
};

#endif //FABIAN_CSERVICEMESSAGELOOP_H_
