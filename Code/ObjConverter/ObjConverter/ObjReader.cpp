#include "ObjReader.h"

#include <tchar.h>
#include <iostream>
#include <fstream>

using namespace std;

ObjReader::ObjReader()
{
}

ObjReader::~ObjReader()
{
}
	
void ObjReader::Read(const wstring& filename)
{
	wifstream file(filename);
	wstring line;
	if (file.is_open())
	{
		while(!file.eof())
		{
			getline(file, line);

			std::wstring type = line.substr(0, line.find_first_of(_T(' ')));

			if (type == _T("v"))
			{
				ReadVertex(line);
			} else if (type == _T("vn"))
			{
				ReadNormal(line);
			} else if (type == _T("vt"))
			{
				ReadTexCoord(line);
			} else if (type == _T("f"))
			{
				ReadFace(line);
			}
		}

		//Close the file
		file.close();
	}
}

bool ObjReader::GetVertices(vector<Point3D>& vertices)
{
	if (m_vertices.size() > 0)
	{
		vertices = m_vertices;
		return true;
	}
	return false;
}

bool ObjReader::GetNormals(vector<Point3D>& normals)
{
	if (m_normals.size() > 0)
	{
		normals = m_normals;
		return true;
	}
	return false;
}

bool ObjReader::GetTexCoords(vector<Point2D>& texCoords)
{
	if (m_texCoords.size() > 0)
	{
		texCoords = m_texCoords;
		return true;
	}
	return false;
}

bool ObjReader::GetFaces(vector<vector<Point3D>>& faces)
{
	if (m_faces.size() > 0)
	{
		faces = m_faces;
		return true;
	}
	return false;
}

void ObjReader::ReadVertex(wstring& vertex)
{
	wstring strX, strY, strZ;

	strZ = vertex.substr(1);
	strZ = strZ.substr(strZ.find_first_not_of(_T(' ')));

	size_t pos = strZ.find_first_of(_T(' '));
	strX = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(_T(' ')));

	pos = strZ.find_first_of(_T(' '));
	strY = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(_T(' ')));

	Point3D point;
	point.X = (float) _wtof(strX.c_str());
	point.Y = (float) _wtof(strY.c_str());
	point.Z = (float) _wtof(strZ.c_str());

	m_vertices.push_back(point);
}

void ObjReader::ReadNormal(wstring& normal)
{
	wstring strX, strY, strZ;

	strZ = normal.substr(2);
	strZ = strZ.substr(strZ.find_first_not_of(_T(' ')));

	size_t pos = strZ.find_first_of(_T(' '));
	strX = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(_T(' ')));

	pos = strZ.find_first_of(_T(' '));
	strY = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(_T(' ')));

	Point3D point;
	point.X = (float) _wtof(strX.c_str());
	point.Y = (float) _wtof(strY.c_str());
	point.Z = (float) _wtof(strZ.c_str());

	m_normals.push_back(point);
}

void ObjReader::ReadTexCoord(wstring& texCoord)
{
	wstring strX, strY;

	strY = texCoord.substr(2);
	strY = strY.substr(strY.find_first_not_of(_T(' ')));

	size_t pos = strY.find_first_of(_T(' '));
	strX = strY.substr(0, pos);
	strY = strY.substr(pos+1);
	strY = strY.substr(strY.find_first_not_of(_T(' ')));

	pos = strY.find_first_of(_T(' '));
	strY = strY.substr(0, pos);

	Point2D point;
	point.X = (float) _wtof(strX.c_str());
	point.Y = 1 - (float) _wtof(strY.c_str());

	m_texCoords.push_back(point);
}

void ObjReader::ReadFace(wstring& face)
{
	wstring strX, strY;

	strY = face.substr(2);
	strY = strY.substr(strY.find_first_not_of(_T(' ')));

	vector<Point3D> tempFace;

	while (strY.length())
	{
		//Get one chunk and prepare the next
		size_t pos = strY.find_first_of(_T(' '));
		strX = strY.substr(0, pos);
		if (pos == string::npos) strY = _T("");
		else strY = strY.substr(pos+1);
		pos = strY.find_first_not_of(_T(' '));
		if (pos == string::npos) strY = _T("");
		else strY = strY.substr(pos);

		//Analyse the chunk
		wstring temp1, temp2;
		pos = strX.find_first_of(_T('/'));
		if (pos == string::npos)
		{
			//Only vertices were used
			Point3D point;
			point.X = (float) _wtof(strX.c_str());
			point.Y = 0;
			point.Z = 0;

			tempFace.push_back(point);
		} else {
			//texture coordinates and/or normals were used too
			temp1 = strX.substr(0, pos);
			strX = strX.substr(pos+1);

			pos = strX.find_first_of(_T('/'));
			temp2 = strX.substr(0, pos);
			strX = strX.substr(pos+1);

			Point3D point;
			point.X = (float) _wtof(temp1.c_str());
			point.Y = (float) _wtof(temp2.c_str());
			point.Z = (float) _wtof(strX.c_str());

			tempFace.push_back(point);
		}
	}

	m_faces.push_back(tempFace);
}