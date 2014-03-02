#include "CContentManager.h"
#include "IRenderer.h"

#include "CLibrary.h"
#include "Fabian.h"

FDISABLE_WARNING_START(4505)
#include <dirent.h>
//FDISABLE_WARNING_END(4505) // don't end it because of the way the warning is generated

//******************************************
// Class CContentManager:
// the content manager is responsible for loading
// and unloading objects like meshes and textures.
//******************************************

//-------------------------------------
// Constructor
CContentManager::CContentManager(IRenderer* pRend)
	:IContentManager()
	,m_pRenderer(pRend)
	,m_pLibraryLoader(nullptr)
{
}
//-------------------------------------
// Destructor
CContentManager::~CContentManager()
{
	if(m_pLibraryLoader != nullptr)
		delete m_pLibraryLoader;
}
//-------------------------------------

//-------------------------------------
// Enables loading and buffering of objects from the storage
//    to the memory.
// p1 in - string, path of where to load the plugins from
// rv - bool, returns false if nothing will be able to load
//               (in case no plugins we're found).
bool CContentManager::StartLoading(const char* path)
{
	if( m_pLibraryLoader != nullptr )
	{
        Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "Content: Starting loading without calling EndLoading.");
		return true;
	}

	// fill in LOAD_DATA en RELEASE_DATA vecors
    std::string sExt =
#if defined WIN32 /*windows*/
        ".dll";
#elif defined UNIX /*unix*/
        ".so";
#else
#error PLATFORM NOT IMPLENTED
#endif

    Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Searching libs to load");
    DIR *dir;
    struct dirent *ent;
    if ( (dir = opendir (path)) != NULL )
    {
		// Create library loader
		m_pLibraryLoader = new CLibraryLoader();
        // loop all the files and directories within directory
        while ((ent = readdir (dir)) != NULL)
        {
            if( ent->d_type == DT_REG ) // if entry is a regular file
            {
                std::string fname(ent->d_name);
                if( fname.find(sExt, (fname.length() - sExt.length()) ) != std::string::npos )
                {
                    //printf("%s\n", fname.c_str());

					int id = m_pLibraryLoader->LoadLib( ("plugins/" + fname).c_str() );
					if( id == -1 )
					{
						Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of plugin failed: \"%s\"", fname.c_str());
						continue;
				    }
					LOAD_DATA fLoadData = (LOAD_DATA)m_pLibraryLoader->GetFunction(id, "LoadData"); // Data Loading function
					RELEASE_DATA fReleaseData = (RELEASE_DATA)m_pLibraryLoader->GetFunction(id, "ReleaseData"); // Data Release function

					if( fLoadData == nullptr || fReleaseData == nullptr )
					{
						Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of LOADDATA(%d) or RELEASEDATA(%d) in \"%s\" failed.", fLoadData, fReleaseData, fname.c_str());
						continue;
					}
					
					m_vpLoadData.push_back(fLoadData);
					m_vpReleaseData.push_back(fReleaseData);
                }
            }
        }
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Failed to open plugin directory");
        return false;
    }

	if( m_vpLoadData.size() <= 0 )
	{
        Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Failed to start loading, no suitable plugins found in folder.");
		delete m_pLibraryLoader;
		return false;
	}

	return true;
}
//-------------------------------------
// Ends the loading of objects and unloads the plugins.
//    You can still "load" objects wich are buffered or already loaded in memory
void CContentManager::EndLoading()
{
	if(m_pLibraryLoader != nullptr)
	{
		m_vpLoadData.clear();
		m_vpReleaseData.clear();

		delete m_pLibraryLoader;
	}
}
//-------------------------------------

