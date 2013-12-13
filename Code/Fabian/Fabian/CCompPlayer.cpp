#include "CCompPlayer.h"

#include "CGameObject.h"

//******************************************
// Interface IObject:
// the base for all drawable or/and updateable objects
// for the game. This includes a transfrom variable to
// move the object arround.
//******************************************

//-------------------------------------
// Constructor
// p1 in* - pointer to parent object, this causes
//            the obbject to be linked to the parent
CCompPlayer::CCompPlayer()
	:IComponent()
{
}
//-------------------------------------
// Destructor
CCompPlayer::~CCompPlayer()
{
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool CCompPlayer::Start()
{
	return true;
}
//-------------------------------------
// Updates the object according to dTime
// p1 in - float, dTime since last update call
void CCompPlayer::Update(float fDt)
{
	m_pGameObject->Transform()->Rotate( glm::vec3(0,  0.1f * fDt,0) );
}
//-------------------------------------




