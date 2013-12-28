#include "Candy.h"
#include "../CGameObject.h"
#include "../CCompModel.h"

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
        m_pGameObject->GetComponentOfType<CCompModel>()->Disable();
		m_bGathered = true;
		--s_CandyCount;
	}
}
//-------------------------------------

void Candy::Reset()
{
    if( m_bGathered)
    {
        m_bGathered = false;
        ++s_CandyCount;
        m_pGameObject->GetComponentOfType<CCompModel>()->Enable();
    }
}

unsigned Candy::CandyLeft()
{
	return s_CandyCount;
}
