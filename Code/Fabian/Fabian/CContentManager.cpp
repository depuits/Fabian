#include "CContentManager.h"
#include "IRenderer.h"

#include "IMesh.h"
#include "IImage.h"
#include "CLibrary.h"
#include "CLog.h"

//******************************************
// Class CContentManager:
// the content manager is responsible for loading
// and unloading objects like meshes and textures.
//******************************************

typedef MeshData* (*LOAD_MESHDATA)(const char*);
typedef void (*RELEASE_MESHDATA)(MeshData*);

typedef ImageData* (*LOAD_IMAGEDATA)(const char*);
typedef void (*RELEASE_IMAGEDATA)(ImageData*);

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
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Unloading Meshes: %d", m_mMeshMap.size());
	for (std::map<std::string, IMesh*>::iterator it( m_mMeshMap.begin() ); it != m_mMeshMap.end(); ++it)
		delete it->second;
	m_mMeshMap.clear();

	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Unloading Textures: %d", m_mImageMap.size());
	for (std::map<std::string, IImage*>::iterator it( m_mImageMap.begin() ); it != m_mImageMap.end(); ++it)
		delete it->second;
	m_mImageMap.clear();
}
//-------------------------------------

//-------------------------------------
// Loads in a mesh or texture from a file and returns it
// p1 in - string, name of the file to load
// rv - pointer IMesh or IImage object and nullptr if failed
IMesh *CContentManager::LoadMesh(const std::string& sFile)
{
	if ( !IsMeshLoaded(sFile))
	{
        std::string sLib("plugins/FPM_OBJLoader");

#if defined WIN32 /*windows*/
        sLib += ".dll";
#elif defined UNIX /*unix*/
        sLib += ".so";
#else
#error PLATFORM NOT IMPLENTED
#endif

		CLibrary lib;
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading new mesh using \"%s\"", sLib.c_str());
		if( !lib.Load(sLib) )
		{
            CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of plugin failed: \"%s\"", sLib.c_str());
			return nullptr;
        }
		LOAD_MESHDATA fLoadMD = (LOAD_MESHDATA)lib.GetFunction("LoadData"); // meshData Loading function
		RELEASE_MESHDATA fReleaseMD = (RELEASE_MESHDATA)lib.GetFunction("ReleaseData"); // meshData Release function

		if( fLoadMD == nullptr || fReleaseMD == nullptr )
		{
            CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of LOADDATA(%d) or RELEASEDATA(%d) in \"%s\" failed.", fLoadMD, fReleaseMD, sLib.c_str());
			return nullptr;
        }

		// load from dll
		MeshData *md = fLoadMD(sFile.c_str());

		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loaded MeshData ( v: %d - i: %d )", md->vCount / 8 /* divided by 8 becaus the vcount is x,y,z,nx,ny,nz,u,v*/, md->iCount);
		IMesh *pMesh = m_pRenderer->LoadMesh(md);
		// release dll data
		fReleaseMD(md);

		if( pMesh == nullptr )
		{
			CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading mesh failed");
			return nullptr;
		}

		m_mMeshMap[sFile] = pMesh;
	}

	return m_mMeshMap[sFile];
}
IImage *CContentManager::LoadImage(const std::string& sFile)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading Texture: %s", sFile.c_str());
	if ( !IsImageLoaded(sFile))
	{
        std::string sLib("plugins/FPI_SOILLoader");

#if defined WIN32 /*windows*/
        sLib += ".dll";
#elif defined UNIX /*unix*/
        sLib += ".so";
#else
#error PLATFORM NOT IMPLENTED
#endif

		CLibrary lib;
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading new Texture using \"%s\"", sLib.c_str());
		if( !lib.Load(sLib) )
		{
            CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of plugin failed: \"%s\"", sLib.c_str());
			return nullptr;
        }
		LOAD_IMAGEDATA fLoadID = (LOAD_IMAGEDATA)lib.GetFunction("LoadData"); // meshData Loading function
		RELEASE_IMAGEDATA fReleaseID = (RELEASE_IMAGEDATA)lib.GetFunction("ReleaseData"); // meshData Release function

		if( fLoadID == nullptr || fReleaseID == nullptr )
		{
            CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of LOADDATA(%d) or RELEASEDATA(%d) in \"%s\" failed.", fLoadID, fReleaseID, sLib.c_str());
			return nullptr;
        }

		// load from dll
		ImageData *id = fLoadID(sFile.c_str());

		IImage *pImage = m_pRenderer->LoadImage(id);
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loaded ImageData ( w: %d - h: %d )", id->w, id->h);
		// release dll data
		fReleaseID(id);

		if( pImage == nullptr )
		{
			CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading texture failed");
			return nullptr;
		}

		m_mImageMap[sFile] = pImage;
	}

	return m_mImageMap[sFile];
}
//-------------------------------------

//-------------------------------------
// Checks weither or not the mesh or image has already been loaded.
// p1 in - string, name of the object file (without extension)
// rv - bool, true if the object is already loaded
bool CContentManager::IsMeshLoaded(const std::string& sKey) const
{
	return  m_mMeshMap.find(sKey) != m_mMeshMap.end();
}
bool CContentManager::IsImageLoaded(const std::string& sKey) const
{
	return  m_mImageMap.find(sKey) != m_mImageMap.end();
}
//-------------------------------------


