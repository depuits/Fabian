#include "Floor.h"
	
//-------------------------------------
// constructor
Floor::Floor()
	:GridEntity()
{
	SetCollisionFlags(CollFlag::CfGround);
}
//-------------------------------------
// destructor
Floor::~Floor()
{
}
//-------------------------------------



