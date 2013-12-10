//commented not needed parts out because of compile errors
#include "SOIL/SOIL.h"
#include <DataStructures.h>
#include <vector>

extern "C"
{
	// Plugin factory function
	__declspec(dllexport) ImageData* LoadData(const char* sFile)
	{
		int w, h;
		ImageData *pID = new ImageData();

		pID->data = SOIL_load_image(sFile, &w, &h, 0, SOIL_LOAD_RGBA);
		pID->w = w;
		pID->h = h;

		return pID;
	}

	// Plugin cleanup function
	__declspec(dllexport) void ReleaseData (ImageData* pID)
	{
		//we allocated in the factory with new, delete the passed object
		SOIL_free_image_data( pID->data );
		delete pID;	
	}
}

