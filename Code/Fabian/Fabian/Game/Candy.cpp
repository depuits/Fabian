#include "Candy.h"
#include "../CGameObject.h"
#include "../CCompModel.h"

unsigned Candy::s_CandyCount = 0;

//-------------------------------------
// constructor
Candy::Candy()
	:Floor()
	,m_bGathered(false)
	,m_pMesh(nullptr)
{
	SetCollisionFlags(CollFlag::CfGround);
	++s_CandyCount;
}
//-------------------------------------
// destructor
Candy::~Candy()
{
}
//-------------------------------------

bool Candy::Start()
{
	if(!Floor::Start())
		return false;

	// this gives the candy mesh rather then the floor mesh because its the only CompModel on the gameobject
	//    when this component is added
	m_pMesh = m_pGameObject->GetComponentOfType<CCompModel>();
	return (m_pMesh != nullptr);
}

//-------------------------------------
// is called each tick an entity is on this gridentity
// p1 in - Entity standing here
void Candy::Collision(Entity*)
{
	if( !m_bGathered )
	{
        m_pMesh->Disable();
		m_bGathered = true;
		--s_CandyCount;
	}
}
//-------------------------------------

void Candy::Reset()
{
    if(m_bGathered)
    {
        m_bGathered = false;
        ++s_CandyCount;
		m_pMesh->Enable();
    }
}

unsigned Candy::CandyLeft()
{
	return s_CandyCount;
}
