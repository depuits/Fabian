#ifndef FABIAN_CVIDEOUPDATESERVICE_H_
#define FABIAN_CVIDEOUPDATESERVICE_H_

#include "IService.h"
#include <SDL.h>

class CVideoUpdateService : public IService
{
public:
	CVideoUpdateService(int priorety = 5000);
	virtual ~CVideoUpdateService();
	
	virtual bool Start();
	virtual void Update();
	virtual void Stop();
	

protected:
	int m_iScreenWidth, 
		m_iScreenHeight;

	SDL_Window *m_pWindow;
	SDL_GLContext m_GLContext;

private:
	DISALLOW_COPY_AND_ASSIGN(CVideoUpdateService);
};

#endif //FABIAN_CVIDEOUPDATESERVICE_H_
