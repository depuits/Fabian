#include "Water.h"

//-------------------------------------
// constructor
Water::Water()
	:GridEntity()
{
	SetCollisionFlags(CollFlag::CfWater);
}
//-------------------------------------
// destructor
Water::~Water()
{
}
//-------------------------------------

