#include "CApplication.h"

#include "CKernel.h"
#include <iostream>

#include "CServiceVideoUpdate.h"
#include "CServiceMessageLoop.h"
#include "CServiceTimer.h"
#include "CServiceGame.h"
#include "CServiceInput.h"

#include "CLog.h"
#include "CLoggerToFiles.h"

//******************************************
// Class CApplication:
// the entry point where the OO starts and where
//    the services get added to the kernel
//******************************************

//-------------------------------------
// Constructor
CApplication::CApplication()
{
}
//-------------------------------------
// Destructor
CApplication::~CApplication()
{
}
//-------------------------------------
	
//-------------------------------------
// Called when the service is registered in the kernel
// p1 in - int, number of arguments past
// p2 in - char*, array of the past arguments
// rv - return value of te app	
int CApplication::Run(int argc, char *argv[])
{
	//initiate the log for the app
	CLoggerToFiles* pLogger = new CLoggerToFiles();
	pLogger->Init();
	CLog::Get().AssignLogger(pLogger);
	
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "----------------- Application Starting -----------------");

	//create kernel
	CKernel *pKernel = &CKernel::Get();

	//load and set potential settings
  
	//parse command-line arguments
	//skip the first argument, which is always the program name
	if(argc > 1)
		for(int i(1); i < argc; ++i)
			std::cout << argv[i] << "\n"; // for now just show them in output
  
	//set up the profiler output

	//add services to use
	pKernel->AddService( new CServiceInput(50) ); // must be called before msg loop to copy the keyboard state
	pKernel->AddService( new CServiceMessageLoop(100) );
	pKernel->AddService( new CServiceTimer(110) );
	CServiceVideoUpdate *pServiceVideo = dynamic_cast<CServiceVideoUpdate*>( pKernel->AddService( new CServiceVideoUpdate(1000) ) );
	//pServiceVideo->SetScreenResolution(800, 600);
	pServiceVideo->SetWindowName("Dimo's Quest");

	pKernel->AddService( new CServiceGame(500) ); // graphic need to be initialized before the game because of opengl initialization

	//main game loop
	int rv = pKernel->Execute();
  
	//clean up
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "----------------- Application Ended -----------------\n");

	return rv;
}
//-------------------------------------

