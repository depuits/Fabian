#ifndef H_COLLAPSEFLOOR
#define H_COLLAPSEFLOOR

#include "GridEntity.h"

class CollapseFloor : public GridEntity
{
public:

	//-------------------------------------
	// constructor
	// p1 in - level pointer
	// p2 in - number of times an entity can pass
	CollapseFloor(int = 3);
	//-------------------------------------
	// destructor
	virtual ~CollapseFloor();
	//-------------------------------------

	//-------------------------------------
	// Updates the object according to dTime
	// p1 in - float, dTime since last update call
	virtual void Update(float);
	//-------------------------------------

	//-------------------------------------
	// is called each tick an entity is on this gridentity
	// p1 in - Entity standing here
	virtual void Collision(Entity*);
	//-------------------------------------

	virtual void Reset();

protected:
	int m_PassTimes;

	Entity* m_pNowOn, *m_pLastOn;

	DISALLOW_COPY_AND_ASSIGN(CollapseFloor);
};

#endif //H_COLLAPSEFLOOR
