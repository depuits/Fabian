#include "CServiceTimer.h"

#include <SDL.h>
#include "CLog.h"

//******************************************
// Class CServiceTimer:
// service responsable for sending out the dTime
//******************************************

//-------------------------------------
// Constructor
// p1 in - int, the priorety of the service
//            ( the lower the higher the priorety )
CServiceTimer::CServiceTimer(int priorety)
	:IService(priorety)

	,m_ulLastFrameIndex(0)
	,m_ulThisFrameIndex(0)

	,m_dTimer(0)
{
}
//-------------------------------------
// Destructor
CServiceTimer::~CServiceTimer()
{
}
//-------------------------------------

//-------------------------------------
// Called when the service is registered in the kernel
// rv - return true on succes,
//         when false is returned then the service gets deleted
bool CServiceTimer::Start()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Time Service: Starting" );
	m_ulThisFrameIndex = SDL_GetTicks();
	m_ulLastFrameIndex = m_ulThisFrameIndex;

	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Time Service: Started" );
	return true;
}
//-------------------------------------
// Called every time the service has to update
void CServiceTimer::Update()
{
	// fix ratio update
	double interval = 1.0 / 60.0;

	do
	{
		m_ulLastFrameIndex = m_ulThisFrameIndex;
		m_ulThisFrameIndex = SDL_GetTicks();
		float dt = ((float)(m_ulThisFrameIndex - m_ulLastFrameIndex)) / 1000.0f;
		m_dTimer += dt;
	}
	while ( m_dTimer < interval );

	m_dTimer -= interval ;
	float dt = (float)interval;

	// lose update (unlimited)
	/*m_ulLastFrameIndex = m_ulThisFrameIndex;
	m_ulThisFrameIndex = SDL_GetTicks();
	float dt = ((float)(m_ulThisFrameIndex - m_ulLastFrameIndex)) / 1000.0f;*/

	// dt callback
	for (TimerCallbackFunc func : m_vCallbackFuncs)
	{
		func(dt);
	}
}
//-------------------------------------
// Called when the service will be deleted
void CServiceTimer::Stop()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Time Service: Stopping" );
}
//-------------------------------------

//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CServiceTimer::MsgProc(SMsg* sm)
{
	if( sm->id == SM_TIMER )
	{
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Time Service: Registering Time Callback" );
		TimerCallbackFunc f = SMsg::Cast<SMsgTimer*>(sm)->pCallbackFunc;
		if( f != nullptr)
			m_vCallbackFuncs.push_back(f);
	}
}
//-------------------------------------


