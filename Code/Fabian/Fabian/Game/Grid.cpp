#include "Grid.h"

FDISABLE_WARNING_START(4201)
//#define GLM_SWIZZLE <- can be used for vec4.xyz() method
#include <glm/glm.hpp>
FDISABLE_WARNING_END(4201)

//-------------------------------------
// constructor
Grid::Grid(int w, int h)
{
	m_Grid.resize(w, std::vector<GridEntity*>(h, nullptr) );
}
//-------------------------------------
// destructor
Grid::~Grid()
{
	// no deletion here because the components get deleted in the gameobjects
	/*for (unsigned x(0); x < m_Grid.size(); ++x)
		for (unsigned y(0); y < m_Grid[x].size(); ++y)
			delete m_Grid[x][y]; // might cause problems look over it again : gridentity component get delete in gameobject so maybe not here*/
}
//-------------------------------------

GridEntity* Grid::GetGObject(int x, int y) const
{
	if( IsInGrid(x, y) )
		return m_Grid[x][y];

	return nullptr;
}
bool Grid::SetGObject(int x, int y, GridEntity* o)
{
	if( IsInGrid(x, y) )
	{
		if( m_Grid[x][y] != nullptr )
			delete m_Grid[x][y];

		m_Grid[x][y] = o;

		return true;
	}

	return false;
}

bool Grid::IsInGrid(int x, int y) const
{
	if( x < 0 || y < 0 )
		return false;

	if( (unsigned)x >= m_Grid.size() )
		return false;
	if( (unsigned)y >= m_Grid[x].size() )
		return false;

	return true;
}
bool Grid::IsFlagRaised(int x, int y, GridEntity::CollFlag cf) const
{
	if( GetGObject(x, y) == nullptr )
		return false;

	return ( (m_Grid[x][y]->GetCollisionFlags() & cf) == cf);
}

void Grid::Reset()
{
	for (unsigned x(0); x < m_Grid.size(); ++x)
		for (unsigned y(0); y < m_Grid[x].size(); ++y)
			if( m_Grid[x][y] != nullptr)
				m_Grid[x][y]->Reset();
}






