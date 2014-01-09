#ifndef FABIAN_CSERVICEINPUT_H_
#define FABIAN_CSERVICEINPUT_H_

#include <CServiceBase.hpp>

class CInputSDL;

//******************************************
// Class CServiceInput:
// service responsable giving the input object
// and for updating it.
//******************************************
class CServiceInput : public CServiceBase
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	CServiceInput(int priorety = 90);
	//-------------------------------------
	// Destructor
	virtual ~CServiceInput();
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

protected:
	CInputSDL *m_pInput;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceInput);
};

#endif //FABIAN_CSERVICEINPUT_H_
