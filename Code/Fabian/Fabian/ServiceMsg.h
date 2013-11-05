#ifndef FABIAN_ServiceMsg_H_
#define FABIAN_ServiceMsg_H_

#include "FabianDef.h"
#include <SDL_assert.h>

#define SM_INVALID			-1
#define SM_QUIT				 0

#define SM_TIMER_DT			10

#define SM_INPUT			20
#define SM_INPUT_REQUEST	21


typedef struct SMsg
{
	SMsg( int pId = SM_INVALID )
		:id(pId)
	{
	}
	virtual ~SMsg() { }
	DISALLOW_COPY_AND_ASSIGN(SMsg);

	const int id;

	template <class T>
	inline static T Cast(SMsg* sm)
	{
		SDL_assert_release( dynamic_cast<T>(sm) == static_cast<T>(sm) );
		return static_cast<T>(sm);
	}

} SMsg;


struct SMsgQuit : public SMsg
{
	SMsgQuit()
		:SMsg(SM_QUIT)
	{
	}
	DISALLOW_COPY_AND_ASSIGN(SMsgQuit);
};

struct SMsgTimerDT : public SMsg
{
	SMsgTimerDT(float pDt)
		:SMsg(SM_TIMER_DT)
		,dt(pDt)
	{
	}
	DISALLOW_COPY_AND_ASSIGN(SMsgTimerDT);

	float dt;
};

class IInput;
struct SMsgInput : public SMsg
{
	SMsgInput(IInput* ppInput)
		:SMsg(SM_INPUT)
		,pInput(ppInput)
	{
	}
	DISALLOW_COPY_AND_ASSIGN(SMsgInput);

	IInput* pInput;
};



#endif //FABIAN_ServiceMsg_H_