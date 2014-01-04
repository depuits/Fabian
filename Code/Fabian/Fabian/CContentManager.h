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
	virtual IShader *LoadShader(const std::string&);
	virtual IMesh *LoadMesh(const std::string&);
	virtual IImage *LoadImage(const std::string&);
	//-------------------------------------

	//-------------------------------------
	// Checks weither or not the mesh or image has already been loaded.
	// p1 in - string, name of the object file (without extension)
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

#endif //FABIAN_CCONTENTMANAGER_H_
