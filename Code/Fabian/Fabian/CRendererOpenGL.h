#ifndef FABIAN_CRENDEREROPENGL_H_
#define FABIAN_CRENDEREROPENGL_H_

#include "IRenderer.h"
#include <map>

class CRendererOpenGL : public IRenderer
{
public:
	CRendererOpenGL();
	virtual ~CRendererOpenGL();
	
	virtual void Clear(float, float, float, float);
	
	virtual IShader *LoadShader(const std::string&);
	virtual IMesh *LoadMesh(const std::string&, const std::string& ext);
	
protected:
	bool IsShaderPresent(const std::string&) const;
	bool IsMeshPresent(const std::string&) const;

	std::map<std::string, IShader*> m_mShaderMap;
	std::map<std::string, IMesh*> m_mMeshMap;


private:
	DISALLOW_COPY_AND_ASSIGN(CRendererOpenGL);
};

#endif //FABIAN_CRENDEREROPENGL_H_
