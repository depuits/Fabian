#include "CA3dReader.h"
#include <DataStructures.h>
#include <string>
#include <map>

extern "C"
{
	std::map<MeshData*, CA3dReader*> g_map;

	// Plugin factory function
	__declspec(dllexport) MeshData* LoadData(const char* sFile)
	{
		CA3dReader *reader = new CA3dReader();
		if( !reader->Read(sFile) )
		{
			delete reader;
			return false;
		}

		if( !reader->m_type[0] || !reader->m_type[1] )
		{
			delete reader;
			return false; // return because there where no normals or uvs
		}

		MeshData *pMD = new MeshData();
		pMD->iCount = reader->m_indices.size();
		pMD->iData = reader->m_indices.data();
		pMD->vCount = reader->m_vertices.size();
		pMD->vData = reader->m_vertices.data();

		// keep the pointer for whe you have to delete them
		g_map[pMD] = reader;


		return pMD;
	}

	// Plugin cleanup function
	__declspec(dllexport) void ReleaseData (MeshData* pMD)
	{
		//we allocated in the factory with new, delete the passed object
		if( g_map.find(pMD) != g_map.end() )
		{
			delete g_map[pMD];
			delete pMD;
		}		
	}
}

