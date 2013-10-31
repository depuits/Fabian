#include "CServiceMessageLoop.h"

#include "CKernel.h"
#include <SDL.h>

CServiceMessageLoop::CServiceMessageLoop(int priorety)
	:IService(priorety)
{
}
CServiceMessageLoop::~CServiceMessageLoop()
{
}
	
bool CServiceMessageLoop::Start()
{
	return true;
}
void CServiceMessageLoop::Update()
{
	SDL_Event e;
	while ( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit 
		if( e.type == SDL_QUIT )
		{	
			SMsg msg(SM_QUIT);
			CKernel::Get()->SendMessage( &msg );
		}
	}
}
void CServiceMessageLoop::Stop()
{
}

