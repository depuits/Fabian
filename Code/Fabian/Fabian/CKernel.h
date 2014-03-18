#ifndef FABIAN_CKERNEL_H_
#define FABIAN_CKERNEL_H_

#include "IKernel.h"
#include <list>
#include "CLibraryLoader.h"

////////////////////////////////////////////
//! Struct ServiceData: 
//! holds extra information about the services
//!    used by the CKernel
////////////////////////////////////////////
typedef struct ServiceData
{
	/// ID of the library used for loading the IService
	int LibId;
	/// Pointer to the actual IService
	IService* pService;
	/// Determines if the IService be destroyed
	bool bCanKill;
	/// The priority of the IService
	int iPriority;
} ServiceData;

////////////////////////////////////////////
//! Class CKernel: 
//! the kernel class is the heart of the engine.
//! This class manages all services and the messaging between them
////////////////////////////////////////////
class CKernel : public IKernel
{
public:
	/************************************/
	/*! Singleton accessor 
	 * @return Pointer to CKernel singleton object
	 */
	static CKernel& Get();
	/************************************/
	/*! Destructor */
	virtual ~CKernel();
	/************************************/

	/************************************/
	/*! Start running the engine,
	 *    should be called after the base services are added
	 * @return 0
	 */
	virtual int Execute();
	/************************************/

	/************************************/
	/*! Loads a new IService into the kernel from a library
	 * @param [in] sLib		- Lib file from which to load the service
	 * @param [in] sService - Name of the service to load (one lib can contain multiple services)
	 * @param [in] iPrior 	- The priority of this service
	 * @return Pointer to the service on success and a nullptr when it fails
	 */
	virtual IService* AddService(const char* sLib, const char* sService, int iPrior);
	/************************************/
	/*! Marks a service to be removed, the service
	 *    will be deleted next loop
	 * @param [in] s - A pointer to the service to remove
	 */
	virtual void RemoveService(IService* s);
	/************************************/

	/************************************/
	/*! Mark all services to be removed
	 * @remark This will also end the application
	 */
	virtual void KillAllServices();
	/************************************/

	/************************************/
	/*! Send a message to the services
	 *    (including the service who sends it)
	 * @param [in] msg - Pointer to SMsg object
	 */
	virtual void SendMessage(SMsg* msg);
	/************************************/

private:
	/************************************/
	/*! Constructor */
	CKernel();
	/************************************/

	std::list<ServiceData> m_pServiceList;
	CLibraryLoader m_LibLoader;

	DISALLOW_COPY_AND_ASSIGN(CKernel);
};

#endif //FABIAN_CKERNEL_H_
