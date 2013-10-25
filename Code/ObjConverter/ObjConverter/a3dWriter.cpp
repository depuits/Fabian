#include "a3dWriter.h"

#include <fstream>
#include <iostream>

using namespace std;

a3dWriter::a3dWriter()
{
}

a3dWriter::~a3dWriter()
{
}

void a3dWriter::Write(wstring& filename)
{
	ofstream file(filename, ios::binary | ios::out);
	if (file.is_open())
	{
		//Write identifier
		file.write("a3D", sizeof(char)*3);

		//Write type of file
		char type = GetType();
		file.write(&type, sizeof(char));

		//Write data
		int size = m_vertices.size();
		file.write((char*)&size, sizeof(int));

		int tempProgress = 0;
		int currentProgress = 0;

		for (unsigned int i = 0; i < m_vertices.size(); ++i)
		{
			float temp = m_vertices[i].X;
			file.write((char*)&temp, sizeof(float));
			temp = m_vertices[i].Y;
			file.write((char*)&temp, sizeof(float));
			temp = m_vertices[i].Z;
			file.write((char*)&temp, sizeof(float));

			if (m_normals.size() > 0)
			{
				temp = m_normals[i].X;
				file.write((char*)&temp, sizeof(float));
				temp = m_normals[i].Y;
				file.write((char*)&temp, sizeof(float));
				temp = m_normals[i].Z;
				file.write((char*)&temp, sizeof(float));
			}

			if (m_texCoords.size() > 0)
			{
				temp = m_texCoords[i].X;
				file.write((char*)&temp, sizeof(float));
				temp = m_texCoords[i].Y;
				file.write((char*)&temp, sizeof(float));
			}

			tempProgress = (int)(i / ((float)(m_vertices.size()+m_faces.size()) / 50.0f));
			for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);
		}

		//Write indices
		size = m_faces.size();
		file.write((char*)&size, sizeof(int));
		for (unsigned int i = 0; i < m_faces.size(); ++i)
		{
			unsigned int temp = (int) m_faces[i][0].X - 1; // In directX the indices start with 0, here they start with 1
			file.write((char*)&temp, sizeof(int));
			temp = (int) m_faces[i][1].X - 1; // In directX the indices start with 0, here they start with 1
			file.write((char*)&temp, sizeof(int));
			temp = (int) m_faces[i][2].X - 1; // In directX the indices start with 0, here they start with 1
			file.write((char*)&temp, sizeof(int));

			tempProgress = (int)((i+m_vertices.size()) / ((m_vertices.size()+m_faces.size()) / 50.0f));
			for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);
		}

		tempProgress = 50;
		for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);

		//Close the file
		file.close();
	}
}

void a3dWriter::SetVertices(vector<Point3D>& vertices)
{
	m_vertices = vertices;
}

void a3dWriter::SetNormals(vector<Point3D>& normals)
{
	m_normals = normals;
}

void a3dWriter::SetTexCoords(vector<Point2D>& texCoords)
{
	m_texCoords = texCoords;
}

void a3dWriter::SetFaces(vector<vector<Point3D>>& faces)
{
	m_faces = faces;
}

char a3dWriter::GetType()
{
	char type = 0;
	if (m_normals.size() > 0) type += 1;
	if (m_texCoords.size() > 0) type += 2;
	return type;
}