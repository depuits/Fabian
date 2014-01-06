#ifndef FABIAN_CSERVICEGAME_H_
#define FABIAN_CSERVICEGAME_H_

#include "IService.h"
#include <string>

// --forward declarations--
class IInput;
class IRenderer;
class CContentManager;

class Grid;
class GridEntity;
class IComponent;
class CGameObject;
// ------------------------

FDISABLE_WARNING_START(4201)
//#define GLM_SWIZZLE <- can be used for vec4.xyz() method
#include <glm/glm.hpp>
FDISABLE_WARNING_END(4201)

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CServiceGame : public IService
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service
	//            ( the lower the higher the priorety )
	CServiceGame(int priorety = 500);
	//-------------------------------------
	// Destructor
	virtual ~CServiceGame();
	//-------------------------------------

	//-------------------------------------
	// Called when the service is registered in the kernel
	// rv - return true on succes,
	//         when false is returned then the service gets deleted
	virtual bool Start();
	void LoadLevel(const std::string&);
	//-------------------------------------
	// Called every time the service has to update
	virtual void Update();
	//-------------------------------------
	// Called when the service will be deleted
	virtual void Stop();
	//-------------------------------------

	//-------------------------------------
	// Called when there are messages send somewhere
	// p1 in - pointer to SMsg object
	virtual void MsgProc(SMsg*);
	//-------------------------------------

	//-------------------------------------
	// Function used for timer callback
	// p1 in - float, delta time
	static void TimerCallback(float);
	//-------------------------------------

protected:
	CGameObject *AddGridEntity(Grid*, glm::vec2&, GridEntity*, IComponent*);

	IInput *m_pInput;
	IRenderer *m_pRenderer;
	CContentManager *m_pContent;
	static float s_fDtime;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceGame);
};

#endif //FABIAN_CSERVICEGAME_H_
