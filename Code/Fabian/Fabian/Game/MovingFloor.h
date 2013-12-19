#ifndef H_MOVINGFLOOR
#define H_MOVINGFLOOR

#include "GridEntity.h"

class MovingFloor : public GridEntity
{
public:
	
	//-------------------------------------
	// constructor
	// p1 in - level pointer
	// p2 in - speed factor in wihich the floor goes away and returns
	MovingFloor(float = 2.5f);
	//-------------------------------------
	// destructor
	virtual ~MovingFloor();
	//-------------------------------------

	//-------------------------------------
	// is called each time the app ticks
	// p1 in - dTime ( time passed in game )
	// p2 in - the grid position of the object
	virtual void Update(float);
	//-------------------------------------

protected:	
	float m_Currentpos, m_Delay, m_DelayCounter, m_Speed;
	int m_Dir;

	DISALLOW_COPY_AND_ASSIGN(MovingFloor);
};

#endif //H_MOVINGFLOOR
