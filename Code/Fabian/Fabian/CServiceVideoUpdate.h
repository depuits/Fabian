#ifndef FABIAN_CSERVICEVIDEOUPDATE_H_
#define FABIAN_CSERVICEVIDEOUPDATE_H_

#include "IService.h"
#include <string>
#include <SDL.h>

// --forward declarations--
class CRendererOpenGL;
// ------------------------

//******************************************
// Class CServiceVideoUpdate:
// service responsable for creating and updating 
// the video output
//******************************************
class CServiceVideoUpdate : public IService
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service 
	//            ( the lower the higher the priorety )
	CServiceVideoUpdate(int priorety = 5000);
	//-------------------------------------
	// Destructor
	virtual ~CServiceVideoUpdate();
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
	
	//-------------------------------------
	// Sets the name of the window
	// p1 in - string, name of the window
	// rv - bool, true when succeeds
	bool SetWindowName(const std::string&);
	//-------------------------------------
	// Sets the visibility of the OS cursor
	// p1 in - bool, true to show it, false to hide it
	void ShowCursor(bool);
	//-------------------------------------
	
	//-------------------------------------
	// Helper method for the IRenderer
	//-------------------------------------
	// Sets the window to fullscreen or back to windowed
	// p1 in - bool, goes to fullscreen if true
	// rv - bool, true when succeeds
	bool SetFullScreen(bool);
	//-------------------------------------
	// Sets the screen resolution of this game
	// p1 in - int, screen width
	// p2 in - int, screen height
	// rv - bool, true when succeeds
	bool SetScreenResolution(int, int);
	//-------------------------------------

protected:
	int m_iScreenWidth, 
		m_iScreenHeight;

	SDL_Window *m_pWindow;
	SDL_GLContext m_GLContext;

	CRendererOpenGL *m_pRenderer;

private:
	DISALLOW_COPY_AND_ASSIGN(CServiceVideoUpdate);
};

#endif //FABIAN_CSERVICEVIDEOUPDATE_H_
