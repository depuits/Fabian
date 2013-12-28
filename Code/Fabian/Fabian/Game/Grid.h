#ifndef H_GRID
#define H_GRID

#include <vector>
#include "GridEntity.h"

class Grid
{
public:
	static const int SCALE = 32;

	//-------------------------------------
	// constructor
	Grid(int w, int h);
	//-------------------------------------
	// destructor
	virtual ~Grid();
	//-------------------------------------

	GridEntity* GetGObject(int x, int y) const;
	bool SetGObject(int x, int y, GridEntity* o);

	bool IsInGrid(int x, int y) const;
	bool IsFlagRaised(int x, int y, GridEntity::CollFlag) const;

private:
	std::vector<std::vector<GridEntity*>> m_Grid;

	Grid(const Grid&);
	Grid& operator=(const Grid&);
};

#endif // H_GRID
