#include "CContentManager.h"
#include "IRenderer.h"

#include "CLibrary.h"
#include "CLog.h"

#include <dirent.h>

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
	// do not delete resources here because they belong to the renderer
	/*CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Unloading Meshes: %d", m_mMeshMap.size());
	for (std::map<std::string, IMesh*>::iterator it( m_mMeshMap.begin() ); it != m_mMeshMap.end(); ++it)
		delete it->second;
	m_mMeshMap.clear();

	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Unloading Textures: %d", m_mImageMap.size());
	for (std::map<std::string, IImage*>::iterator it( m_mImageMap.begin() ); it != m_mImageMap.end(); ++it)
		delete it->second;
	m_mImageMap.clear();*/
}
//-------------------------------------

//-------------------------------------
// Loads in a mesh or texture from a file and returns it
// p1 in - string, name of the file to load
// rv - pointer IMesh or IImage object and nullptr if failed
IShader *CContentManager::LoadShader(const std::string& sFile)
{
	if ( !IsShaderLoaded(sFile))
	{
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading new Shader: \"%s\"", sFile.c_str());

		IShader *pShader = m_pRenderer->LoadShader(sFile);

		if( pShader == nullptr )
		{
			CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading shader failed");
			return nullptr;
		}

		m_mShaderMap[sFile] = pShader;
	}

	return m_mShaderMap[sFile];
}
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
		if( !lib.Load(sLib.c_str()) )
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
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading new mesh: \"%s\"", sFile.c_str());
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
    std::string sExt =
#if defined WIN32 /*windows*/
        ".dll";
#elif defined UNIX /*unix*/
        ".so";
#else
#error PLATFORM NOT IMPLENTED
#endif

    CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading Texture");
	if ( !IsImageLoaded(sFile))
	{
        CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Searching lib to load Texture");
        DIR *dir;
        struct dirent *ent;
        if ( (dir = opendir ("plugins")) != NULL )
        {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL)
            {
                if( ent->d_type == DT_REG ) // if entry is a regular file
                {
                    std::string fname(ent->d_name);
                    if( fname.find(sExt, (fname.length() - sExt.length()) ) != std::string::npos )
                    {
                        printf("%s\n", fname.c_str());
                        IImage *pImg = LoadImageUsing("plugins/" + fname, sFile);
                        if( pImg != nullptr )
                            return pImg;
                    }
                }
            }
            closedir (dir);
        }
        else
        {
            /* could not open directory */
            CLog::Get().Write(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Failed to open plugin directory");
            return nullptr;
        }
        CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Content: No plugin found to load image");
        return nullptr;
    }

    return m_mImageMap[sFile];
}
//-------------------------------------
// Loads in a mesh or texture from a file and returns it
// p1 in - string, name of lib used to load
// p2 in - string, name of the file to load
// rv - pointer IMesh or IImage object and nullptr if failed
IMesh *CContentManager::LoadMeshUsing(const std::string& sLib, const std::string& sFile)
{
    return nullptr;
}
IImage *CContentManager::LoadImageUsing(const std::string& sLib, const std::string& sFile)
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading Texture (\"%s\") using \"%s\"", sFile.c_str(), sLib.c_str());
	if ( !IsImageLoaded(sFile))
	{
		CLibrary lib;
		if( !lib.Load(sLib.c_str()) )
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
		CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading new Texture: \"%s\"", sFile.c_str());
		ImageData *id = fLoadID(sFile.c_str());

		if( id == nullptr ) // dll failed to load
		{
			CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Content: Loading texture failed");
            return nullptr;
		}

        CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loaded ImageData ( w: %d - h: %d )", id->w, id->h);
        IImage *pImage = m_pRenderer->LoadImage(id);
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
bool CContentManager::IsShaderLoaded(const std::string& sKey) const
{
	return  m_mShaderMap.find(sKey) != m_mShaderMap.end();
}
bool CContentManager::IsMeshLoaded(const std::string& sKey) const
{
	return  m_mMeshMap.find(sKey) != m_mMeshMap.end();
}
bool CContentManager::IsImageLoaded(const std::string& sKey) const
{
	return  m_mImageMap.find(sKey) != m_mImageMap.end();
}
//-------------------------------------


