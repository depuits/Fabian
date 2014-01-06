#include "CKernel.h"

#include "IService.h"
#include <algorithm>

#include "CLog.h"

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************

//-------------------------------------
// Singleton accessor
CKernel& CKernel::Get()
{
	static CKernel kernel;
	return kernel;
}

//-------------------------------------
// Constructor
CKernel::CKernel()
{
}
//-------------------------------------
// Destructor
CKernel::~CKernel()
{
	FASSERT(m_pServiceList.size() <= 0);
}
//-------------------------------------

//-------------------------------------
// Start running the engine,
//    should be called after the base services are added
// rv - returns 0
int CKernel::Execute()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Executing Kernel" );
	
	bool bRunning(true);
	while(bRunning)
	{
		{
			{
				//PROFILE("Kernel task loop");

				std::list<IService*>::iterator it( m_pServiceList.begin() );
				for( ; it != m_pServiceList.end(); )
				{
					IService *s = (*it);
					++it;
					if( !s->GetCanKill() )
						s->Update();
					else
					{
						s->Stop();
						m_pServiceList.remove(s);
						delete s; // remove service using its dll to load
						s = nullptr;
					}
				}
				//IMMObject::CollectGarbage();
			}
	#ifdef DEBUG
			CProfileSample::Output();
	#endif
		}

		if ( m_pServiceList.size() <= 0 )
			bRunning = false;
	}
	return 0;
}
//-------------------------------------

//-------------------------------------
// Adds a service to the kernel and takes ownership of it
//    Because the kernel takes ownership of the service
//    you don't have to delete it yourself.
// Planned :
//           Return service IDs for acces (-1 on fail)
// p1 in - a pointer to the service to add (can't be 0)
// rv - returns pointer to the service on succes and a nullptr when it fails
IService* CKernel::AddService(IService* s)
{
	FASSERT(s != nullptr);

	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Adding Service" );
	if(!s->Start())
	{
		delete s;
		return nullptr;
	}

	//keep the order of priorities straight
	std::list<IService*>::iterator it( m_pServiceList.begin() );
	for( ; it != m_pServiceList.end(); ++it)
		if( (*it)->GetPriorety() > s->GetPriorety() )
			break;

	m_pServiceList.insert(it, s);
	return s;
}
//-------------------------------------

//-------------------------------------
// Suspend or resume a service
// !!! - these methods might be removed
// p1 in - a pointer to the service to suspend or resume
// rv - returns true on succes
void CKernel::SuspendService(IService*)
{
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Kernel: Suspend Service Disabled" );
	//check that this task is in our list - we don't want to suspend
	//a task that isn't running
	/*if( std::find(m_pServiceList.begin(), m_pServiceList.end(), s) != m_pServiceList.end() )
	{
		s->OnSuspend();
		m_pServiceList.remove(s);
		m_pPausedServiceList.push_back(s);
	}*/
}
void CKernel::ResumeService(IService*)
{
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Kernel: Resume Service Disabled" );
	/*if( std::find(m_pPausedServiceList.begin(), m_pPausedServiceList.end(), s) != m_pPausedServiceList.end() )
	{
		s->OnResume();
		m_pPausedServiceList.remove(s);

		//keep the order of priorities straight
		std::list<IService*>::iterator it( m_pServiceList.begin() );
		for( ; it != m_pServiceList.end(); ++it)
			if( (*it)->GetPriorety() > s->GetPriorety() )
				break;

		m_pServiceList.insert(it, s);
	}*/
}
//-------------------------------------
// Marks a service to be removed, the service
//    will be deleted next loop
// p1 in - a pointer to the service to remove
void CKernel::RemoveService(IService* s)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Removing Service" );
	if( std::find(m_pServiceList.begin(), m_pServiceList.end(), s) != m_pServiceList.end() )
		s->SetCanKill(true);
}
//-------------------------------------

//-------------------------------------
// Mark all services to be removed and end the
//    application by doing so
void CKernel::KillAllServices()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Killing All Services" );
	for(std::list<IService*>::iterator it( m_pServiceList.begin() ); it != m_pServiceList.end(); ++it)
		(*it)->SetCanKill(true);
}
//-------------------------------------

//-------------------------------------
// Send a message to the services
//    (including the service who sends it)
// p1 in - pointer to SMsg object
void CKernel::SendMessage(SMsg* msg)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Message Broadcast: %d", msg->id );
	if( msg->id == SM_QUIT )
		KillAllServices();

	for(std::list<IService*>::iterator it( m_pServiceList.begin() ); it != m_pServiceList.end(); ++it)
		(*it)->MsgProc(msg);
}
//-------------------------------------




