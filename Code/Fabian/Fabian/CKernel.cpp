#include "CKernel.h"

#include <SDL.h>
#include "IService.h"

//******************************************
// Class CKernel:
// the kernel class is the heart of the engine
// this class manages all services and the messaging between them
//******************************************

//-------------------------------------
// Singleton variable
CKernel* CKernel::m_pInstance = nullptr;
//------------------------------------

//-------------------------------------
// Singleton accessor
CKernel* CKernel::Get()
{
	if( m_pInstance == nullptr ) m_pInstance = new CKernel();
	return m_pInstance;
}

//-------------------------------------
// Constructor
CKernel::CKernel()
	:m_pServiceInit(nullptr)
{
	SDL_Init(0);
}
//-------------------------------------
// Destructor
CKernel::~CKernel()
{
	FASSERT(m_pServiceList.size() <= 0);

	m_pInstance = nullptr;
	SDL_Quit();
}
//-------------------------------------
	
//-------------------------------------
// Start running the engine, 
//    should be called after the base services are added
// rv - returns 0
int CKernel::Execute()
{
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
						delete s;
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
// rv - returns true on succes
bool CKernel::AddService(IService* s)
{
	m_pServiceInit = s;
	if(!s->Start())
	{
		delete s;
		m_pServiceInit = nullptr;
		return false;
	}

	//keep the order of priorities straight
	std::list<IService*>::iterator it( m_pServiceList.begin() );
	for( ; it != m_pServiceList.end(); ++it)
		if( (*it)->GetPriorety() > s->GetPriorety() )
			break;

	m_pServiceList.insert(it, s);
	m_pServiceInit = nullptr;
	return true;
}
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
void CKernel::SuspendService(IService* s)
{
	//check that this task is in our list - we don't want to suspend
	//a task that isn't running
	if( std::find(m_pServiceList.begin(), m_pServiceList.end(), s) != m_pServiceList.end() )
	{
		s->OnSuspend();
		m_pServiceList.remove(s);
		m_pPausedServiceList.push_back(s);
	}
}
void CKernel::ResumeService(IService* s)
{
	if( std::find(m_pPausedServiceList.begin(), m_pPausedServiceList.end(), s) != m_pPausedServiceList.end() )
	{
		s->OnResume();
		m_pPausedServiceList.remove(s);
	
		//keep the order of priorities straight
		std::list<IService*>::iterator it( m_pServiceList.begin() );
		for( ; it != m_pServiceList.end(); ++it)
			if( (*it)->GetPriorety() > s->GetPriorety() )
				break;

		m_pServiceList.insert(it, s);
	}
}
//-------------------------------------
// Marks a service to be removed, the service
//    will be deleted next loop
// p1 in - a pointer to the service to remove
void CKernel::RemoveService(IService* s)
{
	if( std::find(m_pServiceList.begin(), m_pServiceList.end(), s) != m_pServiceList.end() )
		s->SetCanKill(true);
}
//-------------------------------------

//-------------------------------------
// Mark all services to be removed and end the
//    application by doing so
void CKernel::KillAllServices()
{
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
	if( msg->id == SM_QUIT )
		KillAllServices();

	for(std::list<IService*>::iterator it( m_pServiceList.begin() ); it != m_pServiceList.end(); ++it)
		(*it)->MsgProc(msg);

	if( m_pServiceInit != nullptr )
		m_pServiceInit->MsgProc(msg);
}
//-------------------------------------




