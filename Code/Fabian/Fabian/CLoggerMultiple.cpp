#include "CLoggerMultiple.h"


//-------------------------------------
// Constructor
CLoggerMultiple::CLoggerMultiple() 
	:ILogger()
{
}
//-------------------------------------
// Destructor
CLoggerMultiple::~CLoggerMultiple()
{
	for(std::vector<ILogger*>::iterator it( m_vLoggers.begin() ); it != m_vLoggers.end(); ++it)
		delete (*it);

}
//-------------------------------------
	
void CLoggerMultiple::AddLogger(ILogger *pLogger)
{
	m_vLoggers.push_back(pLogger);
}

void CLoggerMultiple::Write(char lvl, char id, const char* msg)
{
	for(std::vector<ILogger*>::iterator it( m_vLoggers.begin() ); it != m_vLoggers.end(); ++it)
		(*it)->Write(lvl, id, msg);
}

