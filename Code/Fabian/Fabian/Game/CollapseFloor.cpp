#include "CollapseFloor.h"

#include "Grid.h"
#include "../CGameObject.h"

//-------------------------------------
// constructor
CollapseFloor::CollapseFloor(int pt)
	:GridEntity()
	,m_PassTimes(pt)
	,m_PassTimesOri(pt)
	,m_pNowOn(nullptr)
	,m_pLastOn(nullptr)
{
	SetCollisionFlags(CollFlag::CfGround);
}
//-------------------------------------
// destructor
CollapseFloor::~CollapseFloor()
{
}
//-------------------------------------

//-------------------------------------
// is called each time the app ticks
// p1 in - dTime ( time passed in game )
// p2 in - the grid position of the object
void CollapseFloor::Update(float)
{
	if( m_pLastOn != m_pNowOn && m_pNowOn == nullptr )
		--m_PassTimes;

	m_pLastOn = m_pNowOn;
	m_pNowOn = nullptr;

	if( m_PassTimes <= 0 )
	{
        m_pGameObject->Transform()->SetScale(0);
		SetCollisionFlags(CollFlag::CfVoid);
    }
}
//-------------------------------------

//-------------------------------------
// is called each tick an entity is on this gridentity
// p1 in - Entity standing here
void CollapseFloor::Collision(Entity* e)
{
	m_pNowOn = e;
}
//-------------------------------------

void CollapseFloor::Reset()
{
	m_PassTimes =m_PassTimesOri;
	m_pNowOn = nullptr;
	m_pLastOn = nullptr;

	m_pGameObject->Transform()->SetScale(Grid::SCALE / 2);
    SetCollisionFlags(CollFlag::CfGround);
}

