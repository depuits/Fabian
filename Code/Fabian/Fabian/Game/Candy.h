#ifndef H_CANDY
#define H_CANDY

#include "Floor.h"

class Candy : public Floor
{
public:
	
	//-------------------------------------
	// constructor
	Candy();
	//-------------------------------------
	// destructor
	virtual ~Candy();
	//-------------------------------------

	//-------------------------------------
	// is called each tick an entity is on this gridentity
	// p1 in - Entity standing here
	virtual void Collision(Entity*);
	//-------------------------------------

	static unsigned CandyLeft();

protected:
	static unsigned s_CandyCount;

	bool m_bGathered;

	DISALLOW_COPY_AND_ASSIGN(Candy);
};

#endif //H_CANDY
