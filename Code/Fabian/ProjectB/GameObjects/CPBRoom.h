#ifndef PROJECTB_CPBROOM_H_
#define PROJECTB_CPBROOM_H_

#include "CPBGameObject.h"

class IMesh;
class IMaterial;

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CPBRoom : public CPBGameObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service
	//            ( the lower the higher the priorety )
	CPBRoom(glm::vec2&);
	//-------------------------------------
	// Destructor
	virtual ~CPBRoom();
	//-------------------------------------
	
	virtual void LoadData(IContentManager*, IRenderer*);	// used to load al the needed data for the object
	virtual void Init();						// used for (re)initializing the object
	virtual void Update(float);					// called when the onject needs to update
	virtual void Draw();						// called when the object needs to be drawn

protected:
	IMesh* m_pMeshFloor;
	IMesh* m_pMeshWalls;
	IMesh* m_pMeshRoof;

	IMaterial* m_pMaterialFloor;
	IMaterial* m_pMaterialWalls;
	IMaterial* m_pMaterialRoof;
	
	glm::vec2 m_size;

private:
	DISALLOW_COPY_AND_ASSIGN(CPBRoom);
};

#endif //PROJECTB_CPBROOM_H_
