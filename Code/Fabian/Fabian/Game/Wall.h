#ifndef H_WALL
#define H_WALL

#include "GridEntity.h"


class Wall : public GridEntity
{
public:
	
	//-------------------------------------
	// constructor
	Wall();
	//-------------------------------------
	// destructor
	virtual ~Wall();
	//-------------------------------------


protected:	
	DISALLOW_COPY_AND_ASSIGN(Wall);
};

#endif //H_WALL
