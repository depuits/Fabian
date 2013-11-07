#pragma once

#include <string>
#include <vector>

class ContentManager;
class Mesh;

class CA3dReader
{
public:
	CA3dReader();
	~CA3dReader();

	bool Read(const std::string& filename);
	
	std::vector<float> m_vertices;
	std::vector<int> m_indices;
	bool m_type[8];
};
