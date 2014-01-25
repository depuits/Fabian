#ifndef FABIAN_CSERVICEGAME_H_
#define FABIAN_CSERVICEGAME_H_

#include <CServiceBase.hpp>
#include <string>

// --forward declarations--
class IInput;
class IRenderer;
class IContentManager;

class CGameObject;
// ------------------------


//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CServiceTestApp : public CServiceBase
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service
	//            ( the lower the higher the priorety )
	CServiceTestApp();
	//-------------------------------------
	// Destructor
	virtual ~CServiceTestApp();
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

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceTestApp);
};

#endif //FABIAN_CSERVICEGAME_H_
