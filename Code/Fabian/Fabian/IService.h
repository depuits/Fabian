#ifndef FABIAN_ISERVICE_H_
#define FABIAN_ISERVICE_H_

#include "FabianDef.h"
#include "ServiceMsg.h"

////////////////////////////////////////////
//! Interface IService: 
//! the interface for all service, used to define
//! parts of the game
//! ex.: rendering, input, physics, AI, ...
////////////////////////////////////////////
class IService
{
public:
	/************************************/
	/*! Constructor */
	IService() { };
	/************************************/
	/*! Destructor */
	virtual ~IService() { };
	/************************************/
	
	/************************************/
	/*! Called when the service is registered in the kernel
	 * @return True on success
	 * @warning When this fails then the service gets removed
	 */
	virtual bool Start() = 0;
	/************************************/
	/*! @deprecated Called when the service is suspended */
	virtual void OnSuspend() { };
	/************************************/
	/*! Called every time the service has to update */
	virtual void Update() = 0;
	/************************************/
	/*! @deprecated Called when the service returns from being suspended */
	virtual void OnResume() { };
	/************************************/
	/*! Called when the service will be deleted */
	virtual void Stop() = 0;
	/************************************/
	
	/************************************/
	/*! Called when there are messages send somewhere
	 * @param [in] msg - Pointer to SMsg object
	 */
	virtual void MsgProc(SMsg* msg) { };
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(IService);
};

#endif //FABIAN_ISERVICE_H_
