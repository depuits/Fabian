#include <IService.h>
#include <Fabian.h>
#include <string>

#include "CServiceTimer.h"
#include "CServiceInput.h"
#include "CServiceVideoUpdate.h"

#include <SDL.h>
#include <vector>
#include <algorithm>

#ifdef DECLDIR
	#undef DECLDIR
#endif

#ifdef WIN32
	#define DECLDIR __declspec(dllexport)
#else
	#define DECLDIR
#endif

std::vector<IService*> g_vpServices;

extern "C"
{
	// Plugin factory function
	DECLDIR IService* LoadService(const char* sServ)
	{
		std::string name(sServ);
		IService* pServ = nullptr;

		if(name == "Timer")
			pServ = new CServiceTimer();
		else if(name == "Input")
			pServ = new CServiceInput();
		else if(name == "Video")
			pServ = new CServiceVideoUpdate();

		if( pServ != nullptr )
		{
			// if its the first service to create then init sdl
			if( g_vpServices.size() <= 0 )
				SDL_Init(0);

			g_vpServices.push_back(pServ);
		}

		return pServ;
	}

	// Plugin cleanup function
	DECLDIR void ReleaseService (IService *pServ)
	{
		std::vector<IService*>::iterator it( std::find(g_vpServices.begin(), g_vpServices.end(), pServ) );
		// not our service
		if( it == g_vpServices.end() )
		{
			Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "SDLServices : Tried to release service that wasn't created here" );
			return;
		}

		delete pServ;
		g_vpServices.erase(it);

		// if it was our last service then exit sdl
		if( g_vpServices.size() <= 0 )
			SDL_Quit();
	}
}

