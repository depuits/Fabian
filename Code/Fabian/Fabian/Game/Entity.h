#ifndef H_ENTITY
#define H_ENTITY

#include "../IComponent.h"

#pragma warning( push )
#pragma warning( disable: 4201 )
//#define GLM_SWIZZLE <- can be used for vec4.xyz() method
#include <glm/glm.hpp>
#pragma warning( pop )

class Grid;

class Entity : public IComponent
{
public:
	//-------------------------------------
	// constructor
	Entity();
	//-------------------------------------
	// destructor
	virtual ~Entity();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, return false if something failed
	virtual bool Start();
	//-------------------------------------
	// Updates the object according to dTime
	// p1 in - float, dTime since last update call
	virtual void Update(float);
	//-------------------------------------

	virtual void DerivedUpdate(float);

	virtual bool Move(const glm::vec2& dir);
	
	virtual void SetPos(const glm::vec2&);
	virtual void GetPos(glm::vec2&) const;
	virtual void SetGridPos(const glm::vec2&);
	virtual void GetGridPos(glm::vec2&) const;

	virtual void Die();
	
	virtual void SetRespawn(const glm::vec2&);

protected:
	virtual bool DoMovement(float);

	Grid* m_pGrid;
	
	glm::vec2 m_Pos,
					m_PosOld,
					m_MoveDir,
					m_Respawn;
	int m_Speed;

	DISALLOW_COPY_AND_ASSIGN(Entity);
};

#endif // H_ENTITY