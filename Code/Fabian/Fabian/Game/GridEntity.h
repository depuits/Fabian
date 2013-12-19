#ifndef H_GRIDENTITY
#define H_GRIDENTITY

#include "../IComponent.h"
class Entity;

class GridEntity : public IComponent
{
public:
	
	enum CollFlag {
		CfVoid			= 0x00,
		CfSolid			= 0x01,
		CfGround		= 0x02,
		CfWater			= 0x04,
		/*OpVertexShader	= 0x08,
		OpFullscreen	= 0x10,
		OpDaylight		= 0x20,*/
	};

	//-------------------------------------
	// constructor
	GridEntity();
	//-------------------------------------
	// destructor
	virtual ~GridEntity();
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

	CollFlag GetCollisionFlags() const;
	void SetCollisionFlags(CollFlag);
	
	//-------------------------------------
	// is called each tick an entity is on this gridentity
	// p1 in - Entity standing here
	virtual void Collision(Entity*);
	//-------------------------------------

protected:
	CollFlag m_CfCollision;

	DISALLOW_COPY_AND_ASSIGN(GridEntity);
};

#endif // H_GRIDENTITY