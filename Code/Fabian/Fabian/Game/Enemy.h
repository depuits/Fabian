#ifndef H_ENEMY
#define H_ENEMY

#include "Entity.h"

class Enemy : public Entity
{
public:
	//-------------------------------------
	// constructor
	Enemy();
	//-------------------------------------
	// destructor
	virtual ~Enemy();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, return false if something failed
	virtual bool Start();
	//-------------------------------------
	// is called each time the app ticks
	// p1 in - dTime ( time passed in game )
	// rv - returns true if no more actions should be done
	virtual void Update(float);
	virtual void DerivedUpdate(float);
	//-------------------------------------

	virtual void EnemyMovement(float) = 0;

	virtual void Die();

protected:
	Entity *m_pPlayer;

	DISALLOW_COPY_AND_ASSIGN(Enemy);
};

#endif // H_ENEMY