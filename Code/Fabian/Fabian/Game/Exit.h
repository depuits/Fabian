#ifndef H_EXIT
#define H_EXIT

#include "Floor.h"


class Exit : public Floor
{
public:
	
	//-------------------------------------
	// constructor
	Exit();
	//-------------------------------------
	// destructor
	virtual ~Exit();
	//-------------------------------------

	//-------------------------------------
	// is called each tick an entity is on this gridentity
	// p1 in - Entity standing here
	virtual void Collision(Entity*);
	//-------------------------------------

protected:	
	bool m_bFinished;
	DISALLOW_COPY_AND_ASSIGN(Exit);
};

#endif //H_EXIT
