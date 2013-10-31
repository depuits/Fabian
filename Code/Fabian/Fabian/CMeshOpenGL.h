#ifndef FABIAN_CMESHOPENGL_H_
#define FABIAN_CMESHOPENGL_H_

#include "FabianDef.h"
#include "IMesh.h"
#include <string>

#include <gl/glew.h>

class CMeshOpenGL : public IMesh
{
public:
	CMeshOpenGL();
	virtual ~CMeshOpenGL();
	
	virtual bool Load(const std::wstring&);
	virtual void Draw();

private:
	GLuint m_VertexArrayID,
			m_VertexBuffer,
			m_IndexBuffer;
	int m_iIndicesCount;

	DISALLOW_COPY_AND_ASSIGN(CMeshOpenGL);
};

#endif //FABIAN_CMESHOPENGL_H_
