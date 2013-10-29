#ifndef FABIAN_CSHADER_H_
#define FABIAN_CSHADER_H_

#include "FabianDef.h"
#include <gl/glew.h>

class CShader
{
public:
	CShader();
	virtual ~CShader();
	
	virtual void Load();
	virtual void Apply();

	void SetVar(int id, int var);
	void GetVarId(int& id, char* name);

protected:
	GLuint LoadShaders(const char *,const char *);
	
	GLuint m_uProgramID;

private:
	DISALLOW_COPY_AND_ASSIGN(CShader);
};

#endif //FABIAN_CSHADER_H_
