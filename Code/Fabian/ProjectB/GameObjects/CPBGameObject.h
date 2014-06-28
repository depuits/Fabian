#ifndef PROJECTB_CPBGAMEOBJECT_H_
#define PROJECTB_CPBGAMEOBJECT_H_

#include <Fabian.h>
#include <CTransform.hpp>

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CPBGameObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service
	//            ( the lower the higher the priorety )
	CPBGameObject();
	//-------------------------------------
	// Destructor
	virtual ~CPBGameObject();
	//-------------------------------------
	
	virtual void LoadData(IContentManager*, IRenderer*) { };	// used to load al the needed data for the object
	virtual void Init() { };									// used for (re)initializing the object
	virtual void Update(float) { };								// called when the onject needs to update
	virtual void Draw() { };									// called when the object needs to be drawn

	CTransform *GetTransform();

protected:
	CTransform m_Transform;


private:
	DISALLOW_COPY_AND_ASSIGN(CPBGameObject);
};

#endif //PROJECTB_CPBSERVICE_H_
