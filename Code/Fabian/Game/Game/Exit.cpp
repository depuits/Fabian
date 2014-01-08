#include "Exit.h"
#include "Candy.h"

#include <Fabian.h>

//-------------------------------------
// constructor
Exit::Exit()
	:Floor()
	,m_bFinished(false)
{
	SetCollisionFlags(CollFlag::CfGround);
}
//-------------------------------------
// destructor
Exit::~Exit()
{
}
//-------------------------------------

//-------------------------------------
// is called each tick an entity is on this gridentity
// p1 in - Entity standing here
void Exit::Collision(Entity*)
{
	if( /*m_pLevel->GetPlayer() == e &&*/ Candy::CandyLeft() <= 0 && !m_bFinished)
	{
		// go to next level
		m_bFinished = true;
		Fab_LogWrite(FLOG_LVL_INFO, FLOG_ID_CLIENT | FLOG_ID_USER, "Congratz: You\'ve won");
	}
}
//-------------------------------------

void Exit::Reset()
{
	Floor::Reset();
	m_bFinished = false;
}
