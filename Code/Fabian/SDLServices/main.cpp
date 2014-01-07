#include <IService.h>
#include <string>

#include "CServiceTimer.h"


extern "C"
{
	// Plugin factory function
	DECLDIR IService* LoadService(const char* sServ)
	{
		std::string name(sServ);
		if(name == "Timer")
		{
			IService* pServ = new CServiceTimer(110);
			return pServ;
		}
		return nullptr;
	}

	// Plugin cleanup function
	DECLDIR void ReleaseService (IService*)
	{
	}
}

