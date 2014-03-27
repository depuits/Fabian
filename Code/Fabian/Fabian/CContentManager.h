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

////////////////////////////////////////////
//! Class CContentManager: 
//! the content manager is responsible for loading 
//! and unloading objects like meshes and textures. 
//! @remark Manual unloading isn't implemented yet
//******************************************
class CContentManager : public IContentManager
{
public:
	/************************************/
	/*! Constructor 
	 * @param [in] pRend - IRenderer used for loading 
	 *                        the content into the graphics engine
	 */
	CContentManager(IRenderer* pRend);
	/************************************/
	/*! Destructor */
	virtual ~CContentManager();
	/************************************/
	
	/************************************/
	/*! Enables loading and buffering of objects from the storage
	 *    to the memory.
	 * @param [in] path - Path of where to load the plugins from
	 * @return False if nothing will be able to load
	 *               (in case no plugins we're found).
	 */
	virtual bool StartLoading(const char*  path);
	/************************************/
	/*! Ends the loading of objects and unloads the plugins.
	 * @remark You can still "load" objects wich are buffered or already loaded in memory
	 */
	virtual void EndLoading();
	/************************************/

	/************************************/
	/// @{
	/*! Loads in a mesh or texture from a file and keeps it loaded
	 * @param [in] sFile - Name of the file to load
	 * @return True if the loading succeeded
	 * @warning For loading shaders you shouldn't add the extension
	 */
	virtual bool BufferShader(const char* sFile);
	virtual bool BufferMesh(const char* sFile);
	virtual bool BufferImage(const char* sFile);
	/// @}
	/************************************/
	/// @{
	/*! Loads in a mesh or texture from a file and returns it
	 * @param [in] sFile - Name of the file to load
	 * @return Pointer IMesh, IImage or IShader object and nullptr if failed
	 * @remark For loading shaders you shouldn't add the extension
	 */
	virtual IShader *LoadShader(const char* sFile);
	virtual IMesh *LoadMesh(const char* sFile);
	virtual IImage *LoadImage(const char* sFile);
	/// @}
	/************************************/

protected:
	/************************************/
	/// @{
	/*! Checks weither or not the mesh or image has already been loaded.
	 * @param [in] sKey - Name of the object file
	 * @return True if the object is already loaded
	 */
	bool IsShaderLoaded(const std::string& sKey) const;
	bool IsMeshLoaded(const std::string& sKey) const;
	bool IsImageLoaded(const std::string& sKey) const;
	/// @}
	/************************************/

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


