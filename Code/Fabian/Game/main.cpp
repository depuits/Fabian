#include <IService.h>
#include <Fabian.h>
#include <string>

#include "CServiceGame.h"

#include <vector>

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
	DECLDIR IService* LoadService(const char* sServ, int prior)
	{
		std::string name(sServ);
		IService* pServ = nullptr;

		if(name == "Game")
			pServ = new CServiceGame(prior);

		if( pServ != nullptr )
			g_vpServices.push_back(pServ);

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
	}
}

