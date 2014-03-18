#ifndef FABIAN_LOGDEF_H_
#define FABIAN_LOGDEF_H_

/** @file */ 

/*! Log level identifiers (flags) */
enum FLOG_LVL : char
{
	FLOG_LVL_UNKNOWN	 = 0,	/*!< Unknown log level entry */
	FLOG_LVL_INFO		 = 1,	/*!< Informative log entry */
	FLOG_LVL_WARNING	 = 2,	/*!< Warning log entry */
	FLOG_LVL_ERROR		 = 4	/*!< Error log entry */
};

/*! Log id identifiers (flags)
 * @remark You can extend on these if the ILogger supports it. 
 * Keep in mind that these are bit flags
 */
enum FLOG_ID : char
{
	FLOG_ID_APP			 = 1,	/*!< Log on application level */
	FLOG_ID_CLIENT		 = 2,	/*!< Log for client use only */
	FLOG_ID_SERVER		 = 4,	/*!< Log server event */
	FLOG_ID_USER		 = 8	/*!< Log on user level */
};

#endif // FABIAN_LOGDEF_H_

