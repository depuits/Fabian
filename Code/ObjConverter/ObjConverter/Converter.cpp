#include "Converter.h"
#include "ObjReader.h"
#include "ObjWriter.h"

#include "a3dReader.h"
#include "a3dWriter.h"

#include <iostream>
#include <tchar.h>
#include <fstream>

using namespace std;

Converter::Converter()
{
}

Converter::~Converter()
{
}

void Converter::Convert(const vector<wstring>& files)
{
	for (unsigned int fileNo = 0; fileNo < files.size(); ++fileNo)
	{
		ifstream file(files[fileNo], ios::binary | ios::in);
		if (file.is_open())
		{
			//Check if a3d file or obj
			string fileType;
			fileType.resize(3);
			file.read(&fileType[0], sizeof(char)*3);
			file.close();

			if (fileType == "a3D") ConvertA3d(files[fileNo]);
			else ConvertObj(files[fileNo]);
		}
	}
}

void Converter::ConvertObj(const wstring& file)
{
	wcout << _T("\n\nStart reading \"")+file+_T("\":\n\n");
	ObjReader* reader = new ObjReader();
	reader -> Read(file);

	reader -> GetVertices(m_vertices);
	reader -> GetNormals(m_normals);
	reader -> GetTexCoords(m_texCoords);
	reader -> GetFaces(m_faces);

	delete reader;

	wcout << _T("Vertices:  ") << m_vertices.size() << _T("\n");
	wcout << _T("Normals:   ") << m_normals.size() << _T("\n");
	wcout << _T("TexCoords: ") << m_texCoords.size() << _T("\n");
	wcout << _T("Faces:     ") << m_faces.size() << _T("\n\n");

	if (!AreFacesReady())
	{
		wcout << _T("The faces are not ready to be exported yet.\n");
		wcout << _T("Start optimising the mesh.\n");

		if (Optimise())
		{
			wcout << _T("\nOptimising done: \n\n");
			wcout << _T("Vertices:  ") << m_vertices.size() << _T("\n");
			wcout << _T("Normals:   ") << m_normals.size() << _T("\n");
			wcout << _T("TexCoords: ") << m_texCoords.size() << _T("\n");
			wcout << _T("Faces:     ") << m_faces.size() << _T("\n\n");
		} else {
			wcout << _T("\nCould not optimise the mesh any more.\n\n");
		}

		if (!AreAllFacesTris())
		{
			wcout << _T("Converting to tris:   ");
			Triangulate();
			wcout << _T(" Done.\n\n");
			wcout << _T("New number of faces: ") << m_faces.size() << _T("\n\n");
		} else {
			wcout << _T("All faces are already triangles.\n");
		}

		wcout << _T("Changing indices:     ");
		IndicesEqualiser();
		wcout << _T(" Done.\n\n");
		wcout << _T("Vertices:  ") << m_vertices.size() << _T("\n");
		wcout << _T("Normals:   ") << m_normals.size() << _T("\n");
		wcout << _T("TexCoords: ") << m_texCoords.size() << _T("\n");
		wcout << _T("Faces:     ") << m_faces.size() << _T("\n\n");
	}
		
	wcout << _T("Preparing to write the file.\n");

	a3dWriter* writer = new a3dWriter();
	writer -> SetVertices(m_vertices);
	writer -> SetNormals(m_normals);
	writer -> SetTexCoords(m_texCoords);
	writer -> SetFaces(m_faces);

	wstring newFileName = file.substr(0, file.length()-4);
	newFileName.append(_T(".a3d"));

	wcout << _T("Writing a3d file:     ");

	writer -> Write(newFileName);
	delete writer;

	wcout << _T(" Done.\n");
}

