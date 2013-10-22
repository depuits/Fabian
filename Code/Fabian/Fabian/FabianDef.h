#ifndef FABIAN_FABIANDEF_H_
#define FABIAN_FABIANDEF_H_

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)


typedef unsigned int ServiceMessage;


#define SM_QUIT			0
#define SM_TIMER_DT		10


#endif //FABIAN_FABIANDEF_H_