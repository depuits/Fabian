#include "CContentManager.h"
#include "IRenderer.h"

#include "IMesh.h"

#include "CA3dReader.h"
#include "CLog.h"

#include "CLibrary.h"

typedef MeshData* (*LOAD_MESHDATA)(const char*, const char*);
typedef void (*RELEASE_MESHDATA)(MeshData*);

//-------------------------------------
// Constructor
CContentManager::CContentManager(IRenderer* pRend)
	:m_pRenderer(pRend)
{
}
//-------------------------------------
// Destructor
CContentManager::~CContentManager()
{
	for (std::map<std::string, IMesh*>::iterator it = m_mMeshMap.begin(); it != m_mMeshMap.end(); ++it)
		delete it->second;
	m_mMeshMap.clear();
}
//-------------------------------------
	
//-------------------------------------
// Loads in a mesh from a file and returns it 
// p1 in - string, name of the mesh file (without extension)
// p2 in - string, extension of the file
// rv - pointer IMesh object and nullptr if failed
IMesh *CContentManager::LoadMesh(const std::string& sName, const std::string& sExt)
{
	if ( !IsMeshLoaded(sName))
	{
		CLibrary lib;
		if( !lib.Load("FPM_A3DLoader.fpm") )
			return nullptr;
		LOAD_MESHDATA fLoadMD = (LOAD_MESHDATA)lib.GetFunction("LoadData"); // meshData Loading function
		RELEASE_MESHDATA fReleaseMD = (RELEASE_MESHDATA)lib.GetFunction("ReleaseData"); // meshData Release function

		if( fLoadMD == nullptr || fReleaseMD == nullptr )
			return nullptr;
		
		// load from dll
		MeshData *md = fLoadMD(sName.c_str(), sExt.c_str() );

		IMesh *pMesh = m_pRenderer->LoadMesh(md);
		// release dll data
		fReleaseMD(md);

		if( pMesh == nullptr )
			return nullptr;
		
		m_mMeshMap[sName] = pMesh;
	}

	return m_mMeshMap[sName];
}
//-------------------------------------

//-------------------------------------
// Checks weither or not the shader or mesh has already been loaded.
// p1 in - string, name of the object file (without extension)
// rv - bool, true if the object is already loaded
bool CContentManager::IsMeshLoaded(const std::string& sKey) const
{
	return  m_mMeshMap.find(sKey) != m_mMeshMap.end();
}
//-------------------------------------