#ifndef FABIAN_CSERVICEBASE_H_
#define FABIAN_CSERVICEBASE_H_

#include "IService.h"

////////////////////////////////////////////
//! Class CServiceBase: 
//! base service class with default simple implementation
////////////////////////////////////////////
class CServiceBase : public IService
{
public:
	/************************************/
	/*! Constructor */
	CServiceBase()
		:IService()
	{
	};
	/************************************/
	/*! Destructor */
	virtual ~CServiceBase() { };
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
	virtual void MsgProc(SMsg*) { };
	/************************************/

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceBase);
};

#endif //FABIAN_CSERVICEBASE_H_
