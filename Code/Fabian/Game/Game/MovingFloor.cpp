#include "MovingFloor.h"

#include "Grid.h"

//-------------------------------------
// constructor
MovingFloor::MovingFloor(float s)
	:GridEntity()
	,m_Currentpos(1)
	,m_Delay(0.6f)
	,m_DelayCounter(0)
	,m_Speed(s)
	,m_Dir(-1)
{
	SetCollisionFlags(CollFlag::CfGround);
}
//-------------------------------------
// destructor
MovingFloor::~MovingFloor()
{
}
//-------------------------------------

//-------------------------------------
// is called each time the app ticks
// p1 in - dTime ( time passed in game )
// p2 in - the grid position of the object
void MovingFloor::Update(float dt)
{
	if(m_DelayCounter == 0)
	{
		m_Currentpos += dt * m_Dir * m_Speed;

		if( (m_Currentpos >= 1 && m_Dir > 0) || (m_Currentpos <= 0 && m_Dir < 0) )
			m_DelayCounter = m_Delay;

		m_Currentpos = glm::clamp<float>(m_Currentpos, 0, 1);
		m_pGameObject->Transform()->SetScale(m_Currentpos/2 * Grid::SCALE);
	}
	else
	{
		m_DelayCounter -= dt;
		if( m_DelayCounter <= 0 )
		{
			m_DelayCounter = 0;
			m_Dir *= -1;
		}
	}

	if( m_Currentpos < 0.8f )
		SetCollisionFlags(CollFlag::CfVoid);
	else
		SetCollisionFlags(CollFlag::CfGround);

	// need code to visualy move te ground up and down
}
//-------------------------------------

void MovingFloor::Reset()
{
	m_Currentpos = 1;
	m_DelayCounter = 0;
	m_Dir = -1;

	SetCollisionFlags(CollFlag::CfGround);
}