void Converter::ConvertA3d(const wstring& file)
{
	wcout << _T("\n\nStart reading \"")+file+_T("\":\n\n");
	a3dReader* reader = new a3dReader();
	reader -> Read(file);

	reader -> GetVertices(m_vertices);
	reader -> GetNormals(m_normals);
	reader -> GetTexCoords(m_texCoords);
	reader -> GetFaces(m_faces);

	delete reader;

	wcout << _T("Vertices:  ") << m_vertices.size() << _T("\n");
	wcout << _T("Normals:   ") << m_normals.size() << _T("\n");
	wcout << _T("TexCoords: ") << m_texCoords.size() << _T("\n");
	wcout << _T("Faces:     ") << m_faces.size() << _T("\n\n");

	wcout << _T("Start optimising the mesh.\n");

	if (Optimise())
	{
		wcout << _T("\nOptimising done: \n\n");
		wcout << _T("Vertices:  ") << m_vertices.size() << _T("\n");
		wcout << _T("Normals:   ") << m_normals.size() << _T("\n");
		wcout << _T("TexCoords: ") << m_texCoords.size() << _T("\n");
		wcout << _T("Faces:     ") << m_faces.size() << _T("\n\n");
	} else {
		wcout << _T("\nCould not optimise the mesh any more.\n\n");
	}
		
	wcout << _T("Preparing to write the file.\n");

	ObjWriter* writer = new ObjWriter();
	writer -> SetVertices(m_vertices);
	writer -> SetNormals(m_normals);
	writer -> SetTexCoords(m_texCoords);
	writer -> SetFaces(m_faces);

	wstring newFileName = file.substr(0, file.length()-4);
	newFileName.append(_T(".obj"));

	wcout << _T("Writing obj file:     ");

	writer -> Write(newFileName);
	delete writer;

	wcout << _T(" Done.\n");
}

bool Converter::AreFacesReady()
{
	for (unsigned int i = 0; i < m_faces.size(); ++i)
	{
		for (unsigned int j = 0; j < m_faces[i].size(); ++j)
		{
			if (j >= 3) return false;
			if ((m_faces[i][j].X == m_faces[i][j].Y) && (m_faces[i][j].Y == m_faces[i][j].Z)) return false;
		}
	}
	return true;
}

bool Converter::AreAllFacesTris()
{
	for (unsigned int i = 0; i < m_faces.size(); ++i)
	{
		if(m_faces[i].size() != 3) return false;
	}
	return true;
}

bool Converter::Optimise()
{
	bool changes = false;
	wcout << _T("\n  Checking vertices:  ");
	changes |= OptimiseVertices();
	wcout << _T(" Done.\n");
	wcout << _T("  Checking normals:   ");
	changes |= OptimiseNormals();
	wcout << _T(" Done.\n");
	wcout << _T("  Checking texCoords: ");
	changes |= OptimiseTexCoords();
	wcout << _T(" Done.\n");

	if (changes) 
	{
		wcout << _T("  Applying changes:   ");
		ApplyChangesToIndices();
		wcout << _T(" Done.\n");
	}

	return changes;
}

bool Converter::OptimiseVertices()
{
	bool changes = false;
	//empty the temp cache
	m_newVerticesIndex.resize(0);
	m_newVerticesIndex.reserve(m_vertices.size()+1);
	m_newVerticesIndex.push_back(0);

	vector<Point3D> newVertices;
	newVertices.reserve(m_vertices.size());

	int currentProgress = 0;
	int temp = 0;

	for (unsigned int i = 0; i < m_vertices.size(); ++i)
	{
		int AlreadyExists = -1;
		for (unsigned int j = 0; j < newVertices.size(); ++j)
		{
			if (m_vertices[i] == newVertices[j]) AlreadyExists = j;
		}

		//If not already exists
		if (AlreadyExists < 0)
		{
			newVertices.push_back(m_vertices[i]);
			m_newVerticesIndex.push_back(newVertices.size());
		//If already exists
		} else {
			changes = true;
			m_newVerticesIndex.push_back(AlreadyExists+1);
		}

		temp = (int)(i / (m_vertices.size() / 50.0f));
		for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);
	}
	temp = 50;
	for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);

	if (changes) m_vertices = newVertices;
	return changes;
}

