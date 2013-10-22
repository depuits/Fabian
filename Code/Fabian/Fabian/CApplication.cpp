#include "CApplication.h"

#include "CKernel.h"
#include <iostream>

#include "CServiceVideoUpdate.h"
#include "CServiceMessageLoop.h"
#include "CServiceTimer.h"

CApplication::CApplication()
	:m_pServiceVideo(nullptr)
	,m_pServiceMsgLoop(nullptr)
	,m_pServiceTimer(nullptr)
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
	m_pServiceMsgLoop = new CServiceMessageLoop(100);
	pKernel->AddService(m_pServiceMsgLoop);
	m_pServiceTimer = new CServiceTimer(110);
	pKernel->AddService(m_pServiceTimer);
	m_pServiceVideo = new CServiceVideoUpdate(10000);
	pKernel->AddService(m_pServiceVideo);

	//main game loop
	int rv = pKernel->Execute();
  
	//clean up
	delete pKernel;

	delete m_pServiceVideo;
	delete m_pServiceMsgLoop;
	delete m_pServiceTimer;

	return rv;
 }

