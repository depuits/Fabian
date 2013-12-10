#include "CServiceMessageLoop.h"

#include "CKernel.h"
#include <SDL.h>

#include "CLog.h"

//******************************************
// Class CServiceMessageLoop:
// service responsable for handling message from the system
// this is needed for moving and closing the window
//******************************************

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service 
//            ( the lower the higher the priorety )
CServiceMessageLoop::CServiceMessageLoop(int priorety)
	:IService(priorety)
{
}
//-------------------------------------
// Destructor
CServiceMessageLoop::~CServiceMessageLoop()
{
}
//-------------------------------------
	
//-------------------------------------
// Called when the service is registered in the kernel
// rv - return true on succes, 
//         when false is returned then the service gets deleted	
bool CServiceMessageLoop::Start()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Message Service: Started" );
	return true;
}
//-------------------------------------
// Called every time the service has to update
void CServiceMessageLoop::Update()
{
	SDL_Event e;
	while ( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit 
		if( e.type == SDL_QUIT )
		{	
			SMsg msg(SM_QUIT);
			CKernel::Get().SendMessage( &msg );
		}
	}
}
//-------------------------------------
// Called when the service will be deleted
void CServiceMessageLoop::Stop()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Message Service: Stopping" );
}
//-------------------------------------

