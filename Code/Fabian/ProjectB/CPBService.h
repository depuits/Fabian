#ifndef PROJECTB_CPBSERVICE_H_
#define PROJECTB_CPBSERVICE_H_

#include <CServiceBase.hpp>

// --forward declarations--
class IInput;
class IRenderer;
class IContentManager;

class CPBPlayer;
class CPBCamera;
// ------------------------

FDISABLE_WARNING_START(4201)
//#define GLM_SWIZZLE <- can be used for vec4.xyz() method
#include "glm/glm.hpp"
FDISABLE_WARNING_END(4201)

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CPBService : public CServiceBase
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service
	//            ( the lower the higher the priorety )
	CPBService();
	//-------------------------------------
	// Destructor
	virtual ~CPBService();
	//-------------------------------------

	//-------------------------------------
	// Called when the service is registered in the kernel
	// rv - return true on succes,
	//         when false is returned then the service gets deleted
	virtual bool Start();
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
	IInput *m_pInput;
	IRenderer *m_pRenderer;
	IContentManager *m_pContent;
	static float s_fDtime;
	
	CPBPlayer *m_pPlayer;
	CPBCamera *m_pCamera;

private:
	DISALLOW_COPY_AND_ASSIGN(CPBService);
};

#endif //PROJECTB_CPBSERVICE_H_
