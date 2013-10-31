#ifndef FABIAN_FABIANDEF_H_
#define FABIAN_FABIANDEF_H_

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)



#endif //FABIAN_FABIANDEF_H_