#ifndef FABIAN_IINPUT_H_
#define FABIAN_IINPUT_H_

#include "FabianDef.h"
#include "InputDef.h"

////////////////////////////////////////////
//! Interface IInput: 
//! this interface provides a way of getting all
//! input stages for the game and for manipulating them.
////////////////////////////////////////////
class IInput
{
public:
	/************************************/
	/*! Constructor */
	IInput() { };
	/************************************/
	/*! Destructor */
	virtual ~IInput() { };
	/************************************/
	
	/************************************/
	/*! Gets the state of a requested key
	 * @param [in] k - FKey to check the state of
	 * @return The state of the key
	 */
	virtual KeyState GetKeyState(FKey k) const = 0;
	/************************************/
	
	/************************************/
	/*! Gets the current position of the mouse relative to the window
	 * @param [out] x - X value of the position
	 * @param [out] y - Y value of the position
	 */
	virtual void GetMousePos(int& x, int& y) const = 0;
	/************************************/
	/*! Gets the distance the mouse moved since last frame
	 * @param [out] x - X value of the movement
	 * @param [out] y - Y value of the movement
	 */
	virtual void GetMouseMovement(int& x, int& y) const = 0;
	/************************************/
	
	/************************************/
	/*! Locks/unlocks the mouse inside the window
	 * @param [in] bLockMouse - True to lock the mouse and false to free it
	 */
	virtual void LockMouse(bool bLockMouse) = 0;
	/************************************/
	/*! Locks the mouse inside the window at a specific position
	 * @param [in] x - X value of the position
	 * @param [in] y - Y value of the position
	 */
	virtual void LockMouse(int x, int y) = 0;
	/************************************/

private:
	DISALLOW_COPY_AND_ASSIGN(IInput);
};

#endif //FABIAN_IINPUT_H_