bool Converter::OptimiseNormals()
{
	bool changes = false;
	//empty the temp cache
	m_newNormalsIndex.resize(0);
	m_newNormalsIndex.reserve(m_normals.size()+1);
	m_newNormalsIndex.push_back(0);

	vector<Point3D> newNormals;
	newNormals.reserve(m_normals.size());

	int currentProgress = 0;
	int temp = 0;

	for (unsigned int i = 0; i < m_normals.size(); ++i)
	{
		int AlreadyExists = -1;
		for (unsigned int j = 0; j < newNormals.size(); ++j)
		{
			if (m_normals[i] == newNormals[j]) AlreadyExists = j;
		}

		//If not already exists
		if (AlreadyExists < 0)
		{
			newNormals.push_back(m_normals[i]);
			m_newNormalsIndex.push_back(newNormals.size());
		//If already exists
		} else {
			changes = true;
			m_newNormalsIndex.push_back(AlreadyExists+1);
		}

		temp = (int)(i / (m_normals.size() / 50.0f));
		for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);
	}
	temp = 50;
	for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);

	if (changes) m_normals = newNormals;
	return changes;
}

bool Converter::OptimiseTexCoords()
{
	bool changes = false;
	//empty the temp cache
	m_newTexCoordsIndex.resize(0);
	m_newTexCoordsIndex.reserve(m_texCoords.size()+1);
	m_newTexCoordsIndex.push_back(0);

	vector<Point2D> newTexCoords;
	newTexCoords.reserve(m_texCoords.size());

	int currentProgress = 0;
	int temp = 0;

	for (unsigned int i = 0; i < m_texCoords.size(); ++i)
	{
		int AlreadyExists = -1;
		for (unsigned int j = 0; j < newTexCoords.size(); ++j)
		{
			if (m_texCoords[i] == newTexCoords[j]) AlreadyExists = j;
		}

		//If not already exists
		if (AlreadyExists < 0)
		{
			newTexCoords.push_back(m_texCoords[i]);
			m_newTexCoordsIndex.push_back(newTexCoords.size());
		//If already exists
		} else {
			changes = true;
			m_newTexCoordsIndex.push_back(AlreadyExists+1);
		}

		temp = (int)(i / (m_texCoords.size() / 50.0f));
		for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);
	}
	temp = 50;
	for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);

	if (changes) m_texCoords = newTexCoords;
	return changes;
}

void Converter::ApplyChangesToIndices()
{
	int currentProgress = 0;
	int temp = 0;

	for (unsigned int i = 0; i < m_faces.size(); ++i)
	{
		for (unsigned int j = 0; j < m_faces[i].size(); ++j)
		{
			m_faces[i][j].X = (float) m_newVerticesIndex[(unsigned int) m_faces[i][j].X];
			m_faces[i][j].Y = (float) m_newTexCoordsIndex[(unsigned int) m_faces[i][j].Y];
			m_faces[i][j].Z = (float) m_newNormalsIndex[(unsigned int) m_faces[i][j].Z];
		}

		temp = (int)(i / (m_faces.size() / 50.0f));
		for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);
	}
	temp = 50;
	for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);
}

