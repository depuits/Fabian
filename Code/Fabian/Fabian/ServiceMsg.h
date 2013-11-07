#ifndef FABIAN_ServiceMsg_H_
#define FABIAN_ServiceMsg_H_

#include "FabianDef.h"

#define SM_INVALID				-1
#define SM_QUIT					 0

#define SM_TIMER_DT				10

#define SM_H_DEFAULT			 0
#define SM_H_REQUEST			 1
#define SM_H_RECEIVE			 2
#define SM_H_REMOVE				 3

#define SM_INPUT				20
#define SM_RENDERER				40


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
		FASSERTR( dynamic_cast<T>(sm) == static_cast<T>(sm) );
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

	const float dt;
};

class IInput;
struct SMsgInput : public SMsg
{
	SMsgInput(IInput* ppInput, int r)
		:SMsg(SM_INPUT + r)
		,pInput(ppInput)
	{
	}
	DISALLOW_COPY_AND_ASSIGN(SMsgInput);

	IInput* pInput;
};

class IRenderer;
struct SMsgRenderer : public SMsg
{
	SMsgRenderer(IRenderer* ppRenderer, int r)
		:SMsg(SM_RENDERER + r)
		,pRenderer(ppRenderer)
	{
	}
	DISALLOW_COPY_AND_ASSIGN(SMsgRenderer);

	IRenderer* pRenderer;
};



#endif //FABIAN_ServiceMsg_H_