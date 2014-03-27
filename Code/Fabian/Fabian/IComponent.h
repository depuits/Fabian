#ifndef FABIAN_ICOMPONENT_H_
#define FABIAN_ICOMPONENT_H_

#include "FabianDef.h"

// --forward declarations--
class IShader;
class CGameObject;
// ------------------------

/// Log level iddentifiers
enum FCOMP_STATE : unsigned char
{
	FCOMP_STATE_ENABLE      = 0,
	FCOMP_STATE_DISABLE	    = 1,

	FCOMP_STATE_USER     	= 32,
	FCOMP_STATE_MAX     	= 255
};

////////////////////////////////////////////
//! Interface IComponent: 
//! the base for all components that can be 
//! added to a CGameObject
////////////////////////////////////////////
class IComponent
{
	friend class CGameObject;

public:
	/************************************/
	/*! Constructor */
	IComponent() { }
	/************************************/
	/*! Destructor */
	virtual ~IComponent() { }
	/************************************/

	/************************************/
	/*! Initializes the object, should be called before any other
	 *    method of the object.
	 * @return False if something failed
	 */
	virtual bool Start() = 0;
	/************************************/
	/*! Method called when the IComponent gets removed */
	virtual void End() = 0;
	/************************************/
	/*! Updates the object according to dTime
	 * @param [in] fDt - Time past since last update call
	 */
	virtual void Update(float fDt) = 0;
	/************************************/
	/*! Draws the object on the screen */
	virtual void Draw() = 0;
	/************************************/

	/************************************/
	/*! This method is called when the component states changed
	 *    You can also use this method to send custom messages or states
	 * @param [in] state - FCOMP_STATE, state identifier
	 */
	virtual void UpdateState(unsigned char state) = 0;
	/************************************/

	/************************************/
	/*! Enables the IComponent in the gameobject */
	virtual void Enable() = 0;
	/************************************/
	/*! disables the IComponent in the gameobject */
	virtual void Disable() = 0;
	/************************************/

protected:
	/************************************/
	/*! Change the component parent CGameObject 
	 * @param [in] pPar - Pointer to CGameObject parent
	 */
	virtual void SetParent(CGameObject*) = 0;
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(IComponent);
};

#endif //FABIAN_ICOMPONENT_H_
