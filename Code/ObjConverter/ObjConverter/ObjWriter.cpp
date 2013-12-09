#include "ObjWriter.h"

#include <fstream>
#include <iostream>
#include <tchar.h>

using namespace std;

ObjWriter::ObjWriter()
{
}

ObjWriter::~ObjWriter()
{
}

void ObjWriter::Write(wstring& filename)
{
	wofstream file(filename);

	int tempProgress = 0;
	int currentProgress = 0;

	if (file.is_open())
	{
		//Write vertices
		for (unsigned int i = 0; i < m_vertices.size(); ++i)
		{
			file << _T("v ") << m_vertices[i].X << _T(" ") << m_vertices[i].Y << _T(" ") << m_vertices[i].Z << _T("\n") ;

			tempProgress = (int)(i / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
			for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);
		}

		//Write normals
		if (m_normals.size() > 0)
		{
			file << _T("\n");
			for (unsigned int i = 0; i < m_normals.size(); ++i)
			{
				file << _T("vn ") << m_normals[i].X << _T(" ") << m_normals[i].Y << _T(" ") << m_normals[i].Z << _T("\n") ;
				
				tempProgress = (int)((i+m_vertices.size()) / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
				for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);
			}
		}

		//Write texCoords
		if (m_texCoords.size() > 0)
		{
			file << _T("\n");
			for (unsigned int i = 0; i < m_texCoords.size(); ++i)
			{
				file << _T("vt ") << m_texCoords[i].X << _T(" ") << (1 - m_texCoords[i].Y) << _T(" 0 \n") ;
				
				tempProgress = (int)((i+m_vertices.size()+m_texCoords.size()) / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
				for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);
			}
		}

		//Write faces
		file << _T("\n");
		for (unsigned int i = 0; i < m_faces.size(); ++i)
		{
			file << _T("f");
			for (unsigned int j = 0; j < m_faces[i].size(); ++j)
			{
				if (m_normals.size() > 0 || m_texCoords.size() > 0)
				{
					file << _T(" ") << m_faces[i][j].X;
					if (m_texCoords.size() > 0) file << _T("/") << m_faces[i][j].Y;
					else file << _T("/");
					if (m_normals.size() > 0) file << _T("/") << m_faces[i][j].Z;
					else file << _T("/");
				} else {
					file << _T(" ") << m_faces[i][j].X;
				}
			}
			file << _T("\n");

			tempProgress = (int)((i+m_vertices.size()+m_normals.size()+m_texCoords.size()) / ((float)(m_vertices.size()+m_normals.size()+m_texCoords.size()+m_faces.size()) / 50.0f));
			for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);
		}

		tempProgress = 50;
		for (; currentProgress < tempProgress; ++ currentProgress) wcout << wchar_t(223);

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

void ObjWriter::SetFaces(vector<vector<Point3D>>& faces)
{
	m_faces = faces;
}