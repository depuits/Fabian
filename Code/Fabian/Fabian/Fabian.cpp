#include "Fabian.h"

#include "CLoggerToFiles.h"
#include "CLoggerToConsole.h"
#include "CLoggerMultiple.h"
#include "CLog.h"
#include "CKernel.h"
#include "CGlobalAccessor.h"
#include "CContentManager.h"
#include "CMatDifTexture.h"

#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

extern "C"
{
	/************************************/
	/// @{
	/*! Creates ILogger object used for logging
	 * @return Pointer to ILogger object
	 */
	DECLDIR ILogger* Fab_LoggerCreateToFiles(bool bAppendFile)
	{
		CLoggerToFiles *pLogger = new CLoggerToFiles(bAppendFile);
		pLogger->Init();
		return pLogger;
	}
	DECLDIR ILogger* Fab_LoggerCreateToConsole(bool bBreakOnError)
	{
		CLoggerToConsole *pLogger = new CLoggerToConsole(bBreakOnError);
		pLogger->Init();
		return pLogger;
	}
	DECLDIR ILogger* Fab_LoggerCreateToMultiple()
	{
		return new CLoggerMultiple();
	}
	/// @}
	/************************************/
	/*! Adds an ILogger object to a multiple logger object
	 * @param [in] pLoggerMulti - Pointer to the multi logger object
	 * @param [in] pLogger - Pointer to ILogger object to add
	 */
	DECLDIR void Fab_LoggerMultipleAddLogger(ILogger* pLoggerMulti, ILogger* pLogger)
	{
		dynamic_cast<CLoggerMultiple*>(pLoggerMulti)->AddLogger(pLogger);
	}
	/************************************/
	/*! Assign a logger used to do the actual logging
	 * @param [in] pLogger - Pointer to ILogger object (takes over ownership)
	 * @return True when successfully assigned
	 */
	DECLDIR bool Fab_LogAssignLogger(ILogger* pLogger)
	{
		return CLog::Get().AssignLogger(pLogger);
	}
	/************************************/
	/*! Write an message to the log
	 * @param [in] lvl 	- FLOG_LVL, useally ERROR, WARNING or INFO
	 * @param [in] id	- FLOG_ID, the place where to write to
	 * @param [in] msg	- Log message
	 * @param [in] ... - Extra parameters, see sprintf
	 */
	DECLDIR void Fab_LogWrite(char lvl, char id, const char* msg, ...)
	{
		va_list args;
		va_start(args, msg);
		char szBuf[1024];
		vsprintf(szBuf, msg, args);
		va_end(args);

		CLog::Get().Write(lvl, id, szBuf);
	}
	/************************************/
	
	/************************************/
	/*! Get the kernel from this dll
	 * @return Pointer to the IKernel
	 */
	DECLDIR IKernel* Fab_GetKernel()
	{
		return &CKernel::Get();
	}
	/************************************/
	/*! Start running the engine, 
	 *    should be called after the base services are added
	 * @return 0
	 */
	DECLDIR int Fab_KernelExecute()
	{
		return CKernel::Get().Execute();
	}
	/************************************/
	/*! Adds a service to the kernel and takes ownership of it
	 * @param [in] sLib		- Lib file from which to load the service
	 * @param [in] sService - Name of the service to load (one lib can contain multiple services)
	 * @param [in] iPrior 	- The priority of this service
	 * @return Pointer to the IService on succes and a nullptr when it fails
	 */
	DECLDIR IService* Fab_KernelAddService(const char* sLib, const char* sService, int iPrior)
	{
		return CKernel::Get().AddService(sLib, sService, iPrior);
	}
	/************************************/
	/*! Marks a service to be removed, the service
	 *    will be deleted next loop
	 * @param [in] s - A pointer to the service to remove
	 */
	DECLDIR void Fab_KernelRemoveService(IService* pServ)
	{
		CKernel::Get().RemoveService(pServ);
	}
	/************************************/
	/*! Mark all services to be removed
	 * @remark This will also end the application
	 */
	DECLDIR void Fab_KernelKillAllServices()
	{
		CKernel::Get().KillAllServices();
	}
	/************************************/
	/*! Send a message to the services
	 *    (including the service who sends it)
	 * @param [in] msg - Pointer to SMsg object
	 */
	DECLDIR void Fab_KernelSendMessage(SMsg* msg)
	{
		CKernel::Get().SendMessage(msg);
	}
	/************************************/

	/************************************/
	/*! Get the IGlobalAccessor from this dll
	 * @return Pointer to the IGlobalAccessor
	 */
	DECLDIR IGlobalAccessor* Fab_GetGlobalAccessor()
	{
		return &CGlobalAccessor::Get();
	}
	/************************************/
	/*! Get a stored object from the accessor
	 * @param [in] key - Name/key of the object
	 * @return If found a pointer to the object else nullptr
	 */
	DECLDIR void *Fab_GlobalAccessorGetObject(const char* sKey)
	{
		return CGlobalAccessor::Get().GetObject(sKey);
	}
	/************************************/
	/*! Add or update an object stored in the accessor
	 * @param [in] key - Name/key for the objct to update or store
	 * @param [in] pObject - Pointer to the object to store
	 */
	DECLDIR void Fab_GlobalAccessorAddObject(const char* sKey, void* pVal)
	{
		CGlobalAccessor::Get().AddObject(sKey, pVal);
	}
	/************************************/

	/************************************/
	/*! Create a new content manager to load and manage content
	 * @param [in] pRend - IRenderer used for creating the content
	 * @return Pointer to the IContentmanager
	 */
	DECLDIR IContentManager *Fab_ContentCreateManager(IRenderer *pRend)
	{
		return new CContentManager(pRend);
	}
	/************************************/
	/*! Releases a contentManager
	 * @param[in] pCM - IContentManager to release
	 */
	DECLDIR void Fab_ContentReleaseManager(IContentManager* pCM)
	{
		// here could some checks to see if i created this object
		delete pCM;
	}
	/************************************/

	/************************************/
	/*! Creates an material ussing the given shader and image 
	 *    filling in the image for the draw in the shader
	 * @param [in] pShad	- pointer to a IShader
	 * @param [in] pImg		- pointer to a IImage
	 * @return Pointer to the IMaterial
	 */
	DECLDIR IMaterial *Fab_MatCreateDifTexture(IShader* pShad, IImage* pImg)
	{
		return new CMatDifTexture(pShad, pImg);
	}
	/************************************/
}

