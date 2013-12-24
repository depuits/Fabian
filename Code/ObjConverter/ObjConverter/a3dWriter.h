#pragma once

#include <string>
#include <vector>

#include "Point2D.h"
#include "Point3D.h"

class a3dWriter
{
public:
	a3dWriter();
	~a3dWriter();

	void Write(std::string& filename);

	void SetVertices(std::vector<Point3D>& vertices);
	void SetNormals(std::vector<Point3D>& normals);
	void SetTexCoords(std::vector<Point2D>& texCoords);
	void SetFaces(std::vector<std::vector<Point3D> >& faces);

private:
	char GetType();

	std::vector<Point3D> m_vertices, m_normals;
	std::vector<Point2D> m_texCoords;
	std::vector<std::vector<Point3D> > m_faces;
};
