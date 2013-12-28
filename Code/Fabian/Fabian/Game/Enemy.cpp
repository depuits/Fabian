#include "Enemy.h"

#include "../CGlobalAccessor.h"
#include "../CLog.h"

//-------------------------------------
// constructor
Enemy::Enemy()
	:Entity()
{
}
//-------------------------------------
// destructor
Enemy::~Enemy()
{
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool Enemy::Start()
{
	m_pPlayer = static_cast<Entity*>(CGlobalAccessor::Get().GetObject("Player"));
	return Entity::Start();
}
//-------------------------------------
// is called each time the app ticks
// p1 in - dTime ( time passed in game )
// rv - returns true if no more actions should be done
void Enemy::Update(float dt)
{
	Entity::Update(dt);

	//check if there is collision with the player and kill him
	glm::vec2 pp;
	m_pPlayer->GetPos(pp);

	if( glm::distance(pp, m_Pos) < 24)
		m_pPlayer->Die();
}
void Enemy::DerivedUpdate(float dt)
{
	EnemyMovement(dt);
}
//-------------------------------------

void Enemy::Die()
{
	//delete the enemy instead of the default respawn behavior
	CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_CLIENT, "Enemy destroying not implemented yet (respawning for now)");
	Entity::Die();
}