void Converter::IndicesEqualiser()
{
	vector<Point3D> newVertices, newNormals, newFaces;
	vector<Point2D> newTexCoords;
	m_newVerticesIndex.resize(0);
	m_newNormalsIndex.resize(0);
	m_newTexCoordsIndex.resize(0);

	newVertices.reserve(m_vertices.size());
	newNormals.reserve(m_normals.size());
	newTexCoords.reserve(m_texCoords.size());
	newFaces.reserve(m_faces.size());
	m_newVerticesIndex.reserve(m_faces.size());
	m_newNormalsIndex.reserve(m_faces.size());
	m_newTexCoordsIndex.reserve(m_faces.size());

	int currentProgress = 0;
	int temp = 0;

	for (unsigned int i = 0; i < m_faces.size(); ++i)
	{
		for (unsigned int j = 0; j < m_faces[i].size(); ++j)
		{
			//Check if already exist
			int AlreadyExists = -1;
			for (unsigned int x = 0; x < newFaces.size(); ++x)
			{
				if(newFaces[x] == m_faces[i][j])
				{
					AlreadyExists = x;
					x = newFaces.size();
				}
			}
			//If already exists
			if (AlreadyExists > -1)
			{
				m_newVerticesIndex.push_back(AlreadyExists+1);
			//If not already exists
			} else {
				newVertices.push_back(m_vertices[(unsigned int) m_faces[i][j].X-1]);
				if(m_normals.size() > 0) newNormals.push_back(m_normals[(unsigned int) m_faces[i][j].Z-1]);
				if(m_texCoords.size() > 0) newTexCoords.push_back(m_texCoords[(unsigned int) m_faces[i][j].Y-1]);
				newFaces.push_back(m_faces[i][j]);

				m_newVerticesIndex.push_back(newFaces.size());
			}
		}

		temp = (int)(i / (m_faces.size() / 50.0f));
		for (; currentProgress < temp; ++currentProgress) wcout << wchar_t(223);
	}
	temp = 50;
	for (; currentProgress < temp; ++currentProgress) wcout << wchar_t(223);

	//Apply changes
	m_vertices = newVertices;
	m_normals = newNormals;
	m_texCoords = newTexCoords;
	m_faces.resize(0);
	m_faces.reserve(m_newVerticesIndex.size()/3);
	for (unsigned int i = 0; i < m_newVerticesIndex.size()/3; ++i)
	{
		vector<Point3D> temp;
		for (unsigned int j = 0; j < 3; ++j)
		{
			Point3D point;

			point.X = (float) m_newVerticesIndex[j+(i*3)];
			point.Y = (float) m_newVerticesIndex[j+(i*3)];
			point.Z = (float) m_newVerticesIndex[j+(i*3)];

			temp.push_back(point);
		}
		m_faces.push_back(temp);
	}
}

void Converter::Triangulate()
{
	vector<vector<Point3D>> newFaces;
	int currentProgress = 0;
	int temp = 0;

	for (unsigned int i = 0; i < m_faces.size(); ++i)
	{
		for (unsigned int j = 0; j < m_faces[i].size()-2; ++j)
		{
			vector<Point3D> temp;

			temp.push_back(m_faces[i][0]);
			temp.push_back(m_faces[i][1+j]);
			temp.push_back(m_faces[i][2+j]);

			newFaces.push_back(temp);
		}

		temp = (int)(i / (m_faces.size() / 50.0f));
		for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);
	}
	temp = 50;
	for (; currentProgress < temp; ++ currentProgress) wcout << wchar_t(223);

	m_faces = newFaces;
}

void Converter::Debug()
{
	wcout << _T("\n\n\n");

	for (unsigned int i = 0; i < m_vertices.size(); ++i)
	{
		wcout << _T("vertex ") << i+1 << _T(" (") << m_vertices[i].X << _T(", ") << m_vertices[i].Y << _T(", ") << m_vertices[i].Z << _T(")\n");
	}
	wcout << _T("\n");

	for (unsigned int i = 0; i < m_normals.size(); ++i)
	{
		wcout << _T("normal ") << i+1 << _T(" (") << m_normals[i].X << _T(", ") << m_normals[i].Y << _T(", ") << m_normals[i].Z << _T(")\n");
	}
	wcout << _T("\n");

	for (unsigned int i = 0; i < m_texCoords.size(); ++i)
	{
		wcout << _T("texcoord ") << i+1 << _T(" (") << m_texCoords[i].X << _T(", ") << m_texCoords[i].Y << _T(")\n");
	}	
	wcout << _T("\n");

	for (unsigned int i = 0; i < m_faces.size(); ++i)
	{
		wcout << _T("face ") << i+1 << _T(" ");
		for (unsigned int j = 0; j < m_faces[i].size(); ++j)
		{
			wcout << _T("(") << m_faces[i][j].X << _T(", ") << m_faces[i][j].Y << _T(", ") << m_faces[i][j].Z << _T(") ");
		}
		wcout << _T("\n");
	}
}