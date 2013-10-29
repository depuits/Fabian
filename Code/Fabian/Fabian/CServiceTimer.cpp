#include "CServiceTimer.h"

#include "CKernel.h"
#include <SDL.h>

CServiceTimer::CServiceTimer(int priorety)
	:IService(priorety)
	
	,m_ulLastFrameIndex(0)
	,m_ulThisFrameIndex(0)
{
}
CServiceTimer::~CServiceTimer()
{
}
	
bool CServiceTimer::Start()
{
	m_ulThisFrameIndex = SDL_GetTicks();
	m_ulLastFrameIndex = m_ulThisFrameIndex;

	return true;
}
void CServiceTimer::Update()
{
	m_ulLastFrameIndex = m_ulThisFrameIndex;
	m_ulThisFrameIndex = SDL_GetTicks();
	float dt = ((float)(m_ulThisFrameIndex - m_ulLastFrameIndex)) / 1000.0f;

	CKernel::Get()->SendMessage(SM_TIMER_DT);
}
void CServiceTimer::Stop()
{
}

