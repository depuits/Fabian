//#include <SDL.h>
#include "CApplication.h"

// this is application dependent
int main(int argc, char *argv[])
{
	// create a new app
	CApplication *pApp = new CApplication();
	// run the app
	int rv = pApp->Run(argc, argv);
	// remove the app
	delete pApp;

	return rv;
}
