#ifndef H_FLOOR
#define H_FLOOR

#include "GridEntity.h"


class Floor : public GridEntity
{
public:

	//-------------------------------------
	// constructor
	Floor();
	//-------------------------------------
	// destructor
	virtual ~Floor();
	//-------------------------------------

	virtual void Reset();

protected:
	DISALLOW_COPY_AND_ASSIGN(Floor);
};

#endif //H_FLOOR
