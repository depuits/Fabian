#ifndef FABIAN_CRENDEREROPENGL_H_
#define FABIAN_CRENDEREROPENGL_H_

#include "IRenderer.h"
#include <map>

// --forward declarations--
class CServiceVideoUpdate;
// ------------------------

//******************************************
// Class CRendererOpenGL:
// IRenderer implementation for OpenGL.
//******************************************
class CRendererOpenGL : public IRenderer
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - pointer to the VideoUpdate service 
	//            which created this renderer
	CRendererOpenGL(CServiceVideoUpdate*);
	//-------------------------------------
	// Destructor
	virtual ~CRendererOpenGL();
	//-------------------------------------
	
	//-------------------------------------
	// Switches the window to fullscreen and back
	// rv - bool, true if in fullscreen
	virtual bool SwitchFullScreen();
	//-------------------------------------
	// Sets the window to fullscreen or windowed
	// p1 in - bool, goes to fullscreen if true
	virtual void SetFullScreen(bool);
	//-------------------------------------
	
	//-------------------------------------
	// Enable or disable VSync
	// p1 in - bool, sets VSync on if true
	virtual void SetVSync(bool);
	//-------------------------------------
	
	//-------------------------------------
	// Sets the screen resolution of this game
	// p1 in - int, screen width
	// p2 in - int, screen height
	virtual void SetScreenResolution(int, int);
	//-------------------------------------
	
	//-------------------------------------
	// Clears the backbuffers to 1 color
	// p1 in - float, R value
	// p2 in - float, G value
	// p3 in - float, B value
	// p4 in - float, A value
	virtual void Clear(float, float, float, float);
	//-------------------------------------
	
	//-------------------------------------
	// Loads in a shader from a file and returns it 
	// p1 in - string, name of the shader file (without extension)
	// rv - pointer IShader object and nullptr if failed
	virtual IShader *LoadShader(const std::string&);
	//-------------------------------------
	// Loads in a mesh from a file and returns it 
	// p1 in - string, name of the mesh file (without extension)
	// p2 in - string, extension of the file
	// rv - pointer IMesh object and nullptr if failed
	virtual IMesh *LoadMesh(const std::string&, const std::string& ext);
	//-------------------------------------
	
protected:
	CServiceVideoUpdate *m_pServiceParent;
	bool m_bFullScreen;
	
	//-------------------------------------
	// Checks weither or not the shader or mesh has already been loaded.
	// p1 in - string, name of the object file (without extension)
	// rv - bool, true if the object is already loaded
	bool IsShaderPresent(const std::string&) const;
	bool IsMeshPresent(const std::string&) const;
	//-------------------------------------

	std::map<std::string, IShader*> m_mShaderMap;
	std::map<std::string, IMesh*> m_mMeshMap;


private:
	DISALLOW_COPY_AND_ASSIGN(CRendererOpenGL);
};

#endif //FABIAN_CRENDEREROPENGL_H_
