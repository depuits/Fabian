#ifndef FABIAN_CKERNEL_H_
#define FABIAN_CKERNEL_H_

#include "FabianDef.h"
#include "ServiceMsg.h"
#include <list>

// --forward declarations--
class IService;
// ------------------------

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************
class CKernel
{
public:
	//-------------------------------------
	// Singleton accessor
	static CKernel& Get();
	//-------------------------------------
	// Destructor
	virtual ~CKernel();
	//-------------------------------------

	//-------------------------------------
	// Start running the engine,
	//    should be called after the base services are added
	// rv - returns 0
	int Execute();
	//-------------------------------------

	//-------------------------------------
	// Adds a service to the kernel and takes ownership of it
	// p1 in - a pointer to the service to add (can't be 0)(takes over ownership)
	// rv - returns pointer to the service on succes and a nullptr when it fails
	IService* AddService(IService*);
	//-------------------------------------

	//-------------------------------------
	// Planned :
	//           Use service ID to interact with the services
	//              instead of pointers
	//-------------------------------------
	// Suspend or resume a service
	// !!! - these methods might be removed
	// p1 in - a pointer to the service to suspend or resume
	// rv - returns true on succes
	void SuspendService(IService*);
	void ResumeService(IService*);
	//-------------------------------------
	// Marks a service to be removed, the service
	//    will be deleted next loop
	// p1 in - a pointer to the service to remove
	void RemoveService(IService*);
	//-------------------------------------

	//-------------------------------------
	// Mark all services to be removed and end the
	//    application by doing so
	void KillAllServices();
	//-------------------------------------

	//-------------------------------------
	// Send a message to the services
	//    (including the service who sends it)
	// p1 in - pointer to SMsg object
	void SendMessage(SMsg*);
	//-------------------------------------

private:
	//-------------------------------------
	// Constructor
	CKernel();
	//-------------------------------------

	std::list<IService*> m_pServiceList;
	std::list<IService*> m_pPausedServiceList;

	DISALLOW_COPY_AND_ASSIGN(CKernel);
};

#endif //FABIAN_CKERNEL_H_
