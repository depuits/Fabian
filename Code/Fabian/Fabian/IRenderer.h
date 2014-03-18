#ifndef FABIAN_IRENDERER_H_
#define FABIAN_IRENDERER_H_

#include "FabianDef.h"
#include "DataStructures.h"
#include <string>

// --forward declarations--
class IShader;
class IMesh;
class IImage;
class ICamera;
// ------------------------

////////////////////////////////////////////
//! Interface IRenderer: 
//! interface used for basic rendering methods 
//! and loading resources like shaders and meshes.
//! @remark this still need lots off extension 
//!        for more advanced things
////////////////////////////////////////////
class IRenderer
{
public:
	/************************************/
	/*! Constructor */
	IRenderer() { };
	/************************************/
	/*! Destructor */
	virtual ~IRenderer() { };
	/************************************/

	/************************************/
	/*! Switches the window to fullscreen and back
	 * @return True if in fullscreen
	 */
	virtual bool SwitchFullScreen() = 0;
	/************************************/
	/*! Sets the window to fullscreen or windowed
	 * @param [in] bFullscreen - Goes to fullscreen if true
	 */
	virtual void SetFullScreen(bool bFullscreen) = 0;
	/************************************/

	/************************************/
	/*! Enable or disable VSync
	 * @param [in] bVSync - Turns VSync on if true
	 */
	virtual void SetVSync(bool bVSync) = 0;
	/************************************/

	/************************************/
	/*! Sets the screen resolution of this game
	 * @param [in] w - Screen width
	 * @param [in] h - Screen height
	 */
	virtual void SetScreenResolution(int w, int h) = 0;
	/************************************/

	/************************************/
	/*! Clears the back buffers to 1 color
	 * @param [in] r - Red value
	 * @param [in] g - Green value
	 * @param [in] b - Blue value
	 * @param [in] a - Alpha value
	 */
	virtual void Clear(float r, float g, float b, float a) = 0;
	/************************************/
	
	/************************************/
	/*! Set The active drawing camera for the coming frame
	 * @param [in] pCam - Pointer to the camera to use
	 */
	virtual void SetActiveCamera(ICamera* pCam) = 0;
	/************************************/

	/************************************/
	/*! Loads in a IShader from a file and returns it
	 * @param [in] sName - Name of the shader file (without extension)
	 * @return Pointer to IShader object, nullptr if failed
	 */
	virtual IShader *LoadShader(const std::string& sName) = 0;
	/************************************/
	/*! Loads in a IMesh from a file and returns it
	 * @param [in] md - Pointer to the MeshData for the mesh
	 * @return Pointer to IMesh object, nullptr if failed
	 */
	virtual IMesh *LoadMesh(MeshData* md) = 0;
	/************************************/
	/*! Loads in a IImage from a file and returns it
	 * @param [in] id - Pointer to the ImageData for the mesh
	 * @return Pointer to IImage object, nullptr if failed
	 */
	virtual IImage *LoadImage(ImageData* id) = 0;
	/************************************/

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(IRenderer);
};

#endif //FABIAN_IRENDERER_H_
