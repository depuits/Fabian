#ifndef FABIAN_IKERNEL_H_
#define FABIAN_IKERNEL_H_

#include "FabianDef.h"
#include "ServiceMsg.h"

// --forward declarations--
class IService;
// ------------------------

//******************************************
// Interface IKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
// This is the interface created for useabilety from dll's
//******************************************
class IKernel
{
public:
	//-------------------------------------
	// Constructor
	IKernel() { }
	//-------------------------------------
	// Destructor
	virtual ~IKernel() { }
	//-------------------------------------

	//-------------------------------------
	// Start running the engine,
	//    should be called after the base services are added
	// rv - returns 0
	virtual int Execute() = 0;
	//-------------------------------------

	//-------------------------------------
	// Adds a service to the kernel and takes ownership of it
	// p1 in - a pointer to the service to add (can't be 0)(takes over ownership)
	// rv - returns pointer to the service on succes and a nullptr when it fails
	virtual IService* AddService(const char*, const char*, int) = 0; // const char*, const char*  ( dll name, seervice name )
	//-------------------------------------
	// Marks a service to be removed, the service
	//    will be deleted next loop
	// p1 in - a pointer to the service to remove
	virtual void RemoveService(IService*) = 0;
	//-------------------------------------

	//-------------------------------------
	// Mark all services to be removed and end the
	//    application by doing so
	virtual void KillAllServices() = 0;
	//-------------------------------------

	//-------------------------------------
	// Send a message to the services
	//    (including the service who sends it)
	// p1 in - pointer to SMsg object
	virtual void SendMessage(SMsg*) = 0;
	//-------------------------------------

private:

	DISALLOW_COPY_AND_ASSIGN(IKernel);
};

#endif //FABIAN_IKERNEL_H_