//-------------------------------------
// Loads in a mesh or texture from a file and keeps it loaded
// p1 in - string, name of the file to load
// rv - bool, true if the loading succeeded
// !!! - for loading shaders you shouldn't add the extension
bool CContentManager::BufferShader(const char* sFile)
{
	if ( !IsShaderLoaded(sFile))
	{
		Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading new Shader: \"%s\"", sFile);

		IShader *pShader = m_pRenderer->LoadShader(sFile);
		if( pShader == nullptr )
		{
			Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading shader failed");
			return false;
		}
		m_mShaderMap[sFile] = pShader;
	}
	return true;
}
bool CContentManager::BufferMesh(const char* sFile)
{
	if( m_pLibraryLoader == nullptr )
		return false;
	
	if ( !IsMeshLoaded(sFile))
	{
		for( unsigned i(0); i < m_vpLoadData.size(); ++i )
		{
			MeshData *md = static_cast<MeshData*>( m_vpLoadData[i](sFile) );
			if( md == nullptr ) // dll failed to load
			{
				Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "Content: Loading mesh data failed");
				continue;
			}

			Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loaded MeshData ( v: %d - i: %d )", md->vCount / 8 /* divided by 8 becaus the vcount is x,y,z,nx,ny,nz,u,v*/, md->iCount);
			IMesh *pMesh = m_pRenderer->LoadMesh(md);
			// release dll data
			m_vpReleaseData[i](md);

			if( pMesh == nullptr )
			{
				Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading mesh failed");
				return false;
			}

			m_mMeshMap[sFile] = pMesh;
			return true;
		}
		return false;
	}
	return true;
}
bool CContentManager::BufferImage(const char* sFile)
{
	if( m_pLibraryLoader == nullptr )
		return false;

	if ( !IsImageLoaded(sFile))
	{
		CLibrary lib;
		if( !lib.Load(sLib.c_str()) )
		{
            Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of plugin failed: \"%s\"", sLib.c_str());
			return nullptr;
        }
		LOAD_DATA fLoadID = (LOAD_DATA)lib.GetFunction("LoadData"); // meshData Loading function
		RELEASE_DATA fReleaseID = (RELEASE_DATA)lib.GetFunction("ReleaseData"); // meshData Release function

		if( fLoadID == nullptr || fReleaseID == nullptr )
		{
            Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of LOADDATA(%d) or RELEASEDATA(%d) in \"%s\" failed.", fLoadID, fReleaseID, sLib.c_str());
			return nullptr;
        }

		// load from dll
		ImageData *id = static_cast<ImageData*>(fLoadID(sFile.c_str()));

		if( id == nullptr ) // dll failed to load
		{
			Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "Content: Loading texture data failed");
            return nullptr;
		}

        Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loaded ImageData ( w: %d - h: %d )", id->w, id->h);
        IImage *pImage = m_pRenderer->LoadImage(id);
        // release dll data
        fReleaseID(id);

        if( pImage == nullptr )
        {
            Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading texture failed");
            return nullptr;
        }

        m_mImageMap[sFile] = pImage;
	}
	return true;
}
//-------------------------------------
// Loads in a mesh or texture from a file and returns it
// p1 in - string, name of the file to load
// rv - pointer IMesh or IImage object and nullptr if failed
IShader *CContentManager::LoadShader(const char* sFile)
{
	if ( !IsShaderLoaded(sFile))
		if( !BufferShader(sFile) )
			return nullptr;

	return m_mShaderMap[sFile];
}
IMesh *CContentManager::LoadMesh(const char* sFile)
{
	if ( !IsMeshLoaded(sFile))
		if( !BufferMesh(sFile) )
			return nullptr;

	return m_mMeshMap[sFile];
}
#undef LoadImage
IImage *CContentManager::LoadImage(const char* sFile)
{
	if ( !IsImageLoaded(sFile))
		if( !BufferImage(sFile) )
			return nullptr;

    return m_mImageMap[sFile];
}
//-------------------------------------
IImage *CContentManager::LoadImageUsing(const std::string& sLib, const std::string& sFile)
{
	Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loading Texture (\"%s\") using \"%s\"", sFile.c_str(), sLib.c_str());
	if ( !IsImageLoaded(sFile))
	{
		CLibrary lib;
		if( !lib.Load(sLib.c_str()) )
		{
            Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of plugin failed: \"%s\"", sLib.c_str());
			return nullptr;
        }
		LOAD_DATA fLoadID = (LOAD_DATA)lib.GetFunction("LoadData"); // meshData Loading function
		RELEASE_DATA fReleaseID = (RELEASE_DATA)lib.GetFunction("ReleaseData"); // meshData Release function

		if( fLoadID == nullptr || fReleaseID == nullptr )
		{
            Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading of LOADDATA(%d) or RELEASEDATA(%d) in \"%s\" failed.", fLoadID, fReleaseID, sLib.c_str());
			return nullptr;
        }

		// load from dll
		ImageData *id = static_cast<ImageData*>(fLoadID(sFile.c_str()));

		if( id == nullptr ) // dll failed to load
		{
			Fab_LogWrite(FLOG_LVL_WARNING, FLOG_ID_APP, "Content: Loading texture data failed");
            return nullptr;
		}

        Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_APP, "Content: Loaded ImageData ( w: %d - h: %d )", id->w, id->h);
        IImage *pImage = m_pRenderer->LoadImage(id);
        // release dll data
        fReleaseID(id);

        if( pImage == nullptr )
        {
            Fab_LogWrite(FLOG_LVL_ERROR, FLOG_ID_APP, "Content: Loading texture failed");
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


