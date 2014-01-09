#ifndef FABIAN_CLOGGERTOFILES_H_
#define FABIAN_CLOGGERTOFILES_H_

#include "ILogger.h"
#include <fstream>

//******************************************
// Class CLoggerToFiles:
// ILogger class which writes out the log to 
// files, one file per log id. It uses only the
// default log id's. The user log id get shown a
// messagebox. 
//******************************************
class CLoggerToFiles : public ILogger
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - bool, append to the already existing file
	CLoggerToFiles(bool = true);
	//-------------------------------------
    // This function must not be implemented in the header or the
    // linker will build the code to call the application delete()
    // function instead of the library delete() function.
    virtual void Release();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the logger, should be called
	//    before using or assigning the logger
	// rv - returns false if it failed
	bool Init();
	//-------------------------------------

	//-------------------------------------
	// Gets called whenever the logs receives a message
	//    and needs it to be actually logged
	// p1 in - log level, useally ERROR, WARNING or INFO
	// p2 in - log id, the place where to write to
	// p3 in - log message
	virtual void Write(char, char, const char*);
	//-------------------------------------

protected:
	//-------------------------------------
	// Destructor
	// private so it can only be called by Release();
	virtual ~CLoggerToFiles();
	//-------------------------------------

private:
	bool m_bAppend;
	
    std::ofstream m_osAppLog;
    std::ofstream m_osClientLog;
    std::ofstream m_osServerLog;

	DISALLOW_COPY_AND_ASSIGN(CLoggerToFiles);
};

#endif //FABIAN_CLOGGERTOFILES_H_
