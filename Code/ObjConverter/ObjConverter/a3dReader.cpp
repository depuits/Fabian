#include "a3dReader.h"

#include <iostream>
#include <fstream>

using namespace std;

a3dReader::a3dReader()
{
}

a3dReader::~a3dReader()
{
}

void a3dReader::Read(const string& filename)
{
	ifstream file(filename.c_str(), ios::binary | ios::in);
	if (file.is_open())
	{
		//Check if a3d file
		string fileType;
		fileType.resize(3);
		file.read(&fileType[0], sizeof(char)*3);
		if (fileType != "a3D") return;

		//Check type
		char type;
		file.read(&type, sizeof(char));

		bool hasNormals = false;
		bool hasTexCoords = false;

		if ((type & 1) == 1) hasNormals = true;
		if ((type & 3) == 3) hasTexCoords = true;

		//Read all except the faces
		unsigned int size;
		file.read((char*)&size, sizeof(int));
		for (unsigned int i = 0; i < size; ++i)
		{
			//vertex
			Point3D vertex;
			file.read((char*)&vertex, sizeof(Point3D));
			m_vertices.push_back(vertex);

			//normal
			if (hasNormals)
			{
				Point3D normal;
				file.read((char*)&normal, sizeof(Point3D));
				m_normals.push_back(normal);
			}

			//texCoord
			if (hasTexCoords)
			{
				Point2D texcoord;
				file.read((char*)&texcoord, sizeof(Point2D));
				m_texCoords.push_back(texcoord);
			}
		}

		//Read faces
		file.read((char*)&size, sizeof(int));
		for (unsigned int i = 0; i < size; ++i)
		{
			vector<Point3D> temp;
			for (unsigned int j = 0; j < 3; ++j)
			{
				int index;
				file.read((char*)&index, sizeof(int));
				Point3D face((float) index+1, (float) index+1, (float) index+1);  // In directX the indices start with 0, here they start with 1
				temp.push_back(face);
			}
			m_faces.push_back(temp);
		}

		//Close the file
		file.close();
	}
}

bool a3dReader::GetVertices(vector<Point3D>& vertices)
{
	if (m_vertices.size() > 0)
	{
		vertices = m_vertices;
		return true;
	}
	return false;
}

bool a3dReader::GetNormals(vector<Point3D>& normals)
{
	if (m_normals.size() > 0)
	{
		normals = m_normals;
		return true;
	}
	return false;
}

bool a3dReader::GetTexCoords(vector<Point2D>& texCoords)
{
	if (m_texCoords.size() > 0)
	{
		texCoords = m_texCoords;
		return true;
	}
	return false;
}

bool a3dReader::GetFaces(vector<vector<Point3D> >& faces)
{
	if (m_faces.size() > 0)
	{
		faces = m_faces;
		return true;
	}
	return false;
}
