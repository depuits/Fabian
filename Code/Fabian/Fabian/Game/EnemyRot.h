#ifndef H_ENEMYROT
#define H_ENEMYROT

#include "Enemy.h"

class EnemyRot : public Enemy
{
public:
	enum RD
	{
		CW			= 0x00, //clockwise
		CCW			= 0x01, // counter clockwise
	};

	//-------------------------------------
	// constructor
	// p1 in - level pointer
	// p2 in - init dir, needs to be 1
	// p3 in - RD value
	EnemyRot(const glm::vec2&, char = CW);
	//-------------------------------------
	// destructor
	virtual ~EnemyRot();
	//-------------------------------------
		
	virtual void EnemyMovement(float);

protected:
	glm::vec2 m_Movement;
	char m_RDValue;

	DISALLOW_COPY_AND_ASSIGN(EnemyRot);
};

#endif // H_ENEMYROT