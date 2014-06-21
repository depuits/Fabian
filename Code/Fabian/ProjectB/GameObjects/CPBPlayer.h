#ifndef PROJECTB_CPBPLAYER_H_
#define PROJECTB_CPBPLAYER_H_

#include "CPBGameObject.h"

class IMesh;
class IMaterial;

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
class CPBPlayer : public CPBGameObject
{
public:
	//-------------------------------------
	// Constructor
	// p1 in* - int, the priorety of the service
	//            ( the lower the higher the priorety )
	CPBPlayer(IInput*);
	//-------------------------------------
	// Destructor
	virtual ~CPBPlayer();
	//-------------------------------------
	
	virtual void LoadData(IContentManager*);	// used to load al the needed data for the object
	virtual void Init();						// used for (re)initializing the object
	virtual void Update(float);					// called when the onject needs to update
	virtual void Draw();						// called when the object needs to be drawn

protected:
	IInput* m_pInput;

	IMesh* m_pMesh;
	IMaterial* m_pMaterial;

private:
	DISALLOW_COPY_AND_ASSIGN(CPBPlayer);
};

#endif //PROJECTB_CPBPLAYER_H_
