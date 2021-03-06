#include "Entity.h"

#include "Grid.h"
#include "GridEntity.h"

#include <Fabian.h>

#include <glm/gtx/norm.hpp>

//-------------------------------------
// constructor
Entity::Entity()
	:CCompBase()
	,m_pGrid(nullptr)
	,m_Pos(0, 0)
	,m_PosOld(0, 0)
	,m_MoveDir(0, 0)
	,m_Respawn(0, 0)

	,m_Speed(250)

	,m_fTurnSmoothing(0.15f)
{
}
//-------------------------------------
// destructor
Entity::~Entity()
{
}
//-------------------------------------

//-------------------------------------
// Initializes the object, should be called before any other
//    method of the object.
// rv - bool, return false if something failed
bool Entity::Start()
{
	m_pGrid = static_cast<Grid*>(Fab_GlobalAccessorGetObject("Grid"));
	return true;
}
//-------------------------------------
// is called each time the app ticks
// p1 in - dTime ( time passed in game )
void Entity::Update(float dt)
{
	//update local position to gameobject
	m_pGameObject->Transform()->SetPos(glm::vec3(m_Pos.x, 0, m_Pos.y));

	glm::vec2 gpos;
	GetGridPos(gpos);

	// respawn when on void or water
	if( !m_pGrid->IsFlagRaised((int)gpos.x, (int)gpos.y, GridEntity::CfGround) )
	{
		Die();
		return;
	}

	// notify the tile i'm on
	GridEntity* e = m_pGrid->GetGObject((int)gpos.x, (int)gpos.y);
	if( e != nullptr)
		e->Collision(this);

	// do movement if needed/moving
	if( DoMovement(dt) )
		return;

	DerivedUpdate(dt);
}
void Entity::DerivedUpdate(float)
{
}
//-------------------------------------

bool Entity::Move(const glm::vec2& dir)
{
	int gs = Grid::SCALE;
	m_PosOld = (m_Pos / (float)gs) * (float)gs; // snap old pos to grid so the entity moves on the grid when it got of

	glm::vec2 gpos;
	GetGridPos(gpos);

	// Test high bit - if set, key was down when GetAsyncKeyState was called.
	if( dir.x > 0 )
	{
		if( !m_pGrid->IsFlagRaised((int)gpos.x + 1, (int)gpos.y, GridEntity::CfSolid) )
		{
			m_MoveDir.x = 1;
			return true;
		}
	}
	if( dir.x < 0 )
	{
		if( !m_pGrid->IsFlagRaised((int)gpos.x - 1, (int)gpos.y, GridEntity::CfSolid) )
		{
			m_MoveDir.x = -1;
			return true;
		}
	}
	if( dir.y < 0 )
	{
		if( !m_pGrid->IsFlagRaised((int)gpos.x, (int)gpos.y - 1, GridEntity::CfSolid) )
		{
			m_MoveDir.y = -1;
			return true;
		}
	}
	if( dir.y > 0 )
	{
		if( !m_pGrid->IsFlagRaised((int)gpos.x, (int)gpos.y + 1, GridEntity::CfSolid) )
		{
			m_MoveDir.y = 1;
			return true;
		}
	}

	return false;
}

glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest)
{
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = glm::normalize(rotationAxis);
		return glm::angleAxis(180.0f, rotationAxis);
	}

	rotationAxis = glm::cross(start, dest);

	float s = glm::sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}

bool Entity::DoMovement(float dt)
{
	//when moving check if you moved a square
	if( m_MoveDir != glm::vec2(0, 0) )
	{
        glm::quat tRot = RotationBetweenVectors(glm::vec3(-m_MoveDir.x, 0, m_MoveDir.y), glm::vec3(0, 0, 1));
        glm::quat nRot = glm::mix(m_pGameObject->Transform()->GetRot(), tRot, m_fTurnSmoothing);
        m_pGameObject->Transform()->SetRot(nRot);

		int gs = Grid::SCALE;

		m_Pos += m_MoveDir * (dt * (float)m_Speed);
		if( m_Pos.x >= m_PosOld.x + gs )
		{
			m_MoveDir = glm::vec2(0, 0);
			m_Pos.x = m_PosOld.x + gs;
		}
		else if( m_Pos.x <= m_PosOld.x - gs )
		{
			m_MoveDir = glm::vec2(0, 0);
			m_Pos.x = m_PosOld.x - gs;
		}
		else if( m_Pos.y >= m_PosOld.y + gs )
		{
			m_MoveDir = glm::vec2(0, 0);
			m_Pos.y = m_PosOld.y + gs;
		}
		else if( m_Pos.y <= m_PosOld.y - gs )
		{
			m_MoveDir = glm::vec2(0, 0);
			m_Pos.y = m_PosOld.y - gs;
		}

		return true;
	}

	return false;
}

void Entity::SetPos(const glm::vec2& pos)
{
	m_Pos = pos;
	m_PosOld = pos;
}
void Entity::GetPos(glm::vec2& pos) const
{
	pos = m_Pos;
}
void Entity::SetGridPos(const glm::vec2& pos)
{
	SetPos(pos * (float)Grid::SCALE);
}
void Entity::GetGridPos(glm::vec2& pos) const
{
	pos = m_Pos / (float)Grid::SCALE;
}

void Entity::Die()
{
	m_Pos = m_Respawn;
	m_MoveDir = glm::vec2(0, 0);
}

void Entity::SetRespawn(const glm::vec2& s)
{
	m_Respawn = s * (float)Grid::SCALE;
}
