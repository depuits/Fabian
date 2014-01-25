#ifndef FABIAN_CSERVICEBASE_H_
#define FABIAN_CSERVICEBASE_H_

#include "IService.h"


//******************************************
// Class CServiceBase:
// base service class with default method implemented
//******************************************
class CServiceBase : public IService
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	CServiceBase()
		:IService()
	{
	};
	//-------------------------------------
	// Destructor
	virtual ~CServiceBase() { };
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
	DISALLOW_COPY_AND_ASSIGN(CServiceBase);
};

#endif //FABIAN_CSERVICEBASE_H_
