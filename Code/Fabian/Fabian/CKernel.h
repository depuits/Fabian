#ifndef FABIAN_CKERNEL_H_
#define FABIAN_CKERNEL_H_

#include "IKernel.h"
#include <list>
#include "CLibraryLoader.h"

typedef struct ServiceData
{
	int LibId;
	IService* pService;
	bool bCanKill;
	int iPriority;
} ServiceData;

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************
class CKernel : public IKernel
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
	virtual int Execute();
	//-------------------------------------

	//-------------------------------------
	// Adds a service to the kernel and takes ownership of it
	// p1 in - a pointer to the service to add (can't be 0)(takes over ownership)
	// rv - returns pointer to the service on succes and a nullptr when it fails
	virtual IService* AddService(const char*, const char*, int);
	//-------------------------------------
	// Marks a service to be removed, the service
	//    will be deleted next loop
	// p1 in - a pointer to the service to remove
	virtual void RemoveService(IService*);
	//-------------------------------------

	//-------------------------------------
	// Mark all services to be removed and end the
	//    application by doing so
	virtual void KillAllServices();
	//-------------------------------------

	//-------------------------------------
	// Send a message to the services
	//    (including the service who sends it)
	// p1 in - pointer to SMsg object
	virtual void SendMessage(SMsg*);
	//-------------------------------------

private:
	//-------------------------------------
	// Constructor
	CKernel();
	//-------------------------------------

	std::list<ServiceData> m_pServiceList;
	CLibraryLoader m_LibLoader;

	DISALLOW_COPY_AND_ASSIGN(CKernel);
};

#endif //FABIAN_CKERNEL_H_
