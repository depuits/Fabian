#ifndef FABIAN_LOGDEF_H_
#define FABIAN_LOGDEF_H_

// Log level iddentifiers
enum FLOG_LVL : char
{
	FLOG_LVL_UNKNOWN	 = 0,
	FLOG_LVL_INFO		 = 1,
	FLOG_LVL_WARNING	 = 2,
	FLOG_LVL_ERROR		 = 4
};

// Log id iddentifiers
// You can extend on these if the ILogger supports it
// keep in mind that these are bit flags
enum FLOG_ID : char
{
	FLOG_ID_APP			 = 1,
	FLOG_ID_CLIENT		 = 2,
	FLOG_ID_SERVER		 = 4,
	FLOG_ID_USER		 = 8
};

#endif // FABIAN_LOGDEF_H_

