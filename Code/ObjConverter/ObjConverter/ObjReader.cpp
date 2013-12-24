#include "ObjReader.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

ObjReader::ObjReader()
{
}

ObjReader::~ObjReader()
{
}

void ObjReader::Read(const string& filename)
{
	ifstream file(filename.c_str());
	string line;
	if (file.is_open())
	{
		while(!file.eof())
		{
			getline(file, line);

			std::string type = line.substr(0, line.find_first_of(' '));

			if (type == "v")
			{
				ReadVertex(line);
			} else if (type == "vn")
			{
				ReadNormal(line);
			} else if (type == "vt")
			{
				ReadTexCoord(line);
			} else if (type == "f")
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

bool ObjReader::GetFaces(vector<vector<Point3D> >& faces)
{
	if (m_faces.size() > 0)
	{
		faces = m_faces;
		return true;
	}
	return false;
}

void ObjReader::ReadVertex(string& vertex)
{
	string strX, strY, strZ;

	strZ = vertex.substr(1);
	strZ = strZ.substr(strZ.find_first_not_of(' '));

	size_t pos = strZ.find_first_of(' ');
	strX = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(' '));

	pos = strZ.find_first_of(' ');
	strY = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(' '));

	Point3D point;
	point.X = (float) atof(strX.c_str());
	point.Y = (float) atof(strY.c_str());
	point.Z = (float) atof(strZ.c_str());

	m_vertices.push_back(point);
}

void ObjReader::ReadNormal(string& normal)
{
	string strX, strY, strZ;

	strZ = normal.substr(2);
	strZ = strZ.substr(strZ.find_first_not_of(' '));

	size_t pos = strZ.find_first_of(' ');
	strX = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(' '));

	pos = strZ.find_first_of(' ');
	strY = strZ.substr(0, pos);
	strZ = strZ.substr(pos+1);
	strZ = strZ.substr(strZ.find_first_not_of(' '));

	Point3D point;
	point.X = (float) atof(strX.c_str());
	point.Y = (float) atof(strY.c_str());
	point.Z = (float) atof(strZ.c_str());

	m_normals.push_back(point);
}

void ObjReader::ReadTexCoord(string& texCoord)
{
	string strX, strY;

	strY = texCoord.substr(2);
	strY = strY.substr(strY.find_first_not_of(' '));

	size_t pos = strY.find_first_of(' ');
	strX = strY.substr(0, pos);
	strY = strY.substr(pos+1);
	strY = strY.substr(strY.find_first_not_of(' '));

	pos = strY.find_first_of(' ');
	strY = strY.substr(0, pos);

	Point2D point;
	point.X = (float) atof(strX.c_str());
	point.Y = 1 - (float) atof(strY.c_str());

	m_texCoords.push_back(point);
}

void ObjReader::ReadFace(string& face)
{
	string strX, strY;

	strY = face.substr(2);
	strY = strY.substr(strY.find_first_not_of(' '));

	vector<Point3D> tempFace;

	while (strY.length())
	{
		//Get one chunk and prepare the next
		size_t pos = strY.find_first_of(' ');
		strX = strY.substr(0, pos);
		if (pos == string::npos) strY = "";
		else strY = strY.substr(pos+1);
		pos = strY.find_first_not_of(' ');
		if (pos == string::npos) strY = "";
		else strY = strY.substr(pos);

		//Analyse the chunk
		string temp1, temp2;
		pos = strX.find_first_of('/');
		if (pos == string::npos)
		{
			//Only vertices were used
			Point3D point;
			point.X = (float) atof(strX.c_str());
			point.Y = 0;
			point.Z = 0;

			tempFace.push_back(point);
		} else {
			//texture coordinates and/or normals were used too
			temp1 = strX.substr(0, pos);
			strX = strX.substr(pos+1);

			pos = strX.find_first_of('/');
			temp2 = strX.substr(0, pos);
			strX = strX.substr(pos+1);

			Point3D point;
			point.X = (float) atof(temp1.c_str());
			point.Y = (float) atof(temp2.c_str());
			point.Z = (float) atof(strX.c_str());

			tempFace.push_back(point);
		}
	}

	m_faces.push_back(tempFace);
}
