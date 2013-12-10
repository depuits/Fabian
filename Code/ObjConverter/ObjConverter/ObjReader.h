#pragma once

#include <string>
#include <vector>
#include "Point3D.h"
#include "Point2D.h"

class ObjReader
{
public:
	ObjReader();
	~ObjReader();
	
	void Read(const std::wstring& filename);

	bool GetVertices(std::vector<Point3D>& vertices);
	bool GetNormals(std::vector<Point3D>& normals);
	bool GetTexCoords(std::vector<Point2D>& texCoords);
	bool GetFaces(std::vector<std::vector<Point3D>>& faces);

private:

	void ReadVertex(std::wstring& vertex);
	void ReadNormal(std::wstring& normal);
	void ReadTexCoord(std::wstring& texCoord);
	void ReadFace(std::wstring& face);

	std::vector<Point3D> m_vertices, m_normals;
	std::vector<Point2D> m_texCoords;
	std::vector<std::vector<Point3D>> m_faces;
};