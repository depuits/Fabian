#ifndef FABIAN_CCONTENTMANAGER_H_
#define FABIAN_CCONTENTMANAGER_H_

#include "IContentManager.h"
#include "CLibraryLoader.h"
#include <string>
#include <vector>
#include <map>

// --forward declarations--
class IRenderer;
// ------------------------

// ----type definitions----
typedef void* (*LOAD_DATA)(const char*);
typedef void (*RELEASE_DATA)(void*);
// ------------------------

//******************************************
// Class CContentManager:
// the content manager is responsible for loading
// and unloading objects like meshes and textures.
// Unloading isn't implemented yet
//******************************************
class CContentManager : public IContentManager
{
public:
	//-------------------------------------
	// Constructor
	CContentManager(IRenderer*);
	//-------------------------------------
	// Destructor
	virtual ~CContentManager();
	//-------------------------------------
	
	//-------------------------------------
	// Enables loading and buffering of objects from the storage
	//    to the memory.
	// p1 in - string, path of where to load the plugins from
	// rv - bool, returns false if nothing will be able to load
	//               (in case no plugins we're found).
	virtual bool StartLoading(const char*);
	//-------------------------------------
	// Ends the loading of objects and unloads the plugins.
	//    You can still "load" objects wich are buffered or already loaded in memory
	virtual void EndLoading();
	//-------------------------------------

	//-------------------------------------
	// Loads in a mesh or texture from a file and keeps it loaded
	// p1 in - string, name of the file to load
	// rv - bool, true if the loading succeeded
	// !!! - for loading shaders you shouldn't add the extension
	virtual bool BufferShader(const char*);
	virtual bool BufferMesh(const char*);
	virtual bool BufferImage(const char*);
	//-------------------------------------
	// Loads in a mesh or texture from a file and returns it
	// p1 in - string, name of the file to load
	// rv - pointer IMesh or IImage object and nullptr if failed
	// !!! - for loading shaders you shouldn't add the extension
	virtual IShader *LoadShader(const char*);
	virtual IMesh *LoadMesh(const char*);
	virtual IImage *LoadImage(const char*);
	//-------------------------------------

	//-------------------------------------
	// Checks weither or not the mesh or image has already been loaded.
	// p1 in - string, name of the object file
	// rv - bool, true if the object is already loaded
	bool IsShaderLoaded(const std::string&) const;
	bool IsMeshLoaded(const std::string&) const;
	bool IsImageLoaded(const std::string&) const;
	//-------------------------------------

private:
	IRenderer *m_pRenderer;

	CLibraryLoader *m_pLibraryLoader;
	std::vector<LOAD_DATA> m_vpLoadData;
	std::vector<RELEASE_DATA> m_vpReleaseData;

	std::map<std::string, IShader*> m_mShaderMap;
	std::map<std::string, IMesh*> m_mMeshMap;
	std::map<std::string, IImage*> m_mImageMap;


	DISALLOW_COPY_AND_ASSIGN(CContentManager);
};

/////////////////////////////////////////////////////////////////////////

//Extern "C" functions that each plugin must implement in order to be recognized as a plugin by us.
// Data* equals to MeshData* for meshes and ImageData* for textures	


//-------------------------------------
// Plugin data loading function
// p1 in - filename to load
// rv - return a pointer to a filled in data structure
// -> needs to be implemted
//extern "C" Data* LoadData (const char*);
//-------------------------------------
// Plugin data cleanup function
// p1 in - pointer to the created data structures which needs to be cleaned up
// -> needs to be implemted
//extern "C" void ReleaseData (Data*);
//-------------------------------------
	 
//-------------------------------------
// !!! Not needed yet or implemented
// The plugin version function
// rv - return the plugin version
// -> use this implementation
//extern "C" int Version() { return FVERSION_PLUGIN_DATA; }
//-------------------------------------


#endif //FABIAN_CCONTENTMANAGER_H_


