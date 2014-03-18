/**
	@mainpage Fabian
**/

#ifndef FABIAN_FABIAN_H_
#define FABIAN_FABIAN_H_

/** @file */ 
/*! @addtogroup Fabian
 * All methods exposed to use in your application from the dll.
 * @{ 
 */

#include "FabianDef.h"

#include "LogDef.h"
#include "ServiceMsg.h"

extern "C"
{	
	class ILogger;
	/************************************/
	/// @{
	/*! Creates ILogger object used for logging
	 * @return Pointer to ILogger object
	 */
	DECLDIR ILogger* Fab_LoggerCreateToFiles(bool bAppendFile = false);
	DECLDIR ILogger* Fab_LoggerCreateToConsole(bool bBreakOnError = true);
	DECLDIR ILogger* Fab_LoggerCreateToMultiple();
	/// @}
	/************************************/
	/*! Adds an ILogger object to a multiple logger object
	 * @param [in] pLoggerMulti - Pointer to the multi logger object
	 * @param [in] pLogger - Pointer to ILogger object to add
	 */
	DECLDIR void Fab_LoggerMultipleAddLogger(ILogger* pLoggerMulti, ILogger* pLogger);
	/************************************/
	/*! Assign a logger used to do the actual logging
	 * @param [in] pLogger - Pointer to ILogger object (takes over ownership)
	 * @return True when successfully assigned
	 */
	DECLDIR bool Fab_LogAssignLogger(ILogger* pLogger);
	/************************************/
	/*! Write an message to the log
	 * @param [in] lvl 	- FLOG_LVL, useally ERROR, WARNING or INFO
	 * @param [in] id	- FLOG_ID, the place where to write to
	 * @param [in] msg	- Log message
	 * @param [in] ... - Extra parameters, see sprintf
	 */
	DECLDIR void Fab_LogWrite(char lvl, char id, const char* msg, ...);
	/************************************/
	
	class IKernel;
	class IService;
	/************************************/
	/*! Get the kernel from this dll
	 * @return Pointer to the IKernel
	 */
	DECLDIR IKernel* Fab_GetKernel();
	/************************************/
	/*! Start running the engine, 
	 *    should be called after the base services are added
	 * @return 0
	 */
	DECLDIR int Fab_KernelExecute();
	/************************************/
	/*! Adds a service to the kernel and takes ownership of it
	 * @param [in] sLib		- Lib file from which to load the service
	 * @param [in] sService - Name of the service to load (one lib can contain multiple services)
	 * @param [in] iPrior 	- The priority of this service
	 * @return Pointer to the IService on succes and a nullptr when it fails
	 */
	DECLDIR IService* Fab_KernelAddService(const char* sLib, const char* sService, int iPrior);
	/************************************/
	/*! Marks a service to be removed, the service
	 *    will be deleted next loop
	 * @param [in] s - A pointer to the service to remove
	 */
	DECLDIR void Fab_KernelRemoveService(IService* s);
	/************************************/
	/*! Mark all services to be removed
	 * @remark This will also end the application
	 */
	DECLDIR void Fab_KernelKillAllServices();
	/************************************/
	/*! Send a message to the services
	 *    (including the service who sends it)
	 * @param [in] msg - Pointer to SMsg object
	 */
	DECLDIR void Fab_KernelSendMessage(SMsg* msg);
	/************************************/

	class IGlobalAccessor;
	/************************************/
	/*! Get the IGlobalAccessor from this dll
	 * @return Pointer to the IGlobalAccessor
	 */
	DECLDIR IGlobalAccessor* Fab_GetGlobalAccessor();
	/************************************/
	/*! Get a stored object from the accessor
	 * @param [in] key - Name/key of the object
	 * @return If found a pointer to the object else nullptr
	 */
	DECLDIR void *Fab_GlobalAccessorGetObject(const char* key);
	/************************************/
	/*! Add or update an object stored in the accessor
	 * @param [in] key - Name/key for the objct to update or store
	 * @param [in] pObject - Pointer to the object to store
	 */
	DECLDIR void Fab_GlobalAccessorAddObject(const char* key, void* pObject);
	/************************************/

	class IContentManager;
	/************************************/
	/*! Create a new content manager to load and manage content
	 * @param [in] pRend - IRenderer used for creating the content
	 * @return Pointer to the IContentmanager
	 */
	DECLDIR IContentManager *Fab_ContentCreateManager(IRenderer* pRend);
	/************************************/
	/*! Releases a contentManager
	 * @param[in] pCM - IContentManager to release
	 */
	DECLDIR void Fab_ContentReleaseManager(IContentManager* pCM);
	/************************************/


	class IMaterial;
	class IShader;
	class IImage;
	/************************************/
	/*! Creates an material ussing the given shader and image 
	 *    filling in the image for the draw in the shader
	 * @param [in] pShad	- pointer to a IShader
	 * @param [in] pImg		- pointer to a IImage
	 * @return Pointer to the IMaterial
	 */
	DECLDIR IMaterial *Fab_MatCreateDifTexture(IShader* pShad, IImage* pImg);
	/************************************/
}

/*! @} */

#endif //FABIAN_FABIAN_H_