#ifndef FABIAN_CRENDEREROPENGL_H_
#define FABIAN_CRENDEREROPENGL_H_

#include "IRenderer.h"
#include <map>

class CServiceVideoUpdate;

class CRendererOpenGL : public IRenderer
{
public:
	CRendererOpenGL(CServiceVideoUpdate*);
	virtual ~CRendererOpenGL();
	
	//fullscreen
	virtual void SwitchFullScreen();
	virtual void SetFullScreen(bool);
	//VSync
	virtual void SetVSync(bool);
	//screen resolution
	virtual void SetScreenResolution(int, int);

	virtual void Clear(float, float, float, float);
	
	virtual IShader *LoadShader(const std::string&);
	virtual IMesh *LoadMesh(const std::string&, const std::string& ext);
	
protected:
	CServiceVideoUpdate *m_pServiceParent;
	bool m_bFullScreen;
	

	bool IsShaderPresent(const std::string&) const;
	bool IsMeshPresent(const std::string&) const;

	std::map<std::string, IShader*> m_mShaderMap;
	std::map<std::string, IMesh*> m_mMeshMap;


private:
	DISALLOW_COPY_AND_ASSIGN(CRendererOpenGL);
};

#endif //FABIAN_CRENDEREROPENGL_H_
