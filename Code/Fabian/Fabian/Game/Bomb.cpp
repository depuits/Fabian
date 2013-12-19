#include "Bomb.h"

#include "Entity.h"
	
//-------------------------------------
// constructor
Bomb::Bomb()
	:Floor()
	,m_bBlown(false)
{
	SetCollisionFlags(CollFlag::CfGround);
}
//-------------------------------------
// destructor
Bomb::~Bomb()
{
}
//-------------------------------------

//-------------------------------------
// is called each tick an entity is on this gridentity
// p1 in - Entity standing here
void Bomb::Collision(Entity* e)
{
	if(!m_bBlown)
	{
		e->Die();
		m_bBlown = true;
	}
}
//-------------------------------------

