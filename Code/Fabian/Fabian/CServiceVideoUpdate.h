#ifndef FABIAN_CSERVICEVIDEOUPDATE_H_
#define FABIAN_CSERVICEVIDEOUPDATE_H_

#include "IService.h"
#include <string>
#include <SDL.h>

class CRendererOpenGL;

class CServiceVideoUpdate : public IService
{
public:
	CServiceVideoUpdate(int priorety = 5000);
	virtual ~CServiceVideoUpdate();
	
	virtual bool Start();
	virtual void Update();
	virtual void Stop();
	
	virtual void MsgProc(SMsg*);

	bool SetWindowName(const std::string&);

	bool SetFullScreen(bool);
	bool SetScreenResolution(int, int);

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
