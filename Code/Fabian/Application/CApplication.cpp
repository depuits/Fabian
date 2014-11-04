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

	//load and set potential settings

	//parse command-line arguments
	//skip the first argument, which is always the program name
	if(argc > 1)
		for(int i(1); i < argc; ++i)
			std::cout << argv[i] << "\n"; // for now just show them in output

	//set up the profiler output

	//add services to use
	Fab_KernelAddService( "./SDLServices", "Timer", 100 );
	Fab_KernelAddService( "./SDLServices", "Input", 50 );
	Fab_KernelAddService( "./SDLServices", "Video", 5000 );

	if(argc > 1)
		Fab_KernelAddService( argv[1], "Game", 500 );
	else
	{
		Fab_KernelAddService( "Game", "Game", 600 );
		//Fab_KernelAddService( "ProjectB", "Project B", 500 );
		//Fab_KernelAddService( "TestApp", "Game", 600 );
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

