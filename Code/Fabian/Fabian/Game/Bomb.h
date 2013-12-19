#ifndef H_BOMB
#define H_BOMB

#include "Floor.h"

class Bomb : public Floor
{
public:
	
	//-------------------------------------
	// constructor
	Bomb();
	//-------------------------------------
	// destructor
	virtual ~Bomb();
	//-------------------------------------

	//-------------------------------------
	// is called each tick an entity is on this gridentity
	// p1 in - Entity standing here
	virtual void Collision(Entity*);
	//-------------------------------------

protected:
	bool m_bBlown;
	DISALLOW_COPY_AND_ASSIGN(Bomb);
};

#endif //H_BOMB
