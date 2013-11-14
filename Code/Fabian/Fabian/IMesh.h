#ifndef FABIAN_IMESH_H_
#define FABIAN_IMESH_H_

#include "FabianDef.h"
#include <string>

//******************************************
// Interface IMesh:
// the mesh object is responsible for loading 
// the buffers and calling any graphics related
// methods
//******************************************
class IMesh
{
public:
	//-------------------------------------
	// Constructor
	IMesh() { };
	//-------------------------------------
	// Destructor
	virtual ~IMesh() { };
	//-------------------------------------
	
	//-------------------------------------
	// Loads and initializes the mesh by loading any needed buffers, etc.
	// p1 in - string, path to the mesh file
	//            ! this is going to be a meshLoaderData
	// rv - bool, return false if something failed
	virtual bool Load(const std::string&) = 0;
	//-------------------------------------
	// Calls the internal draw methods
	virtual void Draw() = 0;
	//-------------------------------------

private:
	DISALLOW_COPY_AND_ASSIGN(IMesh);
};

#endif //FABIAN_IMESH_H_
