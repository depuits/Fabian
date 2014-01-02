#ifndef FABIAN_CCOMPMODEL_H_
#define FABIAN_CCOMPMODEL_H_

#include "FabianDef.h"
#include "IComponent.h"

// --forward declarations--
class IMesh;
class IMaterial;
// ------------------------

//******************************************
// Class CCompModel:
// Wrapper class to draw a meshes with a transform
//******************************************
class CCompModel : public IComponent
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - pointer to Mesh object to draw
	// p2 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CCompModel(IMesh*, IMaterial*);
	//-------------------------------------
	// Destructor
	virtual ~CCompModel();
	//-------------------------------------

	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, false if something failed
	virtual bool Start();
	//-------------------------------------
	// Draws the object on the screen ussing the given shader
	// p1 in - pointer to the shader the object should draw with
	virtual void Draw();
	//-------------------------------------

protected:
	IMesh* m_pMesh;
	IMaterial *m_pMaterial;

private:
	DISALLOW_COPY_AND_ASSIGN(CCompModel);
};

#endif //FABIAN_CCOMPMODEL_H_
