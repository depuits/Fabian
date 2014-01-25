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
	//-------------------------------------
	// Creates logger object used for logging
	// rv - pointer to logger object
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
	//-------------------------------------
	// Adds an logger object to a multiple logger object
	// p1 in - pointer to logger object
	DECLDIR void Fab_LoggerMultipleAddLogger(ILogger* pLoggerMulti, ILogger* pLogger)
	{
		dynamic_cast<CLoggerMultiple*>(pLoggerMulti)->AddLogger(pLogger);
	}
	//-------------------------------------
	// Assign a logger used to do the actual logging
	// p1 in - pointer to ILogger object (takes over ownership)
	// rv - bool, true when succesfully assigned
	DECLDIR bool Fab_LogAssignLogger(ILogger* pLogger)
	{
		return CLog::Get().AssignLogger(pLogger);
	}
	//-------------------------------------
	// Write an message to the log
	// p1 in - Log Level
	// p2 in - Log id
	// p3 in - Log message, registered id or string message
	// ... - Extra parameters, see sprintf in
	DECLDIR void Fab_LogWrite(char lvl, char id, const char* msg, ...)
	{
		va_list args;
		va_start(args, msg);
		char szBuf[1024];
		vsprintf(szBuf, msg, args);
		va_end(args);

		CLog::Get().Write(lvl, id, szBuf);
	}
	//-------------------------------------	
	
	//-------------------------------------
	// Get the kernel from this dll
	// rv - returns pointer to the kernel
	DECLDIR IKernel* Fab_GetKernel()
	{
		return &CKernel::Get();
	}
	//-------------------------------------
	// Start running the engine,
	//    should be called after the base services are added
	// rv - returns 0
	DECLDIR int Fab_KernelExecute()
	{
		return CKernel::Get().Execute();
	}
	//-------------------------------------
	// Adds a service to the kernel and takes ownership of it
	// p1 in - a pointer to the service to add (can't be 0)(takes over ownership)
	// rv - returns pointer to the service on succes and a nullptr when it fails
	DECLDIR IService* Fab_KernelAddService(IService* pServ, int iPrior)
	{
		return CKernel::Get().AddService(pServ, iPrior);
	}
	//-------------------------------------
	// Marks a service to be removed, the service
	//    will be deleted next loop
	// p1 in - a pointer to the service to remove
	DECLDIR void Fab_KernelRemoveService(IService* pServ)
	{
		CKernel::Get().RemoveService(pServ);
	}
	//-------------------------------------
	// Mark all services to be removed and end the
	//    application by doing so
	DECLDIR void Fab_KernelKillAllServices()
	{
		CKernel::Get().KillAllServices();
	}
	//-------------------------------------
	// Send a message to the services
	//    (including the service who sends it)
	// p1 in - pointer to SMsg object
	DECLDIR void Fab_KernelSendMessage(SMsg* msg)
	{
		CKernel::Get().SendMessage(msg);
	}
	//-------------------------------------

	//-------------------------------------
	// Get the GlobalAccessor from this dll
	// rv - returns pointer to the GlobalAccessor
	DECLDIR IGlobalAccessor* Fab_GetGlobalAccessor()
	{
		return &CGlobalAccessor::Get();
	}
	//-------------------------------------
	// Get a stored object from the accessor
	// p1 in - name of the object
	// rv - if found a pointer to the object else nullptr
	DECLDIR void *Fab_GlobalAccessorGetObject(const char* sKey)
	{
		return CGlobalAccessor::Get().GetObject(sKey);
	}
	//-------------------------------------
	// Add or update an object stored in the accessor
	// p1 in - name for the objct to update or store
	// p2 in - a pointer to the object to store
	DECLDIR void Fab_GlobalAccessorAddObject(const char* sKey, void* pVal)
	{
		CGlobalAccessor::Get().AddObject(sKey, pVal);
	}
	//-------------------------------------
	
	//-------------------------------------
	// create a new content manager to load and manage content
	// p1 in - renderer used for creating the content
	// rv - pointer to the contentmanager
	DECLDIR IContentManager *Fab_ContentCreateManager(IRenderer *pRend)
	{
		return new CContentManager(pRend);
	}
	//-------------------------------------
	// releases a contentManager
	// p1 in - ContentManager to release
	DECLDIR void Fab_ContentReleaseManager(IContentManager* pCM)
	{
		// here could some checks to see if i created this object
		delete pCM;
	}
	//-------------------------------------

	//-------------------------------------
	// creates an material using the given shader and image
	//    filling in the image for the draw in the shader
	// p1 in - pointer to the shader
	// p2 in - pointer to the image
	// rv - returns pointer to the IMaterial
	DECLDIR IMaterial *Fab_MatCreateDifTexture(IShader* pShad, IImage* pImg)
	{
		return new CMatDifTexture(pShad, pImg);
	}
	//-------------------------------------
}

