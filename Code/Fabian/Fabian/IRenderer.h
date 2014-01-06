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

//******************************************
// Interface IRenderer:
// interface used for basic rendering methods
// and loading shaders and meshes.
// !!! this still need lots off extension 
//        for more advanced things
//******************************************
class IRenderer
{
public:
	//-------------------------------------
	// Constructor
	IRenderer() { };
	//-------------------------------------
	// Destructor
	virtual ~IRenderer() { };
	//-------------------------------------

	//-------------------------------------
	// Switches the window to fullscreen and back
	// rv - bool, true if in fullscreen
	virtual bool SwitchFullScreen() = 0;
	//-------------------------------------
	// Sets the window to fullscreen or windowed
	// p1 in - bool, goes to fullscreen if true
	virtual void SetFullScreen(bool) = 0;
	//-------------------------------------

	//-------------------------------------
	// Enable or disable VSync
	// p1 in - bool, sets VSync on if true
	virtual void SetVSync(bool) = 0;
	//-------------------------------------

	//-------------------------------------
	// Sets the screen resolution of this game
	// p1 in - int, screen width
	// p2 in - int, screen height
	virtual void SetScreenResolution(int, int) = 0;
	//-------------------------------------

	//-------------------------------------
	// Clears the backbuffers to 1 color
	// p1 in - float, R value
	// p2 in - float, G value
	// p3 in - float, B value
	// p4 in - float, A value
	virtual void Clear(float, float, float, float) = 0;
	//-------------------------------------
	
	//-------------------------------------
	// Set The active drawing camera for the comming frame
	// p1 in - pointer to the camera to use
	virtual void SetActiveCamera(ICamera*) = 0;
	//-------------------------------------

	//-------------------------------------
	// Loads in a shader from a file and returns it
	// p1 in - string, name of the shader file (without extension)
	// rv - pointer IShader object and nullptr if failed
	virtual IShader *LoadShader(const std::string&) = 0;
	//-------------------------------------
	// Loads in a mesh from a file and returns it
	// p1 in - pointer to the meshdata for the mesh
	// rv - pointer IMesh object and nullptr if failed
	virtual IMesh *LoadMesh(MeshData*) = 0;
	//-------------------------------------
	// Loads in a image from a file and returns it
	// p1 in - pointer to the imagedata for the mesh
	// rv - pointer IImage object and nullptr if failed
	virtual IImage *LoadImage(ImageData*) = 0;
	//-------------------------------------

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(IRenderer);
};

#endif //FABIAN_IRENDERER_H_
