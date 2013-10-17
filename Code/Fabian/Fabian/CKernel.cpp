#include "CKernel.h"

#include <SDL.h>
#include "IService.h"


CKernel::CKernel()
{
	SDL_Init(0);
}
CKernel::~CKernel()
{
	SDL_Quit();
}
	
int CKernel::Execute()
{
	bool bRunning(true);
	while(bRunning)
	{
		if ( m_pServiceList.size() <= 0 )
			bRunning = false;
		{
			{
				//PROFILE("Kernel task loop");
			
				std::list<IService*>::iterator it( m_pServiceList.begin() );
				for( ; it != m_pServiceList.end(); ++it)
				{
					IService *s = (*it);
					if( !s->GetCanKill() )
						s->Update();
					else
					{
						s->Stop();
						m_pServiceList.remove(s);
					}
				}
				//IMMObject::CollectGarbage();
			}
	#ifdef DEBUG
			CProfileSample::Output();
	#endif
		}
	}

	return 0;
}
bool CKernel::AddService(IService* s)
{
	if(!s->Start())
		return false;

	//keep the order of priorities straight
	std::list<IService*>::iterator it( m_pServiceList.begin() );
	for( ; it != m_pServiceList.end(); ++it)
		if( (*it)->GetPriorety() > s->GetPriorety() )
			break;

	m_pServiceList.insert(it, s);
	return true;
}
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
void CKernel::RemoveService(IService* s)
{
	if( std::find(m_pServiceList.begin(), m_pServiceList.end(), s) != m_pServiceList.end() )
		s->SetCanKill(true);
}

void CKernel::KillAllServices()
{
	for(std::list<IService*>::iterator it( m_pServiceList.begin() ); it != m_pServiceList.end(); ++it)
		(*it)->SetCanKill(true);
}


