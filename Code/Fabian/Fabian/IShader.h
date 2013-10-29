#ifndef FABIAN_ISHADER_H_
#define FABIAN_ISHADER_H_

#include "FabianDef.h"
#include <gl/glew.h>

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <glm/glm.hpp>
#pragma warning( pop )

class IShader
{
public:
	IShader();
	virtual ~IShader();
	
	virtual void Load();
	virtual void Apply();

	void SetVar(int id, int var);
	void GetVarId(int& id, const char *name);

	void SetProjection(const glm::mat4&);
	void SetView(const glm::mat4&);
	void SetWorld(const glm::mat4&);


protected:
	GLuint LoadShaders(const char *,const char *);
	
	GLuint m_uProgramID;

private:
	DISALLOW_COPY_AND_ASSIGN(IShader);
};

#endif //FABIAN_ISHADER_H_
