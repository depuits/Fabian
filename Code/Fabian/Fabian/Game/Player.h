#ifndef H_PLAYER
#define H_PLAYER

#include "Entity.h"

class IInput;

class Player : public Entity
{
public:
	//-------------------------------------
	// constructor
	Player();
	//-------------------------------------
	// destructor
	virtual ~Player();
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

	virtual void Die();

protected:
	IInput *m_pInput;
	CGameObject *m_pCamera;

	DISALLOW_COPY_AND_ASSIGN(Player);
};

#endif // H_PLAYER