#include "CApplication.h"

#include <Fabian.h>
#include <iostream>
#include <string>

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
	    std::string sExt =
#if defined WIN32 /*windows*/
        ".dll";
#elif defined UNIX /*unix*/
        ".so";
#else
#error PLATFORM NOT IMPLENTED
#endif

	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "going to load: %s", std::string("SDLServices" + sExt).c_str() );

	//add null safety checks
	CLibrary pLib;
	pLib.Load( std::string("./SDLServices" + sExt).c_str() );
	IService*(*func)(const char*) = (IService*(*)(const char*))pLib.GetFunction("LoadService");

	IService* pServ = func("Timer");
	Fab_KernelAddService( pServ, 100 );

	pServ = func("Input");
	Fab_KernelAddService( pServ, 50 );

	pServ = func("Video");
	Fab_KernelAddService( pServ, 5000 );


	CLibrary pLibGame;
	if(argc > 1)
	{
		//pLibGame.Load( std::string("TestApp" + sExt).c_str() );
		pLibGame.Load( std::string(argv[1] + sExt).c_str() );
		func = (IService*(*)(const char*))pLibGame.GetFunction("LoadService");
		pServ = func("Game"); // graphic need to be initialized before the game because of opengl initialization
		Fab_KernelAddService( pServ, 500 );
	}
	else
	{
		//pLibGame.Load( std::string("TestApp" + sExt).c_str() );
		pLibGame.Load( std::string("Game" + sExt).c_str() );
		func = (IService*(*)(const char*))pLibGame.GetFunction("LoadService");
		pServ = func("Game"); // graphic need to be initialized before the game because of opengl initialization
		Fab_KernelAddService( pServ, 500 );

		//Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_USER, "No meaningfull dll was loaded please add some arguents");
		//return 0;
	}

	//main game loop
	int rv = Fab_KernelExecute();

	//clean up
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "----------------- Application Ended -----------------\n");

	return rv;
}
//-------------------------------------

