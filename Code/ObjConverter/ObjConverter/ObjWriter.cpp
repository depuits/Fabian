#include "ObjWriter.h"

#include <fstream>
#include <iostream>

using namespace std;

ObjWriter::ObjWriter()
{
}

ObjWriter::~ObjWriter()
{
}

void ObjWriter::Write(string& filename)
{
	ofstream file(filename.c_str());

	int tempProgress = 0;
	int currentProgress = 0;

	if (file.is_open())
	{
		//Write vertices
		for (unsigned int i = 0; i < m_vertices.size(); ++i)
		{
			file << "v " << m_vertices[i].X << " " << m_vertices[i].Y << " " << m_vertices[i].Z << "\n";

			tempProgress = (int)(i / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
			for (; currentProgress < tempProgress; ++ currentProgress) cout << char(223);
		}

		//Write normals
		if (m_normals.size() > 0)
		{
			file << "\n";
			for (unsigned int i = 0; i < m_normals.size(); ++i)
			{
				file << "vn " << m_normals[i].X << " " << m_normals[i].Y << " " << m_normals[i].Z << "\n";

				tempProgress = (int)((i+m_vertices.size()) / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
				for (; currentProgress < tempProgress; ++ currentProgress) cout << char(223);
			}
		}

		//Write texCoords
		if (m_texCoords.size() > 0)
		{
			file << "\n";
			for (unsigned int i = 0; i < m_texCoords.size(); ++i)
			{
				file << "vt " << m_texCoords[i].X << " " << (1 - m_texCoords[i].Y) << " 0 \n";

				tempProgress = (int)((i+m_vertices.size()+m_texCoords.size()) / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
				for (; currentProgress < tempProgress; ++ currentProgress) cout << char(223);
			}
		}

		//Write faces
		file << "\n";
		for (unsigned int i = 0; i < m_faces.size(); ++i)
		{
			file << "f";
			for (unsigned int j = 0; j < m_faces[i].size(); ++j)
			{
				if (m_normals.size() > 0 || m_texCoords.size() > 0)
				{
					file << " " << m_faces[i][j].X;
					if (m_texCoords.size() > 0) file << "/" << m_faces[i][j].Y;
					else file << "/";
					if (m_normals.size() > 0) file << "/" << m_faces[i][j].Z;
					else file << "/";
				} else {
					file << " " << m_faces[i][j].X;
				}
			}
			file << "\n";

			tempProgress = (int)((i+m_vertices.size()+m_normals.size()+m_texCoords.size()) / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
			for (; currentProgress < tempProgress; ++ currentProgress) cout << char(223);
		}

		tempProgress = 50;
		for (; currentProgress < tempProgress; ++ currentProgress) cout << char(223);

		//Close the file
		file.close();
	}
}

void ObjWriter::SetVertices(vector<Point3D>& vertices)
{
	m_vertices = vertices;
}

void ObjWriter::SetNormals(vector<Point3D>& normals)
{
	m_normals = normals;
}

void ObjWriter::SetTexCoords(vector<Point2D>& texCoords)
{
	m_texCoords = texCoords;
}

void ObjWriter::SetFaces(vector<vector<Point3D> >& faces)
{
	m_faces = faces;
}
