//commented not needed parts out because of compile errors
#include "SOIL/SOIL.h"
#include <DataStructures.h>
#include <vector>
#include <Fabian.h>

#ifdef WIN32
	#define DECLDIR __declspec(dllexport)
#else
	#define DECLDIR
#endif

extern "C"
{
	// Plugin factory function
	DECLDIR ImageData* LoadData(const char* sFile)
	{
		int w, h;
		ImageData *pID = new ImageData();

		pID->data = SOIL_load_image(sFile, &w, &h, 0, SOIL_LOAD_RGBA);
		pID->w = w;
		pID->h = h;

		if( pID->data == nullptr )
		{
            Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "SOIL loading error: '%s'\n", SOIL_last_result());
			delete pID;
			return nullptr;
		}

		return pID;
	}

	// Plugin cleanup function
	DECLDIR void ReleaseData (ImageData* pID)
	{
		//we allocated in the factory with new, delete the passed object
		SOIL_free_image_data( pID->data );
		delete pID;
	}
}

