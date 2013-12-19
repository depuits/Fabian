#include "EnemyRot.h"

#include "Grid.h"
#include "GridEntity.h"

//-------------------------------------
// constructor
EnemyRot::EnemyRot(const glm::vec2& mov, char RD)
	:Enemy()
	,m_Movement(mov)
	,m_RDValue(RD)
{
	m_Speed = 150;
}
//-------------------------------------
// destructor
EnemyRot::~EnemyRot()
{
}
//-------------------------------------

	#define VECTOR2IUP		glm::vec2( 0, -1)
	#define VECTOR2IDOWN	glm::vec2( 0,  1)
	#define VECTOR2ILEFT	glm::vec2(-1,  0)
	#define VECTOR2IRIGHT	glm::vec2( 1,  0)


void EnemyRot::EnemyMovement(float)
{
	glm::vec2 gpos;
	GetGridPos(gpos);

	if( m_pGrid->IsFlagRaised(gpos.x + m_Movement.x, gpos.y + m_Movement.y, GridEntity::CfGround) )
		Move(m_Movement);
	else // rotate CW or CCW
	{
		switch(m_RDValue)
		{
		case CW:
			if( m_Movement == VECTOR2IUP )
				m_Movement = VECTOR2IRIGHT;
			else if( m_Movement == VECTOR2IRIGHT )
				m_Movement = VECTOR2IDOWN;
			else if( m_Movement == VECTOR2IDOWN )
				m_Movement = VECTOR2ILEFT;
			else if( m_Movement == VECTOR2ILEFT )
				m_Movement = VECTOR2IUP;
			break;
		case CCW:
			if( m_Movement == VECTOR2IUP )
				m_Movement = VECTOR2ILEFT;
			else if( m_Movement == VECTOR2ILEFT )
				m_Movement = VECTOR2IDOWN;
			else if( m_Movement == VECTOR2IDOWN )
				m_Movement = VECTOR2IRIGHT;
			else if( m_Movement == VECTOR2IRIGHT )
				m_Movement = VECTOR2IUP;
			break;
		}
	}

}