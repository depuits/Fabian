#ifndef FABIAN_ISERVICE_H_
#define FABIAN_ISERVICE_H_

#include "FabianDef.h"
#include "ServiceMsg.h"


//******************************************
// Interface IService:
// the interface for all service, used to define
// parts of the game
// ex.: rendering, input, physics, AI, ...
// !!! should be a pure interface for dll usage
//        going to create a CServiceBase with this implementation
//        for easy use
//******************************************
class IService
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	IService(int priorety = 5000)
		:m_bCanKill(false)
		,m_iPriority(priorety)
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
	
	//-------------------------------------
	// Get/Set weither this service is marked for remove
	// rv / p1 in - bool, true if its marked for remove
	bool GetCanKill() const { return m_bCanKill; };
	void SetCanKill(bool canKill) { m_bCanKill = canKill; };	
	//-------------------------------------
	// Get the priorety of this service
	// rv - int, priorety number
	int GetPriorety() const { return m_iPriority; };
	//void SetPriorety(int priorety) { m_iPriority = priorety; }; // shouldn't be set once running to avoid reordening
	//-------------------------------------

protected:
	bool m_bCanKill;
	int m_iPriority;

private:
	DISALLOW_COPY_AND_ASSIGN(IService);
};

#endif //FABIAN_ISERVICE_H_
