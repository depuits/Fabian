#ifndef FABIAN_ISERVICE_H_
#define FABIAN_ISERVICE_H_

#include "FabianDef.h"

class IService
{
public:
	IService(int priorety = 5000)
		:m_bCanKill(false)
		,m_iPriority(priorety)
	{
	};
	virtual ~IService() { };
	
	virtual bool Start() = 0;
	virtual void OnSuspend() { };
	virtual void Update() = 0;
	virtual void OnResume() { };
	virtual void Stop() = 0;
	
	bool GetCanKill() const { return m_bCanKill; };
	void SetCanKill(bool canKill) { m_bCanKill = canKill; };

	int GetPriorety() const { return m_iPriority; };
	void SetPriorety(int priorety) { m_iPriority = priorety; };

protected:
	bool m_bCanKill;
	int m_iPriority;

private:
	DISALLOW_COPY_AND_ASSIGN(IService);
};

#endif //FABIAN_ISERVICE_H_
