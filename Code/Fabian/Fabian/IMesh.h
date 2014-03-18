#ifndef FABIAN_IMESH_H_
#define FABIAN_IMESH_H_

#include "FabianDef.h"
#include "DataStructures.h"

////////////////////////////////////////////
//! Interface IMesh: 
//! the mesh object is responsible for loading 
//! the buffers and calling any graphics related 
//! methods
////////////////////////////////////////////
class IMesh
{
public:
	/************************************/
	/*! Constructor */
	IMesh() { };
	/************************************/
	/*! Destructor */
	virtual ~IMesh() { };
	/************************************/
	
	/************************************/
	/*! Loads and initializes the mesh by loading any needed buffers, etc.
	 * @param [in] md -¨Pointer to the MeshData for the mesh
	 * @return False if something failed
	 */
	virtual bool Load(MeshData* md) = 0;
	/************************************/
	/*! Calls the internally used draw methods */
	virtual void Draw() = 0;
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(IMesh);
};

#endif //FABIAN_IMESH_H_
