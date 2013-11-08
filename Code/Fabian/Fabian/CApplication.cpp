#include "CApplication.h"

#include "CKernel.h"
#include <iostream>

#include "CServiceVideoUpdate.h"
#include "CServiceMessageLoop.h"
#include "CServiceTimer.h"
#include "CServiceGame.h"
#include "CServiceInput.h"

CApplication::CApplication()
{
}
 CApplication::~CApplication()
 {
 }
	
 int CApplication::Run(int argc, char *argv[])
 {
	//initiate the log for the app

	//create kernel
	CKernel *pKernel = CKernel::Get();

	//load and set potential settings
  
	//parse command-line arguments
	//skip the first argument, which is always the program name
	if(argc>1)
		for(int i=1;i<argc;i++)
			std::cout << argv[i] << "\n"; // for now just show them in output
  
	//set up the profiler output

	//add services to use
	pKernel->AddService( new CServiceInput(50) ); // must be called before msg loop to copy the keyboard state
	pKernel->AddService( new CServiceMessageLoop(100) );
	pKernel->AddService( new CServiceTimer(110) );
	CServiceVideoUpdate *pServiceVideo = new CServiceVideoUpdate(10000);
	//pServiceVideo->SetScreenResolution(800, 600);
	pKernel->AddService( pServiceVideo );
	pServiceVideo->SetWindowName("Test");

	pKernel->AddService( new CServiceGame(500) ); // graphic nee to be initialized before the game because of opengl initialization

	//main game loop
	int rv = pKernel->Execute();
  
	//clean up
	delete pKernel;

	return rv;
 }

