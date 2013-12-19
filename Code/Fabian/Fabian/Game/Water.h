#ifndef H_WATER
#define H_WATER

#include "GridEntity.h"


class Water : public GridEntity
{
public:
	
	//-------------------------------------
	// constructor
	Water();
	//-------------------------------------
	// destructor
	virtual ~Water();
	//-------------------------------------

protected:	
	DISALLOW_COPY_AND_ASSIGN(Water);
};

#endif //H_WATER
