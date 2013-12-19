#include "Candy.h"

unsigned Candy::s_CandyCount = 0;

//-------------------------------------
// constructor
Candy::Candy()
	:Floor()
	,m_bGathered(false)
{
	SetCollisionFlags(CollFlag::CfGround);
	++s_CandyCount;
}
//-------------------------------------
// destructor
Candy::~Candy()
{
}
//-------------------------------------


//-------------------------------------
// is called each tick an entity is on this gridentity
// p1 in - Entity standing here
void Candy::Collision(Entity*)
{
	if( !m_bGathered )
	{
		m_bGathered = true;
		--s_CandyCount;
	}
}
//-------------------------------------

unsigned Candy::CandyLeft()
{
	return s_CandyCount;
}