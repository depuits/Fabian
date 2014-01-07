#ifndef FABIAN_CCONTENTMANAGER_H_
#define FABIAN_CCONTENTMANAGER_H_

#include "FabianDef.h"
#include <string>
#include <map>

// --forward declarations--
class IRenderer;

class IShader;
class IMesh;
class IImage;
// ------------------------

//******************************************
// Class CContentManager:
// the content manager is responsible for loading
// and unloading objects like meshes and textures.
// Unloading isn't implemented yet
//******************************************
class CContentManager
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
	// Loads in a mesh or texture from a file and returns it
	// p1 in - string, name of the file to load
	// rv - pointer IMesh or IImage object and nullptr if failed
	// !!! - for loading shaders you shouldn't add the extension
	virtual IShader *LoadShader(const std::string&);
	virtual IMesh *LoadMesh(const std::string&);
	virtual IImage *LoadImage(const std::string&);
	//-------------------------------------
	// Loads in a mesh or texture from a file and returns it
	//    using a specifiv dll
	// p1 in - string, name of lib used to load
	// p2 in - string, name of the file to load
	// rv - pointer IMesh or IImage object and nullptr if failed
	virtual IMesh *LoadMeshUsing(const std::string&, const std::string&);
	virtual IImage *LoadImageUsing(const std::string&, const std::string&);
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


