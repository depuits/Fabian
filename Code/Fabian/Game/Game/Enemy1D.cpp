#include "Enemy1D.h"

#include "Grid.h"
#include "GridEntity.h"

//-------------------------------------
// constructor
Enemy1D::Enemy1D(const glm::vec2& mov)
	:Enemy()
	,m_Movement(mov)
{
	m_Speed = 150;
}
//-------------------------------------
// destructor
Enemy1D::~Enemy1D()
{
}
//-------------------------------------

void Enemy1D::EnemyMovement(float)
{
	glm::vec2 gpos;
	GetGridPos(gpos);

	if( m_pGrid->IsFlagRaised((int)(gpos.x + m_Movement.x), (int)(gpos.y + m_Movement.y), GridEntity::CfGround) )
		Move(m_Movement);
	else
		m_Movement *= -1;

}