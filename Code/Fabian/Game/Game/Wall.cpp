#include "Wall.h"
	
//-------------------------------------
// constructor
Wall::Wall()
	:GridEntity()
{
	SetCollisionFlags(CollFlag::CfSolid);
}
//-------------------------------------
// destructor
Wall::~Wall()
{
}
//-------------------------------------

void Wall::Reset()
{
}
