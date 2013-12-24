#pragma once

#include <string>
#include <vector>
#include "Point3D.h"
#include "Point2D.h"

class a3dReader
{
public:
	a3dReader();
	~a3dReader();

	void Read(const std::string& filename);

	bool GetVertices(std::vector<Point3D>& vertices);
	bool GetNormals(std::vector<Point3D>& normals);
	bool GetTexCoords(std::vector<Point2D>& texCoords);
	bool GetFaces(std::vector<std::vector<Point3D> >& faces);

private:

	std::vector<Point3D> m_vertices, m_normals;
	std::vector<Point2D> m_texCoords;
	std::vector<std::vector<Point3D> > m_faces;
};
