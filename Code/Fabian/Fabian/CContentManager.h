#ifndef FABIAN_CCONTENTMANAGER_H_
#define FABIAN_CCONTENTMANAGER_H_

#include "FabianDef.h"
#include <string>
#include <map>

// --forward declarations--
class IRenderer;

class IMesh;
class IImage;
// ------------------------

//******************************************
// Class CMeshOpenGL:
// this class is an OpenGL implementation of 
// the IMesh interface
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
	// Loads in a mesh from a file and returns it 
	// p1 in - string, name of the mesh file
	// rv - pointer IMesh object and nullptr if failed
	virtual IMesh *LoadMesh(const std::string&);
	virtual IImage *LoadImage(const std::string&);
	//-------------------------------------
	
	//-------------------------------------
	// Checks weither or not the shader or mesh has already been loaded.
	// p1 in - string, name of the object file (without extension)
	// rv - bool, true if the object is already loaded
	bool IsMeshLoaded(const std::string&) const;
	bool IsImageLoaded(const std::string&) const;
	//-------------------------------------

private:

	IRenderer *m_pRenderer;
	std::map<std::string, IMesh*> m_mMeshMap;
	std::map<std::string, IImage*> m_mImageMap;


	DISALLOW_COPY_AND_ASSIGN(CContentManager);
};

#endif //FABIAN_CCONTENTMANAGER_H_
