//#include <SDL.h>
#include "CApplication.h"

// this is application dependent
int main(int argc, char *argv[])
{
	// create a new app
	CApplication app;
	// run the app
	return app.Run(argc, argv);
}
