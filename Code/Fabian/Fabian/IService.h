#ifndef FABIAN_ISERVICE_H_
#define FABIAN_ISERVICE_H_

#include "FabianDef.h"
#include "ServiceMsg.h"


//******************************************
// Interface IService:
// the interface for all service, used to define
// parts of the game
// ex.: rendering, input, physics, AI, ...
//******************************************
class IService
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	IService()
	{
	};
	//-------------------------------------
	// Destructor
	virtual ~IService() { };
	//-------------------------------------
	
	//-------------------------------------
	// Called when the service is registered in the kernel
	// rv - return true on succes, 
	//         when false is returned then the service gets deleted
	virtual bool Start() = 0;
	//-------------------------------------
	// Called when the service is suspended
	virtual void OnSuspend() { };
	//-------------------------------------
	// Called every time the service has to update
	virtual void Update() = 0;
	//-------------------------------------
	// Called when the service returns from being suspended
	virtual void OnResume() { };
	//-------------------------------------
	// Called when the service will be deleted
	virtual void Stop() = 0;
	//-------------------------------------
	
	//-------------------------------------
	// Called when there are messages send somewhere
	// p1 in - pointer to SMsg object
	virtual void MsgProc(SMsg*) { };
	//-------------------------------------

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(IService);
};

#endif //FABIAN_ISERVICE_H_
