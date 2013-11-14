#include "CServiceTimer.h"

#include "CKernel.h"
#include <SDL.h>

//******************************************
// Class CServiceTimer:
// service responsable for sending out the dTime
//******************************************

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service 
//            ( the lower the higher the priorety )
CServiceTimer::CServiceTimer(int priorety)
	:IService(priorety)
	
	,m_ulLastFrameIndex(0)
	,m_ulThisFrameIndex(0)
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
	m_ulThisFrameIndex = SDL_GetTicks();
	m_ulLastFrameIndex = m_ulThisFrameIndex;

	return true;
}
//-------------------------------------
// Called every time the service has to update
void CServiceTimer::Update()
{
	m_ulLastFrameIndex = m_ulThisFrameIndex;
	m_ulThisFrameIndex = SDL_GetTicks();
	float dt = ((float)(m_ulThisFrameIndex - m_ulLastFrameIndex)) / 1000.0f;

	SMsgTimerDT msg(dt);
	CKernel::Get()->SendMessage(&msg);
}
//-------------------------------------
// Called when the service will be deleted
void CServiceTimer::Stop()
{
}
//-------------------------------------

