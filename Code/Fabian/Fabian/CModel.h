#ifndef FABIAN_CMODEL_H_
#define FABIAN_CMODEL_H_

#include "FabianDef.h"
#include "IObject.h"

// --forward declarations--
class IMesh;
// ------------------------

//******************************************
// Class CModel:
// Wrapper class to draw a meshes with a transform
//******************************************
class CModel : public IObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in - pointer to Mesh object to draw
	// p2 in* - pointer to parent object, this causes
	//            the object to be linked to the parent
	CModel(IMesh*, IObject* = nullptr);
	//-------------------------------------
	// Destructor
	virtual ~CModel();
	//-------------------------------------
	
	//-------------------------------------
	// Initializes the object, should be called before any other
	//    method of the object.
	// rv - bool, false if something failed	
	virtual bool Init();
	//-------------------------------------
	// Draws the object on the screen ussing the given shader
	// p1 in - pointer to the shader the object should draw with
	virtual void Draw(IShader*);
	//-------------------------------------

protected:
	IMesh* m_pMesh;

	static int s_iIdWorld;

private:
	DISALLOW_COPY_AND_ASSIGN(CModel);
};

#endif //FABIAN_CMODEL_H_
