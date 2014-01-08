#include "GridEntity.h"


//-------------------------------------
// constructor
GridEntity::GridEntity()
	:IComponent()
	,m_CfCollision(CfVoid)
{
}
//-------------------------------------
// destructor
GridEntity::~GridEntity()
{
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool GridEntity::Start()
{
	return true;
}
//-------------------------------------
// is called each time the app ticks
// p1 in - dTime ( time passed in game )
void GridEntity::Update(float)
{
}
//-------------------------------------

	
GridEntity::CollFlag GridEntity::GetCollisionFlags() const
{
	return  m_CfCollision;
}
void GridEntity::SetCollisionFlags(GridEntity::CollFlag cf)
{
	m_CfCollision = cf;
}
	
//-------------------------------------
// is called each tick an entity is on this gridentity
// p1 in - Entity standing here
void GridEntity::Collision(Entity*)
{
}
//-------------------------------------
