#include "CKernel.h"

#include "IService.h"
#include <algorithm>

#include "CLog.h"


bool operator== (const ServiceData& a, const ServiceData& b)
{
	return (a.pService == b.pService);
}

bool operator== (const ServiceData& a, const IService* b)
{
	return (a.pService == b);
}

/************************************/
/*! Singleton accessor 
 * @return Pointer to CKernel singleton object
 */
CKernel& CKernel::Get()
{
	static CKernel kernel;
	return kernel;
}
/************************************/
/*! Constructor */
CKernel::CKernel()
	:IKernel()
{
}
/************************************/
/*! Destructor */
CKernel::~CKernel()
{
	FASSERT(m_pServiceList.size() <= 0);
}
/************************************/

/************************************/
/*! Start running the engine,
 *    should be called after the base services are added
 * @return 0
 */
int CKernel::Execute()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Executing Kernel" );
	
	bool bRunning(true);
	while(bRunning)
	{
		{
			{
				/// @todo PROFILE("Kernel task loop");

				std::list<ServiceData>::iterator it( m_pServiceList.begin() );
				for( ; it != m_pServiceList.end(); )
				{
					ServiceData &s = (*it);
					++it;
					if( !s.bCanKill )
						s.pService->Update();
					else
					{
						s.pService->Stop();

						// call lib functions here to free the services
						void (*funcFree)(IService*) = (void(*)(IService*))m_LibLoader.GetFunction(s.LibId, "ReleaseService");
						if( funcFree == nullptr )
						{
							//crash and burn
							CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Failed to load unloading function for service, trying normal delete ( high crash potential )" );
							delete s.pService;
						}
						else
							funcFree(s.pService); // remove service using its dll to load

						m_pServiceList.remove(s);
					}
				}
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
/************************************/

/************************************/
/*! Loads a new IService into the kernel from a library
 * @param [in] sLib		Lib file from which to load the service
 * @param [in] sService	Name of the service to load (one lib can contain multiple services)
 * @param [in] iPrior	The priority of this service
 * @return Pointer to the service on success and a nullptr when it fails
 */
IService* CKernel::AddService(const char* sLib, const char* sService, int iPrior)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Adding Service\nLib: %s\nService: %s", sLib, sService );

	std::string sExt =
#if defined WIN32 /*windows*/
    ".dll";
#elif defined UNIX /*unix*/
    ".so";
#else
#error PLATFORM NOT IMPLENTED
#endif

	int lib = m_LibLoader.LoadLib( std::string(sLib + sExt).c_str() );
	if(lib == -1 )
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Kernel: Loading lib \"%s\" failed.", sLib );
		return nullptr;
	}
	
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Lib loaded(id: %d), now checking functions", lib );
	IService *(*funcLoad)(const char*) = (IService*(*)(const char*))m_LibLoader.GetFunction(lib, "LoadService");
	void (*funcFree)(IService*) = (void(*)(IService*))m_LibLoader.GetFunction(lib, "ReleaseService");

	// don't go any further if the dll can't load AND unload his services
	if( funcLoad == nullptr || funcFree == nullptr )
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Kernel: Loading functions failed." );
		return nullptr;
	}

	IService *pServ = funcLoad(sService);
	if( pServ == nullptr )
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Kernel: Loading service \"%s\" failed.", sService );
		return nullptr;
	}

	if(!pServ->Start())
	{
		CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Kernel: Starting Service failed" );
		// free service using dll
		funcFree(pServ);
		return nullptr;
	}
	
	ServiceData sd;
	sd.bCanKill = false;
	sd.LibId = lib;
	sd.pService = pServ;
	sd.iPriority = iPrior;

	//keep the order of priorities straight
	std::list<ServiceData>::iterator it( m_pServiceList.begin() );
	for( ; it != m_pServiceList.end(); ++it)
		if( (*it).iPriority > sd.iPriority )
			break;

	m_pServiceList.insert(it, sd);
	return pServ;
}
/************************************/
/*! Marks a service to be removed, the service
 *    will be deleted next loop
 * @param [in] s	A pointer to the service to remove
 */
void CKernel::RemoveService(IService* s)
{
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Kernel: Removing Service" );
	
	std::list<ServiceData>::iterator it( std::find(m_pServiceList.begin(), m_pServiceList.end(), s) );
	if( it != m_pServiceList.end() )
		it->bCanKill = true;

}
/************************************/

/************************************/
/*! Mark all services to be removed
 * @remark This will also end the application
 */
void CKernel::KillAllServices()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Killing All Services" );
	for(std::list<ServiceData>::iterator it( m_pServiceList.begin() ); it != m_pServiceList.end(); ++it)
		it->bCanKill = true;
}
/************************************/

/************************************/
/*! Send a message to the services
 *    (including the service who sends it)
 * @param [in] msg Pointer to SMsg object
 */
void CKernel::SendMessage(SMsg* msg)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Kernel: Message Broadcast: %d", msg->id );
	if( msg->id == SM_QUIT )
		KillAllServices();

	for(std::list<ServiceData>::iterator it( m_pServiceList.begin() ); it != m_pServiceList.end(); ++it)
		(*it).pService->MsgProc(msg);
}
/************************************/




