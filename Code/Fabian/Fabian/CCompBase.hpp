#ifndef FABIAN_CCOMPBASE_H_
#define FABIAN_CCOMPBASE_H_

#include "IComponent.h"
#include "CGameObject.hpp"

////////////////////////////////////////////
//! Class CCompBase: 
//! a base implementation of IComponent
////////////////////////////////////////////
class CCompBase : public IComponent
{
public:
	/************************************/
	/*! Constructor */
	CCompBase()
		:IComponent()
		,m_pGameObject(nullptr)
	{
	}
	/************************************/
	/*! Destructor */
	virtual ~CCompBase() { }
	/************************************/

	/************************************/
	/*! Initializes the object, should be called before any other
	 *    method of the object.
	 * @return False if something failed
	 */
	virtual bool Start() = 0;
	/************************************/
	/*! Method called when the IComponent gets removed */
	virtual void End() { }
	/************************************/
	/*! Updates the object according to dTime
	 * @param [in] fDt - Time past since last update call
	 */
	virtual void Update(float fDt) { }
	/************************************/
	/*! Draws the object on the screen */
	virtual void Draw() { }
	/************************************/

	/************************************/
	/*! This method is called when the component states changed
	 *    You can also use this method to send custom messages or states
	 * @param [in] state - FCOMP_STATE, state identifier
	 */
	virtual void UpdateState(unsigned char state) {};
	/************************************/

	/************************************/
	/*! Enables the IComponent in the gameobject */
	void Enable()
	{
		m_pGameObject->EnableComponent(this);
	}
	/************************************/
	/*! disables the IComponent in the gameobject */
	void Disable()
	{
		m_pGameObject->DisableComponent(this);
	}
	/************************************/



protected:
	CGameObject *m_pGameObject;

private:
	/************************************/
	/*! Change the component parent CGameObject 
	 * @param [in] pPar - Pointer to CGameObject parent
	 */
	void SetParent(CGameObject* pPar)
	{
		FASSERT( pPar != nullptr && m_pGameObject == nullptr );
		m_pGameObject = pPar;
	}
	/************************************/

	DISALLOW_COPY_AND_ASSIGN(CCompBase);
};

#endif //FABIAN_CCOMPBASE_H_
