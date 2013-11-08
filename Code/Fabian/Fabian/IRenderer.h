#ifndef FABIAN_IRENDERER_H_
#define FABIAN_IRENDERER_H_

#include "FabianDef.h"
#include <string>

class IShader;
class IMesh;

class IRenderer
{
public:
	IRenderer() { };
	virtual ~IRenderer() { };
	
	//fullscreen
	virtual void SwitchFullScreen() = 0;
	virtual void SetFullScreen(bool) = 0;
	//screen resolution
	virtual void SetScreenResolution(int, int) = 0;

	virtual void Clear(float, float, float, float) = 0;
	
	virtual IShader *LoadShader(const std::string&) = 0;
	virtual IMesh *LoadMesh(const std::string&, const std::string&) = 0;
	
protected:

private:
	DISALLOW_COPY_AND_ASSIGN(IRenderer);
};

#endif //FABIAN_IRENDERER_H_
