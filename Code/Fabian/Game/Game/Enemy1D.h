#ifndef H_ENEMY1D
#define H_ENEMY1D

#include "Enemy.h"

class Enemy1D : public Enemy
{
public:
	//-------------------------------------
	// constructor
	// p1 in - level pointer
	// p2 in - init dir, the enemy will move allong the defined init dir
	Enemy1D(const glm::vec2&);
	//-------------------------------------
	// destructor
	virtual ~Enemy1D();
	//-------------------------------------
	
	virtual void EnemyMovement(float);

protected:
	glm::vec2 m_Movement;

	DISALLOW_COPY_AND_ASSIGN(Enemy1D);
};

#endif // H_ENEMY1D