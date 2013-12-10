#ifndef FABIAN_ServiceMsg_H_
#define FABIAN_ServiceMsg_H_

#include "FabianDef.h"

// ------------------------
// ---- msg id defines ----
#define SM_INVALID				-1
#define SM_QUIT					 0


#define SM_H_DEFAULT			 0
#define SM_H_REQUEST			 1
#define SM_H_RECEIVE			 2
#define SM_H_REMOVE				 3

#define SM_TIMER				10
#define SM_INPUT				20
#define SM_RENDERER				40
// ------------------------

// --forward declarations--
class IService;
class IInput;
class IRenderer;
// ------------------------

//******************************************
// Struct SMsg:
// the service message struct is used to send messages
//    through services.
//    Derived structs can be used for extra parameters
//******************************************
typedef struct SMsg
{
	//-------------------------------------
	// constructor
	// p1 in - int, the id of the message
	//            used to define what your getting
	SMsg( int pId = SM_INVALID )
		:id(pId)
	{
	}
	//-------------------------------------
	// Destructor
	virtual ~SMsg() { }
	//-------------------------------------
	DISALLOW_COPY_AND_ASSIGN(SMsg);

	const int id;
	
	//-------------------------------------
	// Template method for casting SMsg's
	template <class T>
	inline static T Cast(SMsg* sm)
	{
		FASSERTR( dynamic_cast<T>(sm) == static_cast<T>(sm) );
		return static_cast<T>(sm);
	}
	//-------------------------------------

} SMsg;

//******************************************
// Derived Struct SMsg:
// structs derived from SMsg for extra info
//******************************************
struct SMsgRequest : public SMsg
{
	SMsgRequest(int id, IService *pServ)
		:SMsg(id + SM_H_REQUEST)
		,pService(pServ)
	{
	}
	//-------------------------------------
	DISALLOW_COPY_AND_ASSIGN(SMsgRequest);

	IService *pService;
};

struct SMsgTimer : public SMsg
{
	SMsgTimer( void (*pCallFunc)(float) )
		:SMsg(SM_TIMER)
		,pCallbackFunc(pCallFunc)
	{
	}
	//-------------------------------------
	DISALLOW_COPY_AND_ASSIGN(SMsgTimer);

	void (*pCallbackFunc)(float);
};

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