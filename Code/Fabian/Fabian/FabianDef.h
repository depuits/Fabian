#ifndef FABIAN_FABIANDEF_H_
#define FABIAN_FABIANDEF_H_

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// define for disabling warnings in MSV
#ifdef _MSC_VER
    #define FDISABLE_WARNING_START(warningc)		\
        __pragma(warning(push))						\
        __pragma(warning(disable:warningc))

    #define FDISABLE_WARNING_END(warningc)		\
        __pragma(warning(pop))

#else
    #define FDISABLE_WARNING_START(warningc)
    #define FDISABLE_WARNING_END(warningc)
#endif

// assertion within a macro for easy changing
#include <assert.h>

#define FASSERT(condition)	assert(condition)


// dll export define
#ifdef WIN32
	#ifdef DLL_EXPORT
		#define DECLDIR __declspec(dllexport)
	#else
		#define DECLDIR __declspec(dllimport)
	#endif
#else
	#define DECLDIR
#endif


#endif //FABIAN_FABIANDEF_H_
