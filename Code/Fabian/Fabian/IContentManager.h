#ifndef FABIAN_ICONTENTMANAGER_H_
#define FABIAN_ICONTENTMANAGER_H_

#include "FabianDef.h"

// --forward declarations--
class IShader;
class IMesh;
class IImage;
// ------------------------

////////////////////////////////////////////
//! Interface IContentManager: 
//! the content manager is responsible for loading 
//! and unloading objects like meshes and textures.
////////////////////////////////////////////
class IContentManager
{
public:
	/************************************/
	/*! Constructor */
	IContentManager() { }
	/************************************/
	/*! Destructor */
	virtual ~IContentManager() { }
	/************************************/
	
	/************************************/
	/*! Enables loading and buffering of objects from the storage
	 *    to the memory.
	 * @param [in] path - Path of where to load the plugins from
	 * @return False if nothing will be able to load
	 *               (in case no plugins we're found).
	 */
	virtual bool StartLoading(const char* path = "plugins") = 0;
	/************************************/
	/*! Ends the loading of objects and unloads the plugins.
	 * @remark You can still "load" objects wich are buffered or already loaded in memory
	 */
	virtual void EndLoading() = 0;
	/************************************/

	/************************************/
	/// @{
	/*! Loads in a mesh or texture from a file and keeps it loaded
	 * @param [in] sFile - Name of the file to load
	 * @return True if the loading succeeded
	 * @warning For loading shaders you shouldn't add the extension
	 */
	virtual bool BufferShader(const char* sFile) = 0;
	virtual bool BufferMesh(const char* sFile) = 0;
	virtual bool BufferImage(const char* sFile) = 0;
	/// @}
	/************************************/
	/// @{
	/*! Loads in a mesh or texture from a file and returns it
	 * @param [in] sFile - Name of the file to load
	 * @return Pointer IMesh, IImage or IShader object and nullptr if failed
	 * @remark For loading shaders you shouldn't add the extension
	 */
	virtual IShader *LoadShader(const char* sFile) = 0;
	virtual IMesh *LoadMesh(const char* sFile) = 0;
	virtual IImage *LoadImage(const char* sFile) = 0;
	/// @}
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(IContentManager);
};

/////////////////////////////////////////////////////////////////////////

// Extern "C" functions that each plugin must implement in order to be recognized as a plugin by us.
// Data* equals to MeshData* for meshes and ImageData* for textures	


/************************************/
// Plugin data loading function
// p1 in - filename to load
// rv - return a pointer to a filled in data structure
// -> needs to be implemted
//extern "C" Data* LoadData (const char*);
/************************************/
// Plugin data cleanup function
// p1 in - pointer to the created data structures which needs to be cleaned up
// -> needs to be implemted
//extern "C" void ReleaseData (Data*);
/************************************/
	 
/************************************/
// !!! Not needed yet or implemented
// The plugin version function
// rv - return the plugin version
// -> use this implementation
//extern "C" int Version() { return FVERSION_PLUGIN_DATA; }
/************************************/


#endif //FABIAN_ICONTENTMANAGER_H_


