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

	bool Read(const std::wstring& filename);
	Mesh* CreateObject(ContentManager* pContentManager);

private:
	std::vector<float> m_vertices;
	std::vector<int> m_indices;
	bool m_type[8];
};
