#include "Player.h"

#include "Grid.h"
#include "GridEntity.h"

#include "../IInput.h"
#include "../CGameObject.h"
#include "../CGlobalAccessor.h"

//-------------------------------------
// constructor
Player::Player()
	:Entity()
	,m_pInput(nullptr)
	,m_pCamera(nullptr)
{
	m_Speed = 300;
}
//-------------------------------------
// destructor
Player::~Player()
{
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool Player::Start()
{
	m_pInput = static_cast<IInput*>(CGlobalAccessor::Get().GetObject("Input"));
	m_pCamera = static_cast<CGameObject*>(CGlobalAccessor::Get().GetObject("Camera"));
	return Entity::Start();
}
//-------------------------------------
// is called each time the app ticks
// p1 in - dTime ( time passed in game )
// rv - returns true if no more actions should be done
void Player::Update(float dt)
{
	Entity::Update(dt);
	//update camera position
	glm::vec3 pos, tpos;
	tpos = glm::vec3(m_Pos.x, 10 * Grid::SCALE, m_Pos.y);
	pos = m_pCamera->Transform()->GetPos();
	m_pCamera->Transform()->SetPos( pos + (tpos - pos) * 0.1f ); // using lerp
}
void Player::DerivedUpdate(float)
{
	//if not moving check if the move button is pressed
	// Test high bit - if set, key was down when GetAsyncKeyState was called.
	if( m_pInput->GetKeyState(FKEY_RIGHT) & DOWN )
	{
		if( Move(glm::vec2(1, 0)) )
			return;
	}
	else if( m_pInput->GetKeyState(FKEY_LEFT) & DOWN )
	{
		if( Move(glm::vec2(-1, 0)) )
			return;
	}

	if( m_pInput->GetKeyState(FKEY_UP) & DOWN )
	{
		if( Move(glm::vec2(0, -1)) )
			return;
	}
	else if( m_pInput->GetKeyState(FKEY_DOWN) & DOWN )
	{
		if( Move(glm::vec2(0, 1)) )
			return;
	}
}
//-------------------------------------

void Player::Die()
{
	Entity::Die();
	m_pGrid->Reset();
}


