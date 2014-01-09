#ifndef FABIAN_ICONTENTMANAGER_H_
#define FABIAN_ICONTENTMANAGER_H_

#include "FabianDef.h"

// --forward declarations--
class IShader;
class IMesh;
class IImage;
// ------------------------

//******************************************
// Interface IContentManager:
// the content manager is responsible for loading
// and unloading objects like meshes and textures.
// Unloading isn't implemented yet
//******************************************
class IContentManager
{
public:
	//-------------------------------------
	// Constructor
	IContentManager() { }
	//-------------------------------------
	// Destructor
	virtual ~IContentManager() { }
	//-------------------------------------

	//-------------------------------------
	// Loads in a mesh or texture from a file and returns it
	// p1 in - string, name of the file to load
	// rv - pointer IMesh or IImage object and nullptr if failed
	// !!! - for loading shaders you shouldn't add the extension
	virtual IShader *LoadShader(const char*) = 0;
	virtual IMesh *LoadMesh(const char*) = 0;
	virtual IImage *LoadImage(const char*) = 0;
	//-------------------------------------

private:
	DISALLOW_COPY_AND_ASSIGN(IContentManager);
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


#endif //FABIAN_ICONTENTMANAGER_H_


