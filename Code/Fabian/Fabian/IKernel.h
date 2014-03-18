#ifndef FABIAN_IKERNEL_H_
#define FABIAN_IKERNEL_H_

#include "FabianDef.h"
#include "ServiceMsg.h"

// --forward declarations--
class IService;
// ------------------------

////////////////////////////////////////////
//! Interface IKernel: 
//! the kernel class is the heart of the engine. 
//! This class manages all services and the messaging between them. 
//! This is the interface created for usability from dll's
////////////////////////////////////////////
class IKernel
{
public:
	/************************************/
	/*! Constructor */
	IKernel() { }
	/************************************/
	/*! Destructor */
	virtual ~IKernel() { }
	/************************************/

	/************************************/
	/*! Start running the engine,
	 *    should be called after the base services are added
	 * @return 0
	 */
	virtual int Execute() = 0;
	/************************************/

	/************************************/
	/*! Loads a new IService into the kernel from a library
	 * @param [in] sLib		- Lib file from which to load the service
	 * @param [in] sService - Name of the service to load (one lib can contain multiple services)
	 * @param [in] iPrior 	- The priority of this service
	 * @return Pointer to the service on success and a nullptr when it fails
	 */
	virtual IService* AddService(const char*, const char*, int) = 0;
	/************************************/
	/*! Marks a service to be removed, the service
	 *    will be deleted next loop
	 * @param [in] s - A pointer to the service to remove
	 */
	virtual void RemoveService(IService*) = 0;
	/************************************/

	/************************************/
	/*! Mark all services to be removed
	 * @remark This will also end the application
	 */
	virtual void KillAllServices() = 0;
	/************************************/

	/************************************/
	/*! Send a message to the services
	 *    (including the service who sends it)
	 * @param [in] msg - Pointer to SMsg object
	 */
	virtual void SendMessage(SMsg*) = 0;
	/************************************/

private:

	DISALLOW_COPY_AND_ASSIGN(IKernel);
};

#endif //FABIAN_IKERNEL_H_
