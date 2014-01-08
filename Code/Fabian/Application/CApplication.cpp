#include "CApplication.h"

#include <Fabian.h>
#include <iostream>

#include "CLibrary.hpp"

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
	ILogger* pLoggerMulti = Fab_LoggerCreateToMultiple();

	ILogger* pLogger = Fab_LoggerCreateToConsole(true);
	Fab_LoggerMultipleAddLogger(pLoggerMulti, pLogger);
	pLogger = Fab_LoggerCreateToFiles(false);
	Fab_LoggerMultipleAddLogger(pLoggerMulti, pLogger);

	Fab_LogAssignLogger(pLoggerMulti);

	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "----------------- Application Starting -----------------");

	//test log
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "this is info");
	Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Oh no an error");
	Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "Watch out I warned ya");
	Fab_LogWrite(FLOG_LVL_UNKNOWN, FLOG_ID_APP, "I have no clue what this is, could be anything");
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "some more info");

	//create kernel

	//load and set potential settings

	//parse command-line arguments
	//skip the first argument, which is always the program name
	if(argc > 1)
		for(int i(1); i < argc; ++i)
			std::cout << argv[i] << "\n"; // for now just show them in output

	//set up the profiler output
	/*
	//add services to use
	//pKernel->AddService( new CServiceInput(50) );
	//pKernel->AddService( new CServiceTimer(110) );
	CServiceVideoUpdate *pServiceVideo = dynamic_cast<CServiceVideoUpdate*>( Fab_KernelAddService( new CServiceVideoUpdate(1000) ) );
	//pServiceVideo->SetScreenResolution(800, 600);
	pServiceVideo->SetWindowName("Dimo's Quest");
	*/

	//add null safety checks
	CLibrary pLib;
	pLib.Load("SDLServices.so");
	IService*(*func)(const char*, int) = (IService*(*)(const char*, int))pLib.GetFunction("LoadService");

	IService* pServ = func("Timer", 100);
	Fab_KernelAddService( pServ );

	pServ = func("Input", 50);
	Fab_KernelAddService( pServ );

	pServ = func("Video", 5000);
	Fab_KernelAddService( pServ );

	CLibrary pLibGame;
	pLibGame.Load("Game.so");
	func = (IService*(*)(const char*, int))pLibGame.GetFunction("LoadService");
	pServ = func("Game", 500); // graphic need to be initialized before the game because of opengl initialization
	Fab_KernelAddService( pServ );

	//main game loop
	int rv = Fab_KernelExecute();

	//clean up
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "----------------- Application Ended -----------------\n");

	return rv;
}
//-------------------------------------

