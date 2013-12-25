#ifndef FABIAN_FABIANDEF_H_
#define FABIAN_FABIANDEF_H_

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// sdl assertion within a macro because of compiler warnings
#include <SDL_assert.h>

#ifdef _MSC_VER
    #define FASSERT(condition)			\
        __pragma(warning(push))			\
        __pragma(warning(disable:4127))	\
        SDL_assert(condition);			\
        __pragma(warning(pop))

    #define FASSERTR(condition)			\
        __pragma(warning(push))			\
        __pragma(warning(disable:4127))	\
        SDL_assert_release(condition);	\
        __pragma(warning(pop))
#else
    #define FASSERT(condition)			\
        SDL_assert(condition);

    #define FASSERTR(condition)			\
        SDL_assert_release(condition);
# endif

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
