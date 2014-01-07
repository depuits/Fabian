#include "CApplication.h"

#include "CKernel.h"
#include <iostream>

#include "CServiceVideoUpdate.h"
#include "CServiceTimer.h"
#include "CServiceGame.h"
#include "CServiceInput.h"

#include "CLog.h"
#include "CLoggerMultiple.h"
#include "CLoggerToConsole.h"
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
	CLoggerMultiple* pLogger = new CLoggerMultiple();
	
	CLoggerToConsole* pLoggerConsole = new CLoggerToConsole(true);
	pLoggerConsole->Init();
	CLoggerToFiles* pLoggerFiles = new CLoggerToFiles(false);
	pLoggerFiles->Init();
	
	pLogger->AddLogger(pLoggerConsole);
	pLogger->AddLogger(pLoggerFiles);

	CLog::Get().AssignLogger(pLogger);
	
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "----------------- Application Starting -----------------");

	//test log
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "this is info");
	CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Oh no an error");
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Watch out I warned ya");
	CLog::Get().Write(FLOG_LVL_UNKNOWN, FLOG_ID_APP, "I have no clue what this is, could be anything");
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "some more info");

	//create kernel
	CKernel *pKernel = &CKernel::Get();

	//load and set potential settings
  
	//parse command-line arguments
	//skip the first argument, which is always the program name
	if(argc > 1)
		for(int i(1); i < argc; ++i)
			std::cout << argv[i] << "\n"; // for now just show them in output
  
	//set up the profiler output

	//temperary set up and exit sdl here
	// this will move with the sdl depended services to a DLL
	SDL_Init(0);

	//add services to use
	pKernel->AddService( new CServiceInput(50) );
	pKernel->AddService( new CServiceTimer(110) );
	CServiceVideoUpdate *pServiceVideo = dynamic_cast<CServiceVideoUpdate*>( pKernel->AddService( new CServiceVideoUpdate(1000) ) );
	//pServiceVideo->SetScreenResolution(800, 600);
	pServiceVideo->SetWindowName("Dimo's Quest");

	pKernel->AddService( new CServiceGame(500) ); // graphic need to be initialized before the game because of opengl initialization

	//main game loop
	int rv = pKernel->Execute();
  
	//clean up
	SDL_Quit();
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "----------------- Application Ended -----------------\n");

	return rv;
}
//-------------------------------------

