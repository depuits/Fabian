#pragma once

#include <string>
#include <vector>

#include "Point2D.h"
#include "Point3D.h"

class Converter
{
public:
	Converter();
	~Converter();

	void Convert(const std::vector<std::string>& files);
	void ConvertObj(const std::string& file);
	void ConvertA3d(const std::string& file);

	bool AreFacesReady();
	bool AreAllFacesTris();

	bool Optimise();

	void IndicesEqualiser();

	void Debug();

private:

	bool OptimiseVertices();
	bool OptimiseNormals();
	bool OptimiseTexCoords();

	void ApplyChangesToIndices();

	void Triangulate();

	//Normal data save
	std::vector<Point3D> m_vertices, m_normals;
	std::vector<Point2D> m_texCoords;
	std::vector<std::vector<Point3D> > m_faces;

	//Temporary save
	std::vector<int> m_newVerticesIndex, m_newNormalsIndex, m_newTexCoordsIndex;
};
