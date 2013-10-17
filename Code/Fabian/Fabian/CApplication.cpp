#include "CApplication.h"

#include "CKernel.h"
#include <iostream>

#include "CVideoUpdateService.h"

CApplication::CApplication()
	:m_pKernel(nullptr)

	,m_pVideoService(nullptr)
{
}
 CApplication::~CApplication()
 {
 }
	
 int CApplication::Run(int argc, char *argv[])
 {
	//initiate the log for the app

	//create kernel
	m_pKernel = new CKernel();

	//load and set potential settings
  
	//parse command-line arguments
	//skip the first argument, which is always the program name
	if(argc>1)
		for(int i=1;i<argc;i++)
			std::cout << argv[i] << "\n"; // for now just show them in output
  
	//set up the profiler output

	//add services to use
	m_pVideoService = new CVideoUpdateService(10000);
	m_pKernel->AddService(m_pVideoService);

	//main game loop
	int rv = m_pKernel->Execute();
  
	//clean up
	delete m_pKernel;

	delete m_pVideoService;

	return rv;
 }

