#include "CA3dReader.h"

#include <tchar.h>
#include <iostream>
#include <fstream>

using namespace std;

CA3dReader::CA3dReader()
{
}

CA3dReader::~CA3dReader()
{
}

bool CA3dReader::Read(const string& filename)
{
	ifstream file(filename, ios::binary | ios::in);
	if (file.is_open())
	{
		//Check if a3d file
		string fileType;
		fileType.resize(3);
		file.read(&fileType[0], sizeof(char)*3);
		if (fileType != "a3D") return false;

		//Check type
		char type;
		file.read(&type, sizeof(char));

		m_type[0]= false;
		m_type[1] = false;
		unsigned int size = 3;

		//Has normals
		if ((type & 1) == 1)
		{
			m_type[0] = true;
			size += 3;
		}
		//Has TexCoords
		if ((type & 3) == 3)
		{
			m_type[1] = true;
			size += 2;
		}

		//Read all vertices
		unsigned int temp;
		file.read((char*)&temp, sizeof(int));

		m_vertices.resize(size*temp);
		file.read((char*)&m_vertices[0], sizeof(float)*size*temp);

		//Read indices
		file.read((char*)&temp, sizeof(int));

		m_indices.resize(temp*3);
		file.read((char*)&m_indices[0], sizeof(int)*temp*3);

		//Close the file
		file.close();
		return true;
	}
	return false;
}

