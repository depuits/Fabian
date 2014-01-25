#ifndef FABIAN_FABIAN_H_
#define FABIAN_FABIAN_H_

#include "FabianDef.h"

#include "LogDef.h"
#include "ServiceMsg.h"

extern "C"
{	
	class ILogger;
	//-------------------------------------
	// Creates logger object used for logging
	// rv - pointer to logger object
	DECLDIR ILogger* Fab_LoggerCreateToFiles(bool bAppendFile = false);
	DECLDIR ILogger* Fab_LoggerCreateToConsole(bool bBreakOnError = true);
	DECLDIR ILogger* Fab_LoggerCreateToMultiple();
	//-------------------------------------
	// Adds an logger object to a multiple logger object
	// p1 in - pointer to the multi logger object
	// p1 in - pointer to logger object to add
	DECLDIR void Fab_LoggerMultipleAddLogger(ILogger*, ILogger*);
	//-------------------------------------
	// Assign a logger used to do the actual logging
	// p1 in - pointer to ILogger object (takes over ownership)
	// rv - bool, true when succesfully assigned
	DECLDIR bool Fab_LogAssignLogger(ILogger*);
	//-------------------------------------
	// Write an message to the log
	// p1 in - Log Level
	// p2 in - Log id
	// p3 in - Log message, registered id or string message
	// ... - Extra parameters, see sprintf in
	DECLDIR void Fab_LogWrite(char, char, const char*, ...);
	//-------------------------------------
	
	class IKernel;
	class IService;
	//-------------------------------------
	// Get the kernel from this dll
	// rv - returns pointer to the kernel
	DECLDIR IKernel* Fab_GetKernel();
	//-------------------------------------
	// Start running the engine,
	//    should be called after the base services are added
	// rv - returns 0
	DECLDIR int Fab_KernelExecute();
	//-------------------------------------
	// Adds a service to the kernel and takes ownership of it
	// p1 in - a pointer to the service to add (can't be 0)(takes over ownership)
	// rv - returns pointer to the service on succes and a nullptr when it fails
	DECLDIR IService* Fab_KernelAddService(IService*, int);
	//-------------------------------------
	// Marks a service to be removed, the service
	//    will be deleted next loop
	// p1 in - a pointer to the service to remove
	DECLDIR void Fab_KernelRemoveService(IService*);
	//-------------------------------------
	// Mark all services to be removed and end the
	//    application by doing so
	DECLDIR void Fab_KernelKillAllServices();
	//-------------------------------------
	// Send a message to the services
	//    (including the service who sends it)
	// p1 in - pointer to SMsg object
	DECLDIR void Fab_KernelSendMessage(SMsg*);
	//-------------------------------------

	class IGlobalAccessor;
	//-------------------------------------
	// Get the GlobalAccessor from this dll
	// rv - returns pointer to the GlobalAccessor
	DECLDIR IGlobalAccessor* Fab_GetGlobalAccessor();
	//-------------------------------------
	// Get a stored object from the accessor
	// p1 in - name of the object
	// rv - if found a pointer to the object else nullptr
	DECLDIR void *Fab_GlobalAccessorGetObject(const char*);
	//-------------------------------------
	// Add or update an object stored in the accessor
	// p1 in - name for the objct to update or store
	// p2 in - a pointer to the object to store
	DECLDIR void Fab_GlobalAccessorAddObject(const char*, void*);
	//-------------------------------------

	class IContentManager;
	//-------------------------------------
	// create a new content manager to load and manage content
	// p1 in - renderer used for creating the content
	// rv - pointer to the contentmanager
	DECLDIR IContentManager *Fab_ContentCreateManager(IRenderer*);
	//-------------------------------------
	// releases a contentManager
	// p1 in - ContentManager to release
	DECLDIR void Fab_ContentReleaseManager(IContentManager*);
	//-------------------------------------


	class IMaterial;
	class IShader;
	class IImage;
	//-------------------------------------
	// creates an material using the given shader and image
	//    filling in the image for the draw in the shader
	// p1 in - pointer to the shader
	// p2 in - pointer to the image
	// rv - returns pointer to the IMaterial
	DECLDIR IMaterial *Fab_MatCreateDifTexture(IShader*, IImage*);
	//-------------------------------------
}

#endif //FABIAN_FABIAN_H_